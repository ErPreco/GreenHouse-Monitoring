#include "warningmessagelog.h"

WarningMessageLog::WarningMessageLog(const QString& _message, const QString& _title, const QMessageBox::StandardButtons& _standardButtons)
: MessageLog(_title, _message), buttons(_standardButtons) {}

QMessageBox::StandardButton WarningMessageLog::getResult() const {
    return result;
}

void WarningMessageLog::showMessage() {
    result = QMessageBox::warning(this, title, message, buttons);
}
