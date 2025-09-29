#ifndef TAB_H
#define TAB_H

#include <QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QScrollArea>
#include "ui_floblox.h"

class Tab : public QWidget
{
    QGridLayout* grid_layout;
    QScrollArea* scroll_area;
    QWidget* scroll_area_widget_contents;
    std::vector<QWidget*> widgets;
    Ui::FlobloxClass ui;

    void spawnWidgetsMenu(const QPoint &pos);
    void spawnFunctionCallWidget();

    Q_OBJECT
public:
    explicit Tab(Ui::FlobloxClass ui, QWidget *parent = nullptr);
    uint y_offset;
    const uint x = 10;

signals:
};

#endif // TAB_H
