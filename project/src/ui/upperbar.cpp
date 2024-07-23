#include "upperbar.h"

UpperBar::UpperBar(QApplication& _app) : app(_app), fileNameText(new QLabel()) {
    setStyleSheet("background-color:#00308F");
    setMaximumHeight(35);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setAlignment(Qt::AlignRight);
    layout->setSpacing(5);
    layout->setContentsMargins(8, 5, 8, 5);

    layout->addStretch();
    
    // file name
    fileNameText->setText(JsonManager::instance()->getFileName());
    fileNameText->setStyleSheet("color:white; font-weight:bold");
    layout->addWidget(fileNameText);

    layout->addStretch();

    // quit button
    QPushButton* quitBtn = new QPushButton();
    quitBtn->setIcon(QIcon(":/quiticon"));
    quitBtn->setStyleSheet("background-color:red");
    connect(quitBtn, &QPushButton::pressed, this, &UpperBar::quit);
    layout->addWidget(quitBtn);

    JsonManager::instance()->registerObserver(this);
}

void UpperBar::quit() {
    if (!JsonManager::instance()->getIsModified())
        app.quit();

    QString msg = "Exit the application? This action will delete all progress of the unsaved file \"" + JsonManager::instance()->getFileName() + "\".";
    WarningMessageLog warningMessageLog(msg, "Unsaved file", QMessageBox::Cancel | QMessageBox::Save | QMessageBox::Discard);
    warningMessageLog.showMessage();
    QMessageBox::StandardButton res = warningMessageLog.getResult();
    if (res == QMessageBox::Cancel)
        return;
    if (res == QMessageBox::Discard)
        app.quit();
    if (res == QMessageBox::Save) {
        if (SensorsManager::instance()->getSensors().empty()) {
            QString msg = "Current sensor file cannot be empty.";
            CriticalMessageLog criticalMessageLog(msg, "Unsalvageable file");
            criticalMessageLog.showMessage();
        } else if (JsonManager::instance()->getPath().isEmpty()) {
            if (auto filePath = QFileDialog::getSaveFileName(this, tr("Save file"), "sensor-simulation.json", tr("(*.json)")); !filePath.isEmpty())
                JsonManager::instance()->save(filePath);
            else
                return;
        } else {
            JsonManager::instance()->save();
        }
        app.quit();
    }
}

void UpperBar::notifyModifiedFile() {
    fileNameText->setText(JsonManager::instance()->getFileName() + " *");
}

void UpperBar::notifySavedFile() {
    fileNameText->setText(JsonManager::instance()->getFileName());
}

void UpperBar::paintEvent(QPaintEvent* _event) {
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QWidget::paintEvent(_event);
}
