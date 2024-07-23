#ifndef INFO_PANEL_H
#define INFO_PANEL_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include "../../logic/sensor/sensor.h"
#include "../../logic/sensor/interfaces/isensorobserver.h"

class InfoPanel : public QWidget, public ISensorObserver {
    Q_OBJECT

    private:
        Sensor& sensor;

        QLabel* name;
        QLabel* distribution;

    public:
        InfoPanel(Sensor&);

        void notifySimulation(Sensor&) override;
        void notifyModification(const Sensor&) override;
};

#endif
