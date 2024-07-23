#ifndef MODIFICATION_PANEL_H
#define MODIFICATION_PANEL_H

#include <QWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include "../../../logic/sensor/sensor.h"
#include "../../../logic/sensor/interfaces/isensorobserver.h"
#include "../../../logic/sensor/sensorsmanager.h"
#include "../../../json/jsonmanager.h"
#include "info_visitors/sensorinfovisitor.h"
#include "set_visitors/sensorsetvisitor.h"
#include "info_visitors/distributioninfovisitor.h"
#include "set_visitors/distributionsetvisitor.h"
#include "../../log/criticalmessagelog.h"

class ModificationPanel : public QWidget {
    Q_OBJECT

    private:
        Sensor* sensor;
        SensorInfoVisitor sensorVisitor;
        const Distribution* distribution;
        DistributionInfoVisitor distributionVisitor;

        QDialog* dialog;
        QVBoxLayout* layout;
        QLineEdit* nameInputField;
        QComboBox* typeField;
        QLabel* hoursLabel;
        QLineEdit* minInputField;
        QLineEdit* maxInputField;
        QLayout* customFieldsLayout;
    
        void clearLayout(QLayout*);

    private slots:
        void increaseHoursField();
        void decreaseHoursField();
        void changeCustomFields(const QString&);
        void save();

    public:
        ModificationPanel();

        void openDialog(Sensor*);
};

#endif
