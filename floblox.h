#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTabWidget>
#include "ui_floblox.h"

class Floblox : public QMainWindow
{
    Q_OBJECT

public:
    Floblox(QWidget *parent = nullptr);
    ~Floblox();

private slots:

private:
    Ui::FlobloxClass ui;
    QTabWidget *tabWidget;
};
