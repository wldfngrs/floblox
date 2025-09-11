#include "floblox.h"

Floblox::Floblox(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.scrollArea->setContextMenuPolicy(Qt::CustomContextMenu);
}

Floblox::~Floblox()
{}

void Floblox::on_scrollArea_customContextMenuRequested(const QPoint &pos)
{
    QMenu menu(ui.scrollArea);
    menu.addAction(ui.actionInput);
    menu.addAction(ui.menuOutput->menuAction());
    menu.exec(ui.scrollArea->mapToGlobal(pos));
}
