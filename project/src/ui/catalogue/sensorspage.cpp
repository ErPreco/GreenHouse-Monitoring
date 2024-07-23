#include "sensorspage.h"

SensorsPage::SensorsPage() : layout(new QVBoxLayout(this)) {
    layout->setAlignment(Qt::AlignTop);
    layout->setSpacing(10);
    layout->setContentsMargins(10, 0, 10, 0);
}

std::vector<const SensorPanel*> SensorsPage::getSensorPanels() const {
    std::vector<const SensorPanel*> v;
    for (auto p : sensorPanels)
        v.push_back(p);
    return v;
}

bool SensorsPage::isEmpty() const {
    return sensorPanels.empty();
}

unsigned int SensorsPage::sensorPanelsCount() const {
    return sensorPanels.size();
}

void SensorsPage::addSensorPanel(SensorPanel* _sensorPanel) {
    sensorPanels.push_back(_sensorPanel);
    layout->addWidget(_sensorPanel);
}

SensorPanel* SensorsPage::updatePage(unsigned int _shiftedSensorPanelIdx, SensorPanel* _sensorPanel) {
    SensorPanel* shiftedSensorPanel = sensorPanels[_shiftedSensorPanelIdx];
    layout->removeWidget(shiftedSensorPanel);
    while (++_shiftedSensorPanelIdx < sensorPanels.size())
        sensorPanels[_shiftedSensorPanelIdx - 1] = sensorPanels[_shiftedSensorPanelIdx];
    
    if (_sensorPanel != nullptr) {
        sensorPanels[--_shiftedSensorPanelIdx] = _sensorPanel;
        layout->addWidget(_sensorPanel);
    } else
        sensorPanels.pop_back();
    
    return shiftedSensorPanel;
}
