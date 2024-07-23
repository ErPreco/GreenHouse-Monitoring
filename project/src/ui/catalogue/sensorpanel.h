#ifndef SENSOR_PANEL_H
#define SENSOR_PANEL_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPixmap>
#include <QPaintEvent>
#include <QStyleOption>
#include <QPainter>
#include <QString>
#include "infopanel.h"
#include "../../logic/sensor/sensorsmanager.h"
#include "../../json/jsonmanager.h"
#include "../../logic/sensor/sensor.h"
#include "modification/modificationpanel.h"

class SensorPanel : public QWidget {
    Q_OBJECT
    
    private:
        Sensor& sensor;
        ModificationPanel* modificationPanel;

    private slots:
        void removeSensor();
        void startSimulation();
        void openModificationPanel();
    
    public:
        SensorPanel(Sensor&, ModificationPanel*);

        void paintEvent(QPaintEvent*) override;
};

#endif
