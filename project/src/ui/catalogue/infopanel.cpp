#include "infopanel.h"

InfoPanel::InfoPanel(Sensor& _sensor) : sensor(_sensor), name(new QLabel()), distribution(new QLabel()) {
    _sensor.registerObserver(this);

    QGridLayout* layout = new QGridLayout(this);
    layout->setContentsMargins(30, 0, 30, 0);
    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 1);

    // sensor name label
    name->setText("Sensor name: " + QString::fromStdString(_sensor.getName()));
    layout->addWidget(name, 0, 0);

    // sensor type label
    QLabel* type = new QLabel("Sensor type: " + QString::fromStdString(_sensor.getTypeName()));
    layout->addWidget(type, 1, 0);

    // sensor id label
    QLabel* id = new QLabel("Sensor ID: " + QString::number(_sensor.getId()));
    layout->addWidget(id, 0, 1);

    // distribution type label
    distribution->setText("Distribution type: " + QString::fromStdString(_sensor.getDistribution()->getTypeName()));
    layout->addWidget(distribution, 1, 1);
}

void InfoPanel::notifySimulation(Sensor&) {}

void InfoPanel::notifyModification(const Sensor& _sensor) {
    name->setText("Sensor name: " + QString::fromStdString(_sensor.getName()));
    distribution->setText("Distribution type: " + QString::fromStdString(_sensor.getDistribution()->getTypeName()));
}
