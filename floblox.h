#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_floblox.h"

class Floblox : public QMainWindow
{
    Q_OBJECT

public:
    Floblox(QWidget *parent = nullptr);
    ~Floblox();

private slots:
    void on_scrollArea_customContextMenuRequested(const QPoint &pos);

private:
    Ui::FlobloxClass ui;
};
