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
    this->y_offset = 30;

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
    //QPoint pos = QCursor::pos();
    this->widgets.push_back(new FunctionCall(this->scroll_area_widget_contents, this->y_offset));
    this->y_offset += this->widgets[this->widgets.size() - 1]->height() + 10;
}
