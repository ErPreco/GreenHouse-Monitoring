#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include "upperbar.h"
#include "toolbar.h"
#include "mainpanel.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
    
    public:
        MainWindow(QApplication&);
};

#endif
