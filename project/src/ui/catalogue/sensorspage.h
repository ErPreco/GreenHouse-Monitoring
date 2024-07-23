#ifndef SENSORS_PAGE_H
#define SENSORS_PAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <vector>
#include "sensorpanel.h"

class SensorsPage : public QWidget {
    Q_OBJECT

    private:
        std::vector<SensorPanel*> sensorPanels;
        QVBoxLayout* layout;

    public:
        SensorsPage();

        std::vector<const SensorPanel*> getSensorPanels() const;

        bool isEmpty() const;
        unsigned int sensorPanelsCount() const;
        void addSensorPanel(SensorPanel*);
        // Takes panels back one to the (shiftedSensorPanelIdx)th panel, returns it and push the given panel in last position.
        SensorPanel* updatePage(unsigned int, SensorPanel*);
};

#endif
