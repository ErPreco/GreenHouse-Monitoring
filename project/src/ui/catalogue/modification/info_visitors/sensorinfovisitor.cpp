#include "sensorinfovisitor.h"

QVBoxLayout* SensorInfoVisitor::getLayout() const {
    return layout;
}

std::vector<QLineEdit*> SensorInfoVisitor::getFields() const {
    return fields;
}

void SensorInfoVisitor::visit(const WaterSensor& _sensor) {
    layout = new QVBoxLayout();
    fields.clear();

    QHBoxLayout* sunriseHourLayout = new QHBoxLayout();
    layout->addLayout(sunriseHourLayout);
    sunriseHourLayout->addWidget(new QLabel("Max recycled water perc"));
    sunriseHourLayout->addStretch();
    QLineEdit* sunriseHourInputField = new QLineEdit(QString::number(_sensor.getMaxRecyledWaterPerc()));
    sunriseHourInputField->setValidator(new QDoubleValidator());
    sunriseHourInputField->setMaxLength(5);
    sunriseHourInputField->setFixedWidth(50);
    sunriseHourLayout->addWidget(sunriseHourInputField);
    fields.push_back(sunriseHourInputField);
}

void SensorInfoVisitor::visit(const LightSensor& _sensor) {
    layout = new QVBoxLayout();
    fields.clear();

    QHBoxLayout* sunriseHourLayout = new QHBoxLayout();
    layout->addLayout(sunriseHourLayout);
    sunriseHourLayout->addWidget(new QLabel("Sunrise hour"));
    sunriseHourLayout->addStretch();
    QLineEdit* sunriseHourInputField = new QLineEdit(QString::number(_sensor.getSunriseHour()));
    sunriseHourInputField->setValidator(new QIntValidator());
    sunriseHourInputField->setMaxLength(5);
    sunriseHourInputField->setFixedWidth(50);
    sunriseHourLayout->addWidget(sunriseHourInputField);
    fields.push_back(sunriseHourInputField);

    QHBoxLayout* sunsetHourLayout = new QHBoxLayout();
    layout->addLayout(sunsetHourLayout);
    sunsetHourLayout->addWidget(new QLabel("Sunset hour"));
    sunsetHourLayout->addStretch();
    QLineEdit* sunsetHourInputField = new QLineEdit(QString::number(_sensor.getSunsetHour()));
    sunsetHourInputField->setValidator(new QIntValidator());
    sunsetHourInputField->setMaxLength(5);
    sunsetHourInputField->setFixedWidth(50);
    sunsetHourLayout->addWidget(sunsetHourInputField);
    fields.push_back(sunsetHourInputField);

    QHBoxLayout* dailyMinLightLayout = new QHBoxLayout();
    layout->addLayout(dailyMinLightLayout);
    dailyMinLightLayout->addWidget(new QLabel("Daily min light"));
    dailyMinLightLayout->addStretch();
    QLineEdit* dailyMinLightInputField = new QLineEdit(QString::number(_sensor.getDailyMinLight()));
    dailyMinLightInputField->setValidator(new QDoubleValidator());
    dailyMinLightInputField->setMaxLength(5);
    dailyMinLightInputField->setFixedWidth(50);
    dailyMinLightLayout->addWidget(dailyMinLightInputField);
    fields.push_back(dailyMinLightInputField);
}

void SensorInfoVisitor::visit(const HeatSensor& _sensor) {
    layout = new QVBoxLayout();
    fields.clear();

    QHBoxLayout* minAllowedTempLayout = new QHBoxLayout();
    layout->addLayout(minAllowedTempLayout);
    minAllowedTempLayout->addWidget(new QLabel("Min allowed temperature"));
    minAllowedTempLayout->addStretch();
    QLineEdit* minAllowedTempInputField = new QLineEdit(QString::number(_sensor.getMinAllowedTemp()));
    minAllowedTempInputField->setValidator(new QDoubleValidator());
    minAllowedTempInputField->setMaxLength(5);
    minAllowedTempInputField->setFixedWidth(50);
    minAllowedTempLayout->addWidget(minAllowedTempInputField);
    fields.push_back(minAllowedTempInputField);

    QHBoxLayout* maxAllowedTempLayout = new QHBoxLayout();
    layout->addLayout(maxAllowedTempLayout);
    maxAllowedTempLayout->addWidget(new QLabel("Max allowed temperature"));
    maxAllowedTempLayout->addStretch();
    QLineEdit* maxAllowedTempInputField = new QLineEdit(QString::number(_sensor.getMaxAllowedTemp()));
    maxAllowedTempInputField->setValidator(new QDoubleValidator());
    maxAllowedTempInputField->setMaxLength(5);
    maxAllowedTempInputField->setFixedWidth(50);
    maxAllowedTempLayout->addWidget(maxAllowedTempInputField);
    fields.push_back(maxAllowedTempInputField);
}
