#ifndef PAGE_CONTROLLER_PANEL_H
#define PAGE_CONTROLLER_PANEL_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <QPaintEvent>
#include <QPainter>
#include <QStyleOption>

class PageControllerPanel : public QWidget {
    Q_OBJECT

    private:
        unsigned int pagesCount;
        QLabel* pageIndicator;
        QLabel* totPageIndicator;
    
    public:
        PageControllerPanel(unsigned int = 1);

        void setPagesCount(unsigned int);
        void updatePagesCount(bool);
        void setPageIndicator(unsigned int);

        void paintEvent(QPaintEvent*) override;
    
    signals:
        void changePage(bool);
    
    public slots:
        void prevPage();
        void nextPage();
};

#endif
