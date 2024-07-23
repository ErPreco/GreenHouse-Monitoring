#ifndef CREATE_PANEL_H
#define CREATE_PANEL_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include "searchpanel.h"
#include "../log/warningmessagelog.h"
#include "../../logic/sensor/sensorsmanager.h"
#include "../../json/jsonmanager.h"
#include "../../logic/distribution/distributiontypes/uniformdistribution.h"
#include "../../logic/distribution/distributiontypes/normaldistribution.h"
#include "../../logic/distribution/distributiontypes/exponentialdistribution.h"
#include "../../logic/sensor/sensortypes/watersensor.h"
#include "../../logic/sensor/sensortypes/lightsensor.h"
#include "../../logic/sensor/sensortypes/heatsensor.h"

class CreatePanel : public QWidget {
    Q_OBJECT

    private:
        QComboBox* sensorTypeField;
        QLineEdit* nameInputField;
        QComboBox* distributionTypeField;

        SearchPanel* searchPanel;

    private slots:
        void createSensor();
    
    public:
        CreatePanel(SearchPanel*);
};

#endif
