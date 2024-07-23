#ifndef SIMULATION_VISITOR_H
#define SIMULATION_VISITOR_H

#include <QtCharts>
#include <QValueAxis>
#include <QLineSeries>
#include <QBarSet>
#include <QBarSeries>
#include <QLabel>
#include "../../../../logic/sensor/interfaces/isensorvisitor.h"
#include "../../../../logic/sensor/sensortypes/watersensor.h"
#include "../../../../logic/sensor/sensortypes/lightsensor.h"
#include "../../../../logic/sensor/sensortypes/heatsensor.h"

class SimulationVisitor : public ISensorVisitor {
    private:
        QChart* chart;
        QValueAxis* axisX;
        QValueAxis* axisY;
        QLabel* label;

        void setInfo(const QString&);
        void setWarning(const QString&);

    public:
        SimulationVisitor(QChart*, QValueAxis*, QValueAxis*, QLabel*);

        void visit(WaterSensor&) override;
        void visit(LightSensor&) override;
        void visit(HeatSensor&) override;
};

#endif
