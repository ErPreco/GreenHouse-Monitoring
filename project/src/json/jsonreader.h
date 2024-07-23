#ifndef JSON_READER_H
#define JSON_READER_H

#include <QJsonObject>
#include "../logic/sensor/sensortypes/watersensor.h"
#include "../logic/sensor/sensortypes/lightsensor.h"
#include "../logic/sensor/sensortypes/heatsensor.h"
#include "../logic/distribution/distributiontypes/uniformdistribution.h"
#include "../logic/distribution/distributiontypes/normaldistribution.h"
#include "../logic/distribution/distributiontypes/exponentialdistribution.h"

// Returns the sensor instantiated by the given json object.
Sensor* readSensor(const QJsonObject&);

#endif
