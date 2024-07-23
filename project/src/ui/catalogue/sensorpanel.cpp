#include "sensorpanel.h"

SensorPanel::SensorPanel(Sensor& _sensor, ModificationPanel* _modificationPanel) : sensor(_sensor), modificationPanel(_modificationPanel) {
    setStyleSheet("background-color:#E2E2E2");

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setSpacing(30);
    layout->setContentsMargins(35, 15, 35, 15);

    // icon
    QString iconPath = QString("%1%2%3").arg(":/").arg(QString::fromStdString(_sensor.getTypeName()).toLower()).arg("icon");
    QPixmap image(iconPath);
    QLabel* icon = new QLabel();
    icon->setPixmap(image.scaledToHeight(60));
    layout->addWidget(icon);
    
    // central layout
    QVBoxLayout* midLayout = new QVBoxLayout();
    midLayout->setAlignment(Qt::AlignCenter);
    midLayout->setSpacing(10);
    layout->addLayout(midLayout);

    InfoPanel* info = new InfoPanel(_sensor);
    midLayout->addWidget(info);

    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->setAlignment(Qt::AlignHCenter);
    QPushButton* simulationBtn = new QPushButton("simulation");
    simulationBtn->setStyleSheet("background-color:white");
    simulationBtn->setMinimumWidth(200);
    btnLayout->addWidget(simulationBtn);
    midLayout->addLayout(btnLayout);
    connect(simulationBtn, &QPushButton::pressed, this, &SensorPanel::startSimulation);

    // right buttons
    QGridLayout* rightCommands = new QGridLayout();
    rightCommands->setSpacing(10);
    layout->addLayout(rightCommands);
    
    QPushButton* modifyBtn = new QPushButton;
    modifyBtn->setIcon(QIcon(":/modifyicon"));
    modifyBtn->setStyleSheet("background-color:green");
    modifyBtn->setIconSize(QSize(30, 30));
    rightCommands->addWidget(modifyBtn, 0, 0);
    connect(modifyBtn, &QPushButton::pressed, this, &SensorPanel::openModificationPanel);

    QPushButton* deleteBtn = new QPushButton;
    deleteBtn->setIcon(QIcon(":/deleteicon"));
    deleteBtn->setStyleSheet("background-color:red");
    deleteBtn->setIconSize(QSize(30, 30));
    rightCommands->addWidget(deleteBtn, 1, 0);
    connect(deleteBtn, &QPushButton::pressed, this, &SensorPanel::removeSensor);
}

void SensorPanel::removeSensor() {
    SensorsManager::instance()->removeSensor(&sensor);
    JsonManager::instance()->setIsModified(true);
}

void SensorPanel::startSimulation() {
    sensor.startSimulation();
}

void SensorPanel::openModificationPanel() {
    modificationPanel->openDialog(&sensor);
}

void SensorPanel::paintEvent(QPaintEvent* _event) {
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QWidget::paintEvent(_event);
}
