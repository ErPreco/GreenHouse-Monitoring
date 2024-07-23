#include "modificationpanel.h"

ModificationPanel::ModificationPanel() = default;

void ModificationPanel::openDialog(Sensor* _sensor) {
    sensor = _sensor;
    dialog = new QDialog();
    dialog->setWindowTitle("Modification window");
    layout = new QVBoxLayout(dialog);
    layout->setAlignment(Qt::AlignTop);

    // name input field
    QHBoxLayout* nameLayout = new QHBoxLayout();
    nameLayout->setSpacing(20);
    layout->addLayout(nameLayout);
    nameLayout->addWidget(new QLabel("Sensor name"));
    nameLayout->addStretch();
    nameInputField = new QLineEdit(QString::fromStdString(_sensor->getName()));
    nameInputField->setMaxLength(Sensor::getNameMaxLength());
    nameInputField->setFixedWidth(150);
    nameLayout->addWidget(nameInputField);

    // sensor custom fields
    _sensor->accept(sensorVisitor);
    layout->addLayout(sensorVisitor.getLayout());

    // distribution type
    QHBoxLayout* typeLayout = new QHBoxLayout();
    layout->addLayout(typeLayout);
    typeLayout->addWidget(new QLabel("Distribution type"));
    typeLayout->addStretch();
    typeField = new QComboBox();
    typeField->setStyleSheet("background-color:white; color:black");
    typeField->addItem("Uniform");
    typeField->addItem("Normal");
    typeField->addItem("Exponential");
    typeField->setCurrentText(QString::fromStdString(_sensor->getDistribution()->getTypeName()));
    connect(typeField, &QComboBox::currentTextChanged, this, &ModificationPanel::changeCustomFields);
    typeLayout->addWidget(typeField);

    // hours
    QHBoxLayout* hoursLayout = new QHBoxLayout();
    hoursLayout->setAlignment(Qt::AlignHCenter);
    hoursLayout->setSpacing(20);
    layout->addLayout(hoursLayout);
    hoursLayout->addWidget(new QLabel("Hours"));
    hoursLayout->addStretch();
    // minus button
    QPushButton* minusBtn = new QPushButton();
    minusBtn->setIcon(QIcon(":/minusicon"));
    minusBtn->setFixedSize(20, 20);
    connect(minusBtn, &QPushButton::pressed, this, &ModificationPanel::decreaseHoursField);
    hoursLayout->addWidget(minusBtn);
    // counter label
    hoursLabel = new QLabel();
    hoursLabel->setText(QString::number(_sensor->getDistribution()->getHours()));
    hoursLayout->addWidget(hoursLabel);
    // plus button
    QPushButton* plusBtn = new QPushButton();
    plusBtn->setIcon(QIcon(":/plusicon"));
    plusBtn->setFixedSize(20, 20);
    connect(plusBtn, &QPushButton::pressed, this, &ModificationPanel::increaseHoursField);
    hoursLayout->addWidget(plusBtn);

    // min
    QHBoxLayout* minLayout = new QHBoxLayout();
    layout->addLayout(minLayout);
    minLayout->addWidget(new QLabel("Min"));
    minLayout->addStretch();
    minInputField = new QLineEdit(QString::number(_sensor->getDistribution()->getMin()));
    minInputField->setValidator(new QDoubleValidator());
    minInputField->setMaxLength(5);
    minInputField->setFixedWidth(50);
    minLayout->addWidget(minInputField);

    // max
    QHBoxLayout* maxLayout = new QHBoxLayout();
    layout->addLayout(maxLayout);
    maxLayout->addWidget(new QLabel("Max"));
    maxLayout->addStretch();
    maxInputField = new QLineEdit(QString::number(_sensor->getDistribution()->getMax()));
    maxInputField->setValidator(new QDoubleValidator());
    maxInputField->setMaxLength(5);
    maxInputField->setFixedWidth(50);
    maxLayout->addWidget(maxInputField);

    // save button
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->setAlignment(Qt::AlignHCenter);
    layout->addLayout(buttonLayout);
    QPushButton* saveBtn = new QPushButton("save");
    saveBtn->setStyleSheet("background-color:white");
    saveBtn->setMaximumWidth(100);
    buttonLayout->addWidget(saveBtn);
    connect(saveBtn, &QPushButton::pressed, this, &ModificationPanel::save);

    // distribution custom fields
    customFieldsLayout = nullptr;
    // inserts custom fields before last element
    changeCustomFields(QString::fromStdString(_sensor->getDistribution()->getTypeName()));

    dialog->setModal(true);
    dialog->exec();
    dialog->deleteLater();
}

void ModificationPanel::clearLayout(QLayout* _layout) {
    QLayoutItem* child;
    while (_layout->count() != 0) {
        child = _layout->takeAt(0);
        if (child->layout() != 0)
            clearLayout(child->layout());
        else if (child->widget() != 0)
            delete child->widget();
        delete child;
    }
}

void ModificationPanel::increaseHoursField() {
    if (auto v = hoursLabel->text().toUInt(); v < 24)
        hoursLabel->setText(QString::number(v + 1));
}

void ModificationPanel::decreaseHoursField() {
    if (auto v = hoursLabel->text().toUInt(); v > 1)
        hoursLabel->setText(QString::number(v - 1));
}

void ModificationPanel::changeCustomFields(const QString& _text) {
    if (customFieldsLayout == nullptr) {
        distribution = sensor->getDistribution();
    } else {
        clearLayout(customFieldsLayout);
        delete customFieldsLayout;
        static_cast<QDialog*>(layout->parent())->adjustSize();
        if (_text == QString::fromStdString(sensor->getDistribution()->getTypeName())) {
            // displays current values if the type selected is the current distibution
            distribution = sensor->getDistribution();
        } else {
            if (distribution != sensor->getDistribution())
                delete distribution;
            // displays default values if the type selected is not the current distribution
            std::map<std::string, std::any> params = SensorsManager::instance()->getDistributionsDefaultParams()[sensor->getTypeName()];
            if (_text == "Uniform")
                distribution = new UniformDistribution(std::any_cast<double>(params["min"]), std::any_cast<double>(params["max"]));
            else if (_text == "Normal")
                distribution = new NormalDistribution(std::any_cast<double>(params["min"]), std::any_cast<double>(params["max"]), std::any_cast<double>(params["normalMean"]), std::any_cast<double>(params["normalStddev"]));
            else if (_text == "Exponential")
                distribution = new ExponentialDistribution(std::any_cast<double>(params["min"]), std::any_cast<double>(params["max"]), std::any_cast<double>(params["exponentialLambda"]));
            else
                throw DistributionTypeNotFound("\"" + _text.toStdString() + "\" not found when attempting to update modification panel");
        }
    }

    distribution->accept(distributionVisitor);
    customFieldsLayout = distributionVisitor.getLayout();
    // inserts the custom layout above the save button
    layout->insertLayout(layout->count() - 1, customFieldsLayout);
}

void ModificationPanel::save() {
    std::vector<double> values;
    // sensor params check
    for (auto field : sensorVisitor.getFields())
        values.push_back(field->text().toDouble());
    try {
        std::string name = nameInputField->text().trimmed().toStdString();
        sensor->validParams(name, values);
        SensorSetVisitor setVisitor(name, values);
        sensor->accept(setVisitor);
    } catch (InvalidSensorParams e) {
        CriticalMessageLog criticalMessageLog(QString::fromStdString(e.getMessage()), "Invalid sensor params");
        criticalMessageLog.showMessage();
        return;
    }

    values.clear();
    // distribution params check
    values.push_back(hoursLabel->text().toDouble());
    values.push_back(minInputField->text().toDouble());
    values.push_back(maxInputField->text().toDouble());
    for (auto field : distributionVisitor.getFields())
        values.push_back(field->text().toDouble());
    try {
        distribution->validParams(values);
        DistributionSetVisitor setVisitor(values);
        const_cast<Distribution*>(distribution)->accept(setVisitor);
        sensor->setDistribution(distribution);
    } catch (InvalidDistributionParams e) {
        CriticalMessageLog criticalMessageLog(QString::fromStdString(e.getMessage()), "Invalid distribution params");
        criticalMessageLog.showMessage();
        return;
    }

    dialog->accept();
    sensor->modified();
    JsonManager::instance()->setIsModified(true);
}
