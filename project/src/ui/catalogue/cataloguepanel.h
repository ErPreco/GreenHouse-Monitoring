#ifndef CATALOGUE_PANEL_H
#define CATALOGUE_PANEL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPaintEvent>
#include <QPainter>
#include <QStyleOption>
#include <vector>
#include <math.h>
#include "../../logic/sensor/sensorsmanager.h"
#include "sensorpanel.h"
#include "sensorspage.h"
#include "pagecontrollerpanel.h"
#include "simulation/simulationpanel.h"
#include "modification/modificationpanel.h"

class SensorsPage;

class CataloguePanel : public QWidget, public ISensorsManagerObserver {
    Q_OBJECT

    private:
        SimulationPanel* simulationPanel;
        PageControllerPanel* pageControllerPanel;
        ModificationPanel* modificationPanel;

        unsigned int sensorsPerPage;
        std::vector<SensorsPage*> pages;
        unsigned int curPageIdx;

        QVBoxLayout* layout;

        void createCatalogue(const std::vector<Sensor*>&);
        void clearCatalogue();
    
    private slots:
        void changePage(bool);
    
    public:
        CataloguePanel(SimulationPanel*, ModificationPanel*, unsigned int = 5);

        void notifyCreatedSensor(Sensor&) override;
        void notifyRemovedSensor(unsigned int) override;
        void notifyFilteredSensors(const std::vector<Sensor*>&) override;
        void notifyOpenedFile() override;

        void paintEvent(QPaintEvent*) override;
};

#endif
