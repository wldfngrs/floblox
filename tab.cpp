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
    // open to modification thanks to https://chatgpt.com/s/t_68de802add0c8191b8a9f8664e58dda0
    auto iter = 0;
    auto min = 0;
    // get seed min value
    for (; iter < widgets.size(); iter++) {
        if (widgets[iter]->y() >= drop_point.y() && (!dynamic_cast<FunctionCall*>(widgets[iter])->dragging)) {
            min = widgets[iter]->y();
            QPoint new_pos(QPoint(this->min_x_pos, widgets[iter]->y() + dropped_widget->height() + this->spacing));
            widgets[iter]->move(new_pos);
            break;
        }
    }

    // check if any other subsequent values are less than seed min to find true min
    for (++iter; iter < widgets.size(); iter++) {
        if (widgets[iter]->y() >= drop_point.y() && (!dynamic_cast<FunctionCall*>(widgets[iter])->dragging)) {
            if (widgets[iter]->y() < min) {
                min = widgets[iter]->y();
            }
            QPoint new_pos(QPoint(this->min_x_pos, widgets[iter]->y() + dropped_widget->height() + this->spacing));
            widgets[iter]->move(new_pos);
        }
    }

    if (min != 0) {
        if (drop_point.y() < this->min_y_pos) {
            // drop point is at the top of the existing widget ordering
            QPoint new_pos(QPoint(this->min_x_pos, this->min_y_pos));
            dropped_widget->move(new_pos);
        } else {
            // drop point is at an arbitrary position within the existing widget ordering
            QPoint new_pos(QPoint(this->min_x_pos, min));
            dropped_widget->move(new_pos);
        }
    } else {
        // drop point is at the end of the widgets ordering
        QPoint new_pos(QPoint(this->min_x_pos, this->y_offset));
        dropped_widget->move(new_pos);
    }

    this->y_offset += dropped_widget->height() + this->spacing;
}

void Tab::handleWidgetDragStart(QWidget* dragged_widget, QPoint drag_point) {
    this->y_offset -= dragged_widget->height() + this->spacing;
    for (auto w : widgets) {
        if (w->y() > drag_point.y() && (!dynamic_cast<FunctionCall*>(w)->dragging)) {
            QPoint new_pos(QPoint(this->min_x_pos, w->y() - this->spacing - dragged_widget->height()));
            w->move(new_pos);
        }
    }
}
