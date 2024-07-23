#ifndef SENSOR_SET_VISITOR_H
#define SENSOR_SET_VISITOR_H

#include "../../../../logic/sensor/interfaces/isensorvisitor.h"
#include "../../../../logic/sensor/sensortypes/watersensor.h"
#include "../../../../logic/sensor/sensortypes/lightsensor.h"
#include "../../../../logic/sensor/sensortypes/heatsensor.h"

class SensorSetVisitor : public ISensorVisitor {
    private:
        std::string name;
        std::vector<double> params;
    
    public:
        SensorSetVisitor(const std::string&, const std::vector<double>&);

        void visit(WaterSensor&) override;
        void visit(LightSensor&) override;
        void visit(HeatSensor&) override;
};

#endif
