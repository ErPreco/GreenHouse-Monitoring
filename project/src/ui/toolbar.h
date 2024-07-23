#ifndef ACTIONS_BAR_H
#define ACTIONS_BAR_H

#include <QWidget>
#include <QFileDialog>
#include <QString>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QPaintEvent>
#include <QStyleOption>
#include <QPainter>
#include "../json/jsonmanager.h"
#include "../logic/sensor/sensorsmanager.h"
#include "log/criticalmessagelog.h"
#include "log/warningmessagelog.h"

class ToolBar : public QWidget {
    Q_OBJECT

    private slots:
        void openSaveDialog();
        void openLoadDialog();

    public:
        ToolBar();

        void paintEvent(QPaintEvent*) override;
};

#endif
