#ifndef UPPER_BAR_H
#define UPPER_BAR_H

#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>
#include <QPaintEvent>
#include <QStyleOption>
#include <QPainter>
#include "../json/jsonmanager.h"
#include "log/criticalmessagelog.h"
#include "log/warningmessagelog.h"

class UpperBar : public QWidget, public IJsonManagerObserver {
    Q_OBJECT

    private:
        QApplication& app;
        QLabel* fileNameText;

    private slots:
        void quit();

    public:
        UpperBar(QApplication&);

        void notifyModifiedFile() override;
        void notifySavedFile() override;

        void paintEvent(QPaintEvent*) override;
};

#endif
