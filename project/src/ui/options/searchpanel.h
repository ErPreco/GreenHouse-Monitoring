#ifndef SEARCH_PANEL_H
#define SEARCH_PANEL_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include "../../logic/sensor/sensorsmanager.h"
#include "../../logic/sensor/sensor.h"
#include "filter_visitor/filtervisitor.h"

class SearchPanel : public QWidget {
    Q_OBJECT

    private:
        QLineEdit* nameInputField;
        QCheckBox* caseSensitiveCheckBox;
        
        QCheckBox* waterCheckBox;
        QCheckBox* lightCheckBox;
        QCheckBox* heatCheckBox;

        QCheckBox* uniformCheckBox;
        QCheckBox* normalCheckBox;
        QCheckBox* exponentialCheckBox;

        std::vector<Sensor*> filteredSensors;
        FilterVisitor visitor;

    private slots:
        void searchSensor();

    public:
        SearchPanel();

        std::vector<Sensor*> getFilteredSensors() const;
        FilterVisitor getFilterVisitor() const;
};

#endif
