#include "mainpanel.h"

MainPanel::MainPanel() {
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    OptionsPanel* optionsPanel = new OptionsPanel();
    layout->addWidget(optionsPanel, 3);

    SimulationPanel* simulationPanel = new SimulationPanel();
    ModificationPanel* modificationPanel = new ModificationPanel();

    CataloguePanel* cataloguePanel = new CataloguePanel(simulationPanel, modificationPanel);
    layout->addWidget(cataloguePanel, 7);
}
