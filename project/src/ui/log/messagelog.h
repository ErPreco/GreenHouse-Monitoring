#ifndef MESSAGE_LOG_H
#define MESSAGE_LOG_H

#include <QString>
#include <QDialog>

class MessageLog : public QDialog {
    protected:
        QString title;
        QString message;

    public:
        MessageLog(const QString&, const QString&);
        virtual ~MessageLog() = default;

        virtual void showMessage() = 0;
};

#endif
