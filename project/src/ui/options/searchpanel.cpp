#include "searchpanel.h"

SearchPanel::SearchPanel()
: nameInputField(new QLineEdit()), caseSensitiveCheckBox(new QCheckBox()),
waterCheckBox(new QCheckBox()), lightCheckBox(new QCheckBox()), heatCheckBox(new QCheckBox()),
uniformCheckBox(new QCheckBox()), normalCheckBox(new QCheckBox()), exponentialCheckBox(new QCheckBox()),
visitor() {
// sensorVisitor(), distributionVisitor() {
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    layout->setSpacing(20);
    layout->setContentsMargins(20, 10, 20, 10);

    // title
    QHBoxLayout* titleLayout = new QHBoxLayout();
    titleLayout->setAlignment(Qt::AlignHCenter);
    layout->addLayout(titleLayout);
    QLabel* searchText = new QLabel("search");
    searchText->setStyleSheet("font-weight:bold; font-size:22px");
    titleLayout->addWidget(searchText);

    // name input field
    QVBoxLayout* nameLayout = new QVBoxLayout();
    nameLayout->setAlignment(Qt::AlignHCenter);
    nameLayout->setSpacing(10);
    layout->addLayout(nameLayout);

    QHBoxLayout* nameInputFieldLayout = new QHBoxLayout();
    nameInputFieldLayout->setAlignment(Qt::AlignHCenter);
    nameLayout->addLayout(nameInputFieldLayout);
    nameInputField->setStyleSheet("background-color:white");
    nameInputField->setMaxLength(Sensor::getNameMaxLength());
    nameInputField->setPlaceholderText("type...");
    nameInputField->setFixedWidth(200);
    connect(nameInputField, &QLineEdit::textChanged, this, &SearchPanel::searchSensor);
    nameInputFieldLayout->addWidget(nameInputField);

    // case sensitive checkbox
    QString checkedColor = "#6BB564";
    QHBoxLayout* caseSensitiveCheckBoxLayout = new QHBoxLayout();
    caseSensitiveCheckBoxLayout->setAlignment(Qt::AlignHCenter);
    nameLayout->addLayout(caseSensitiveCheckBoxLayout);
    caseSensitiveCheckBox->setText("Case sensitive");
    caseSensitiveCheckBox->setStyleSheet("QCheckBox::indicator{border:1px solid; background-color:white}\
                                QCheckBox::indicator:checked{background-color:" + checkedColor + "}");
    connect(caseSensitiveCheckBox, &QCheckBox::stateChanged, this, &SearchPanel::searchSensor);
    caseSensitiveCheckBoxLayout->addWidget(caseSensitiveCheckBox);

    // sensor type
    QVBoxLayout* sensorTypeLayout = new QVBoxLayout();
    sensorTypeLayout->setAlignment(Qt::AlignHCenter);
    sensorTypeLayout->setSpacing(10);
    layout->addLayout(sensorTypeLayout);

    // checkboxes
    sensorTypeLayout->addWidget(new QLabel("Sensor type"));
    QVBoxLayout* sensorCheckBoxesLayout = new QVBoxLayout();
    sensorCheckBoxesLayout->setAlignment(Qt::AlignHCenter);
    sensorTypeLayout->addLayout(sensorCheckBoxesLayout);
    waterCheckBox->setText("Water");
    waterCheckBox->setStyleSheet("QCheckBox::indicator{border:1px solid; background-color:white}\
                                    QCheckBox::indicator:checked{background-color:" + checkedColor + "}");
    connect(waterCheckBox, &QCheckBox::stateChanged, this, &SearchPanel::searchSensor);
    sensorCheckBoxesLayout->addWidget(waterCheckBox);
    lightCheckBox->setText("Light");
    lightCheckBox->setStyleSheet("QCheckBox::indicator{border:1px solid; background-color:white}\
                                    QCheckBox::indicator:checked{background-color:" + checkedColor + "}");
    connect(lightCheckBox, &QCheckBox::stateChanged, this, &SearchPanel::searchSensor);
    sensorCheckBoxesLayout->addWidget(lightCheckBox);
    heatCheckBox->setText("Heat");
    heatCheckBox->setStyleSheet("QCheckBox::indicator{border:1px solid; background-color:white}\
                                    QCheckBox::indicator:checked{background-color:" + checkedColor + "}");
    connect(heatCheckBox, &QCheckBox::stateChanged, this, &SearchPanel::searchSensor);
    sensorCheckBoxesLayout->addWidget(heatCheckBox);

    // distribution type
    QVBoxLayout* distributionTypeLayout = new QVBoxLayout();
    distributionTypeLayout->setAlignment(Qt::AlignHCenter);
    distributionTypeLayout->setSpacing(10);
    layout->addLayout(distributionTypeLayout);

    // checkboxes
    distributionTypeLayout->addWidget(new QLabel("Distribution type"));
    QVBoxLayout* distributionCheckBoxesLayout = new QVBoxLayout();
    distributionCheckBoxesLayout->setAlignment(Qt::AlignHCenter);
    distributionTypeLayout->addLayout(distributionCheckBoxesLayout);
    uniformCheckBox->setText("Uniform");
    uniformCheckBox->setStyleSheet("QCheckBox::indicator{border:1px solid; background-color:white}\
                                    QCheckBox::indicator:checked{background-color:" + checkedColor + "}");
    connect(uniformCheckBox, &QCheckBox::stateChanged, this, &SearchPanel::searchSensor);
    distributionCheckBoxesLayout->addWidget(uniformCheckBox);
    normalCheckBox->setText("Normal");
    normalCheckBox->setStyleSheet("QCheckBox::indicator{border:1px solid; background-color:white}\
                                    QCheckBox::indicator:checked{background-color:" + checkedColor + "}");
    connect(normalCheckBox, &QCheckBox::stateChanged, this, &SearchPanel::searchSensor);
    distributionCheckBoxesLayout->addWidget(normalCheckBox);
    exponentialCheckBox->setText("Exponential");
    exponentialCheckBox->setStyleSheet("QCheckBox::indicator{border:1px solid; background-color:white}\
                                    QCheckBox::indicator:checked{background-color:" + checkedColor + "}");
    connect(exponentialCheckBox, &QCheckBox::stateChanged, this, &SearchPanel::searchSensor);
    distributionCheckBoxesLayout->addWidget(exponentialCheckBox);
}

std::vector<Sensor*> SearchPanel::getFilteredSensors() const {
    return filteredSensors;
}

FilterVisitor SearchPanel::getFilterVisitor() const {
    return visitor;
}

void SearchPanel::searchSensor() {
    // sensor filters
    visitor.setName(nameInputField->text().toStdString());
    visitor.setCaseSensitive(caseSensitiveCheckBox->isChecked());
    visitor.setFilterWater(waterCheckBox->isChecked());
    visitor.setFilterLight(lightCheckBox->isChecked());
    visitor.setFilterHeat(heatCheckBox->isChecked());
    // distribution filters
    visitor.setFilterUniform(uniformCheckBox->isChecked());
    visitor.setFilterNormal(normalCheckBox->isChecked());
    visitor.setFilterExponential(exponentialCheckBox->isChecked());

    filteredSensors.clear();
    for (auto sensor : SensorsManager::instance()->getSensors()) {
        visitor.setIsAllMatch(false);
        visitor.setIsAllMatch(false);

        sensor->accept(visitor);
        sensor->getDistribution()->accept(visitor);
        
        // filter the sensor if the specific checkbox is checked or none of them are
        if (visitor.getIsNameMatch() &&
            (visitor.getIsSensorTypeMatch() || visitor.getIsSensorTypesEmpty()) &&
            (visitor.getIsDistributionTypeMatch() || visitor.getIsDistributionTypesEmpty()))
            filteredSensors.push_back(const_cast<Sensor*>(sensor));
    }

    SensorsManager::instance()->filterSensors(filteredSensors);
}
