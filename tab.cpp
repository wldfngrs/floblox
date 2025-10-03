#include "tab.h"
#include "floblox.h"
#include "floblox_widgets/functioncall.h"
#include <QtWidgets/QMenu>
#include <QCursor>

#include <iostream>

Tab::Tab(Ui::FlobloxClass ui, QWidget *parent)
    : QWidget{parent}
{
    this->grid_layout = new QGridLayout(this);
    this->grid_layout->setSpacing(6);
    this->grid_layout->setContentsMargins(11, 11, 11, 11);
    this->grid_layout->setObjectName("tab_grid_layout");

    this->scroll_area = new QScrollArea(this);
    this->scroll_area->setObjectName("tab_scroll_area");
    this->scroll_area->setWidgetResizable(true);

    this->scroll_area_widget_contents = new QWidget();
    this->scroll_area_widget_contents->setObjectName("tab_scroll_area_widget_contents");
    this->scroll_area_widget_contents->setGeometry(QRect(0, 0, 603, 198));
    this->scroll_area->setWidget(this->scroll_area_widget_contents);
    this->scroll_area_widget_contents->setContextMenuPolicy(Qt::CustomContextMenu);

    this->grid_layout->addWidget(this->scroll_area, 0, 0, 1, 1);
    this->ui = ui;

    QObject::connect(this->scroll_area_widget_contents, &QScrollArea::customContextMenuRequested, this, &Tab::spawnWidgetsMenu);
    QObject::connect(ui.actionFunction_Call, &QAction::triggered, this, &Tab::spawnFunctionCallWidget);
}

void Tab::spawnWidgetsMenu(const QPoint &pos) {
    QMenu menu(this->scroll_area_widget_contents);
    menu.addAction(ui.actionFunction_Call);
    menu.exec(this->scroll_area_widget_contents->mapToGlobal(pos));
}

void Tab::spawnFunctionCallWidget()
{
    FunctionCall* functionCall = new FunctionCall(this->scroll_area_widget_contents, this->min_x_pos, this->y_offset);
    this->widgets.push_back(functionCall);
    QObject::connect(functionCall, &FunctionCall::dragFinished, this, &Tab::handleWidgetDrop);
    QObject::connect(functionCall, &FunctionCall::dragStarted, this, &Tab::handleWidgetDragStart);
    this->y_offset += this->widgets[this->widgets.size() - 1]->height() + this->spacing;
}

void Tab::handleWidgetDrop(QWidget* dropped_widget, QPoint drop_point) {
    bool next_widget_updated = false;
    auto next_itr = widgets.begin();
    auto new_y = 0;
    for (auto it = widgets.begin(); it != widgets.end(); ++it) {
        QWidget* w = *it;
        if (w->y() > drop_point.y()) {
            if (!next_widget_updated) {
                next_itr = it;
                new_y = w->y();
                next_widget_updated = true;
            }

            QPoint new_pos(this->min_x_pos, w->y() + dropped_widget->height() + this->spacing);
            w->move(new_pos);
        }
    }

    if (!next_widget_updated) {
        // drop at end of widget ordering
        // maybe compute y_offset in a seperate pass, maybe not?
        QPoint new_pos(this->min_x_pos, this->y_offset);
        dropped_widget->move(new_pos);
        widgets.push_back(dropped_widget);
    } else {
        widgets.insert(next_itr, dropped_widget);
        QPoint new_pos(this->min_x_pos, new_y);
        dropped_widget->move(new_pos);
    }

    this->y_offset += dropped_widget->height() + this->spacing;
}

void Tab::handleWidgetDragStart(QWidget* dragged_widget, QPoint drag_point) {
    this->y_offset -= dragged_widget->height() + this->spacing;
    const auto it = std::find(widgets.begin(), widgets.end(), dragged_widget);
    widgets.erase(it);

    for (auto w : widgets) {
        if (w->y() > drag_point.y()) {
            QPoint new_pos(QPoint(this->min_x_pos, w->y() - this->spacing - dragged_widget->height()));
            w->move(new_pos);
        }
    }
}
