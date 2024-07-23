#ifndef I_SENSOR_VISITOR_H
#define I_SENSOR_VISITOR_H

class WaterSensor;
class LightSensor;
class HeatSensor;

class ISensorVisitor {
    public:
        virtual ~ISensorVisitor() = default;

        virtual void visit(WaterSensor&) = 0;
        virtual void visit(LightSensor&) = 0;
        virtual void visit(HeatSensor&) = 0;
};

#endif
