#ifndef SENSOR_INFO_VISITOR_H
#define SENSOR_INFO_VISITOR_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QIntValidator>
#include <QString>
#include <vector>
#include "../../../../logic/sensor/interfaces/isensorconstvisitor.h"
#include "../../../../logic/sensor/sensortypes/watersensor.h"
#include "../../../../logic/sensor/sensortypes/lightsensor.h"
#include "../../../../logic/sensor/sensortypes/heatsensor.h"

class SensorInfoVisitor : public ISensorConstVisitor {
    private:
        QVBoxLayout* layout;
        std::vector<QLineEdit*> fields;
    
    public:
        QVBoxLayout* getLayout() const;
        std::vector<QLineEdit*> getFields() const;

        void visit(const WaterSensor&) override;
        void visit(const LightSensor&) override;
        void visit(const HeatSensor&) override;
};

#endif
