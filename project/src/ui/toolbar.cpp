#include "toolbar.h"

ToolBar::ToolBar() {
    setStyleSheet("background-color:#6CB4EE");
    setMaximumHeight(35);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setAlignment(Qt::AlignLeft);
    layout->setSpacing(5);
    layout->setContentsMargins(8, 5, 8, 5);

    // save button
    QPushButton* saveBtn = new QPushButton();
    saveBtn->setIcon(QIcon(":/saveicon"));
    saveBtn->setStyleSheet("background-color:lightblue");
    saveBtn->setShortcut(Qt::CTRL | Qt::Key_S);
    connect(saveBtn, &QPushButton::pressed, this, &ToolBar::openSaveDialog);
    layout->addWidget(saveBtn);

    // load button
    QPushButton* loadBtn = new QPushButton();
    loadBtn->setIcon(QIcon(":/loadicon"));
    loadBtn->setStyleSheet("background-color:lightblue");
    loadBtn->setShortcut(Qt::CTRL | Qt::Key_O);
    connect(loadBtn, &QPushButton::pressed, this, &ToolBar::openLoadDialog);
    layout->addWidget(loadBtn);
}

void ToolBar::openSaveDialog() {
    if (SensorsManager::instance()->getSensors().empty()) {
        QString msg = "Current sensor file cannot be empty.";
        CriticalMessageLog criticalMessageLog(msg, "Unsalvageable file");
        criticalMessageLog.showMessage();
    } else if (JsonManager::instance()->getPath().isEmpty()) {
        if (auto filePath = QFileDialog::getSaveFileName(this, tr("Save file"), "sensor-simulation.json", tr("(*.json)")); !filePath.isEmpty())
            JsonManager::instance()->save(filePath);
    } else {
        JsonManager::instance()->save();
    }
}

void ToolBar::openLoadDialog() {
    if (JsonManager::instance()->getIsModified()) {
        QString msg = "Open a new file? This action will delete all progress of the unsaved file \"" + JsonManager::instance()->getFileName() + "\".";
        WarningMessageLog warningMessageLog(msg, "Unsaved file", QMessageBox::Cancel | QMessageBox::Save | QMessageBox::Open);
        warningMessageLog.showMessage();
        
        if (warningMessageLog.getResult() == QMessageBox::Cancel)
            return;
        if (warningMessageLog.getResult() == QMessageBox::Save)
            openSaveDialog();
    }
    
    if (auto filePath = QFileDialog::getOpenFileName(this, tr("Open file"), "", tr("(*.json)")); !filePath.isEmpty()) {
        SensorsManager::instance()->clearSensors();
        JsonManager::instance()->load(filePath);
    }
}

void ToolBar::paintEvent(QPaintEvent* _event) {
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QWidget::paintEvent(_event);
}
