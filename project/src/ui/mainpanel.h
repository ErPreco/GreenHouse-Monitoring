#ifndef MAIN_PANEL_H
#define MAIN_PANEL_H

#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include "options/optionspanel.h"
#include "catalogue/cataloguepanel.h"
#include "catalogue/simulation/simulationpanel.h"
#include "catalogue/modification/modificationpanel.h"

class MainPanel : public QWidget {
    Q_OBJECT;

    public:
        MainPanel();
};

#endif
