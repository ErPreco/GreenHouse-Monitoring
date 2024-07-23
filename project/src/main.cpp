#include <QApplication>
#include "ui/mainwindow.h"

int main(int _argc, char* _argv[]) {
    QApplication app(_argc, _argv);
    
    MainWindow mainWindow(app);
    mainWindow.setWindowState(Qt::WindowMaximized);
    mainWindow.show();
    
    return app.exec();
}
