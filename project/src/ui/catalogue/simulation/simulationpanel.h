#ifndef SIMULATION_PANEL_H
#define SIMULATION_PANEL_H

#include <QWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QtCharts>
#include <QLineSeries>
#include <QLabel>
#include "../../../logic/sensor/sensor.h"
#include "../../../logic/sensor/interfaces/isensorobserver.h"
#include "visitor/simulationvisitor.h"

class SimulationPanel : public QWidget, public ISensorObserver {
    Q_OBJECT

    public:
        SimulationPanel();

        void notifySimulation(Sensor&) override;
        void notifyModification(const Sensor&) override;
};

#endif
