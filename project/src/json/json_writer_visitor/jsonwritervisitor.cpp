#include "jsonwritervisitor.h"

QJsonObject JsonWriterVisitor::getJsonObject() const {
    return object;
}

// sensor

void JsonWriterVisitor::visit(const WaterSensor& _sensor) {
    object.insert("type", QJsonValue::fromVariant(_sensor.getTypeName().c_str()));
    object.insert("id", QJsonValue::fromVariant(_sensor.getId()));
    object.insert("name", QJsonValue::fromVariant(_sensor.getName().c_str()));
    object.insert("maxRecycledWaterPerc", QJsonValue::fromVariant(_sensor.getMaxRecyledWaterPerc()));
    object.insert("unitOfMeasurement", QJsonValue::fromVariant(_sensor.getUnitOfMeasurement().c_str()));
    JsonWriterVisitor visitor;
    _sensor.getDistribution()->accept(visitor);
    object["distribution"] = visitor.getJsonObject();
}

void JsonWriterVisitor::visit(const LightSensor& _sensor) {
    object.insert("type", QJsonValue::fromVariant(_sensor.getTypeName().c_str()));
    object.insert("id", QJsonValue::fromVariant(_sensor.getId()));
    object.insert("name", QJsonValue::fromVariant(_sensor.getName().c_str()));
    object.insert("sunriseHour", QJsonValue::fromVariant(_sensor.getSunriseHour()));
    object.insert("sunsetHour", QJsonValue::fromVariant(_sensor.getSunsetHour()));
    object.insert("dailyMinLight", QJsonValue::fromVariant(_sensor.getDailyMinLight()));
    object.insert("unitOfMeasurement", QJsonValue::fromVariant(_sensor.getUnitOfMeasurement().c_str()));
    JsonWriterVisitor visitor;
    _sensor.getDistribution()->accept(visitor);
    object["distribution"] = visitor.getJsonObject();
}

void JsonWriterVisitor::visit(const HeatSensor& _sensor) {
    object.insert("type", QJsonValue::fromVariant(_sensor.getTypeName().c_str()));
    object.insert("id", QJsonValue::fromVariant(_sensor.getId()));
    object.insert("name", QJsonValue::fromVariant(_sensor.getName().c_str()));
    object.insert("minAllowedTemp", QJsonValue::fromVariant(_sensor.getMinAllowedTemp()));
    object.insert("maxAllowedTemp", QJsonValue::fromVariant(_sensor.getMaxAllowedTemp()));
    object.insert("unitOfMeasurement", QJsonValue::fromVariant(_sensor.getUnitOfMeasurement().c_str()));
    JsonWriterVisitor visitor;
    _sensor.getDistribution()->accept(visitor);
    object["distribution"] = visitor.getJsonObject();
}

// distribution

void JsonWriterVisitor::visit(const UniformDistribution& _distribution) {
    object.insert("type", QJsonValue::fromVariant(_distribution.getTypeName().c_str()));
    object.insert("hours", QJsonValue::fromVariant(_distribution.getHours()));
    object.insert("min", QJsonValue::fromVariant(_distribution.getMin()));
    object.insert("max", QJsonValue::fromVariant(_distribution.getMax()));
    object.insert("maxDelta", QJsonValue::fromVariant(_distribution.getMaxDelta()));
}

void JsonWriterVisitor::visit(const NormalDistribution& _distribution) {
    object.insert("type", QJsonValue::fromVariant(_distribution.getTypeName().c_str()));
    object.insert("hours", QJsonValue::fromVariant(_distribution.getHours()));
    object.insert("min", QJsonValue::fromVariant(_distribution.getMin()));
    object.insert("max", QJsonValue::fromVariant(_distribution.getMax()));
    object.insert("mean", QJsonValue::fromVariant(_distribution.getMean()));
    object.insert("stddev", QJsonValue::fromVariant(_distribution.getStddev()));
}

void JsonWriterVisitor::visit(const ExponentialDistribution& _distribution) {
    object.insert("type", QJsonValue::fromVariant(_distribution.getTypeName().c_str()));
    object.insert("hours", QJsonValue::fromVariant(_distribution.getHours()));
    object.insert("min", QJsonValue::fromVariant(_distribution.getMin()));
    object.insert("max", QJsonValue::fromVariant(_distribution.getMax()));
    object.insert("lambda", QJsonValue::fromVariant(_distribution.getLambda()));
}
