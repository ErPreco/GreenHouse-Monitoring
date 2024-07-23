#ifndef OPTIONS_PANEL_H
#define OPTIONS_PANEL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPaintEvent>
#include <QStyleOption>
#include <QPainter>
#include "searchpanel.h"
#include "createpanel.h"
#include "../../logic/sensor/sensorsmanager.h"

class OptionsPanel : public QWidget {
    Q_OBJECT

    public:
        OptionsPanel();

        void paintEvent(QPaintEvent*) override;
};

#endif
