#include "floblox.h"
#include "tab.h"

Floblox::Floblox(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    // clear default created tabs
    while (ui.tabWidget->count() > 0) {
        QWidget *page = ui.tabWidget->widget(0);
        ui.tabWidget->removeTab(0);
        delete page;
    }
    ui.tabWidget->addTab(new Tab(ui), "Main");
    //canvas_layout = new QVBoxLayout(ui.scrollArea);
    //QObject::connect(ui.actionFunction_Call, &QAction::triggered, this, &Floblox::spawnFunctionCallWidget);
}

Floblox::~Floblox()
{}
