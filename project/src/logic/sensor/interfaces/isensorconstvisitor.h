#ifndef I_CONST_SENSOR_VISITOR_H
#define I_CONST_SENSOR_VISITOR_H

class WaterSensor;
class LightSensor;
class HeatSensor;

class ISensorConstVisitor {
    public:
        virtual ~ISensorConstVisitor() = default;

        virtual void visit(const WaterSensor&) = 0;
        virtual void visit(const LightSensor&) = 0;
        virtual void visit(const HeatSensor&) = 0;
};

#endif
