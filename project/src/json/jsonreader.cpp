#include "jsonreader.h"

// sensor

Sensor* readWaterSensor(const QJsonObject& _object) {
    Sensor* sensor = new WaterSensor(
        nullptr,
        _object.value("maxRecycledWaterPerc").toDouble(),
        _object.value("unitOfMeasurement").toString().toStdString(),
        _object.value("name").toString().toStdString()
    );
    return sensor;
}

Sensor* readLightSensor(const QJsonObject& _object) {
    Sensor* sensor = new LightSensor(
        nullptr,
        _object.value("sunriseHour").toInt(),
        _object.value("sunsetHour").toInt(),
        _object.value("dailyMinLight").toDouble(),
        _object.value("unitOfMeasurement").toString().toStdString(),
        _object.value("name").toString().toStdString()
    );
    return sensor;
}

Sensor* readHeatSensor(const QJsonObject& _object) {
    Sensor* sensor = new HeatSensor(
        nullptr,
        _object.value("minAllowedTemp").toDouble(),
        _object.value("maxAllowedTemp").toDouble(),
        _object.value("unitOfMeasurement").toString().toStdString(),
        _object.value("name").toString().toStdString()
    );
    return sensor;
}

// distribution

Distribution* readUniformDistribution(const QJsonObject& _object) {
    UniformDistribution* distribution = new UniformDistribution(
        _object.value("min").toDouble(),
        _object.value("max").toDouble(),
        _object.value("hours").toInt()
    );
    distribution->setMaxDelta(_object.value("maxDelta").toDouble());
    return distribution;
}

Distribution* readNormalDistribution(const QJsonObject& _object) {
    return new NormalDistribution(
        _object.value("min").toDouble(),
        _object.value("max").toDouble(),
        _object.value("mean").toDouble(),
        _object.value("stddev").toDouble(),
        _object.value("hours").toInt()
    );
}

Distribution* readExponentialDistribution(const QJsonObject& _object) {
    return new ExponentialDistribution(
        _object.value("min").toDouble(),
        _object.value("max").toDouble(),
        _object.value("lambda").toDouble(),
        _object.value("hours").toInt()
    );
}

// reader

Sensor* readSensor(const QJsonObject& _object) {
    Sensor* sensor = nullptr;
    QString type = _object.value("type").toString();
    if (type == "Water")
        sensor = readWaterSensor(_object);
    else if (type == "Light")
        sensor = readLightSensor(_object);
    else if (type == "Heat")
        sensor = readHeatSensor(_object);
    else
        throw SensorTypeNotFound("\"" + type.toStdString() + "\" not found when attempting to read from JSON");
    sensor->setId(_object.value("id").toInt());
    
    type = _object["distribution"]["type"].toString();
    if (type == "Uniform")
        sensor->setDistribution(readUniformDistribution(_object["distribution"].toObject()));
    else if (type == "Normal")
        sensor->setDistribution(readNormalDistribution(_object["distribution"].toObject()));
    else if (type == "Exponential")
        sensor->setDistribution(readExponentialDistribution(_object["distribution"].toObject()));
    else
        throw DistributionTypeNotFound("\"" + type.toStdString() + "\" not found when attempting to read from JSON");

    return sensor;
}
