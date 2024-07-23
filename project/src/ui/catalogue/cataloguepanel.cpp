#include "cataloguepanel.h"

CataloguePanel::CataloguePanel(SimulationPanel* _simulationPanel, ModificationPanel* _modificationPanel, unsigned int _sensorsPerPage)
: simulationPanel(_simulationPanel), pageControllerPanel(new PageControllerPanel()), modificationPanel(_modificationPanel), sensorsPerPage(_sensorsPerPage), curPageIdx(0), layout(new QVBoxLayout(this)) {
    setStyleSheet("background-color:#F6FFF7");

    layout->setAlignment(Qt::AlignTop);
    layout->setSpacing(10);
    layout->setContentsMargins(0, 0, 0, 0);

    // page controller bar displaied on top
    connect(pageControllerPanel, &PageControllerPanel::changePage, this, &CataloguePanel::changePage);
    layout->addWidget(pageControllerPanel);

    SensorsManager::instance()->registerObserver(this);
}

void CataloguePanel::createCatalogue(const std::vector<Sensor*>& _sensors) {
    if (_sensors.size() == 0) {
        pageControllerPanel->setPagesCount(1);
        pageControllerPanel->setPageIndicator(1);
        return;
    }

    for (unsigned int i = 0; i < _sensors.size(); i++) {
        if (i % sensorsPerPage == 0)
            pages.push_back(new SensorsPage());
        SensorPanel* sensorPanel = new SensorPanel(*_sensors[i], modificationPanel);
        pages[i / sensorsPerPage]->addSensorPanel(sensorPanel);
        _sensors[i]->registerObserver(simulationPanel);
    }
    layout->addWidget(pages[0]);
    pageControllerPanel->setPagesCount(pages.size());
    pageControllerPanel->setPageIndicator(1);
}

void CataloguePanel::clearCatalogue() {
    for (auto it = pages.begin(); it != pages.end(); it++)
        delete *it;
    pages.clear();
    std::vector<Sensor*> sensors = SensorsManager::instance()->setSensors();
    for (auto it = sensors.begin(); it != sensors.end(); it++)
        (*it)->unregisterObserver(simulationPanel);
    curPageIdx = 0;
}

void CataloguePanel::notifyCreatedSensor(Sensor& _createdSensor) {
    if (pages.size() == 0) {
        pages.push_back(new SensorsPage());
        layout->addWidget(pages[0]);
    } else if (pages.back()->sensorPanelsCount() % sensorsPerPage == 0) {
        pages.push_back(new SensorsPage());
        pageControllerPanel->updatePagesCount(true);
    }
    SensorPanel* sensorPanel = new SensorPanel(_createdSensor, modificationPanel);
    pages.back()->addSensorPanel(sensorPanel);
    _createdSensor.registerObserver(simulationPanel);
}

void CataloguePanel::notifyRemovedSensor(unsigned int _removedSensorIdx) {
    unsigned int pageIdx = pages.size() - 1;
    SensorPanel* nextSensorPanel = nullptr;
    // updates only the pages over the page with the removed sensor
    while (curPageIdx < pageIdx) {
        nextSensorPanel = pages[pageIdx]->updatePage(0, nextSensorPanel);
        pageIdx--;
    }
    // updates only the panels over the removed sensor
    pages[curPageIdx]->updatePage(_removedSensorIdx % sensorsPerPage, nextSensorPanel);

    // if were on the last page, removes the page and moves back to the previous page
    if (pages.back()->isEmpty()) {
        if (curPageIdx == pages.size() - 1)
            pageControllerPanel->prevPage();
        delete pages.back();
        pages.pop_back();
        pageControllerPanel->updatePagesCount(false);
    }
}

void CataloguePanel::notifyFilteredSensors(const std::vector<Sensor*>& _sensors) {
    clearCatalogue();
    createCatalogue(_sensors);
}

void CataloguePanel::notifyOpenedFile() {
    clearCatalogue();
    createCatalogue(SensorsManager::instance()->setSensors());
}

void CataloguePanel::changePage(bool _prev) {
    layout->removeWidget(pages[curPageIdx]);
    pages[curPageIdx]->setVisible(false);
    curPageIdx += _prev ? -1 : 1;
    layout->addWidget(pages[curPageIdx]);
    pages[curPageIdx]->setVisible(true);
}

void CataloguePanel::paintEvent(QPaintEvent* _event) {
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QWidget::paintEvent(_event);
}
