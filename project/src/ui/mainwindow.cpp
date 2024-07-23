#include "mainwindow.h"

MainWindow::MainWindow(QApplication& _app) {
    QWidget* central = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(central);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    UpperBar* upperBar = new UpperBar(_app);
    layout->addWidget(upperBar);

    ToolBar* actionsBar = new ToolBar();
    layout->addWidget(actionsBar);

    MainPanel* mainPanel = new MainPanel();
    layout->addWidget(mainPanel);

    setCentralWidget(central);
}
