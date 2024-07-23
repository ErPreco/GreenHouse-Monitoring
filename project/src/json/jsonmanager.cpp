#include "jsonmanager.h"

JsonManager* JsonManager::ptr = nullptr;

JsonManager::JsonManager() : path(""), fileName("Untitled-file"), isModified(false) {}

JsonManager* JsonManager::instance() {
    if (ptr == nullptr)
        ptr = new JsonManager();
    return ptr;
}

// getter

const QString& JsonManager::getPath() const {
    return path;
}

const QString& JsonManager::getFileName() const {
    return fileName;
}

bool JsonManager::getIsModified() const {
    return isModified;
}

// setter

void JsonManager::setIsModified(bool _v) {
    isModified = _v;
    if (isModified) {
        for (auto observer : observers)
            observer->notifyModifiedFile();
    } else {
        for (auto observer : observers)
            observer->notifySavedFile();
    }
}

// save

void JsonManager::save(const QString& _path) {
    if (!_path.isEmpty()) {
        path = _path;
        QStringList seg = path.split("/");
        fileName = seg.value(seg.length() - 1).split(".").value(0);
    }
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly))
        throw OpenFileFailed("\"" + _path.toStdString() + " cannot be found or cannot be openned in \"write only\" mode.");

    QJsonArray array;
    for (auto sensor : SensorsManager::instance()->getSensors()) {
        JsonWriterVisitor visitor;
        sensor->accept(visitor);
        array.append(visitor.getJsonObject());
    }

    QJsonObject obj;
    obj.insert("sensors", array);
    file.write(QJsonDocument(obj).toJson());

    setIsModified(false);
}

// load

void JsonManager::load(const QString& _path) {
    path = _path;
    QStringList seg = path.split("/");
    fileName = seg.value(seg.length() - 1).split(".").value(0);
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
        throw OpenFileFailed("\"" + _path.toStdString() + " cannot be found or cannot be openned in \"read only\" mode.");

    QJsonDocument doc(QJsonDocument::fromJson(file.readAll()));
    QJsonObject obj(doc.object());

    if (auto v = obj.value("sensors"); v.isArray()) {
        Sensor::resetIdStarter();
        for (auto sensor : v.toArray())
            SensorsManager::instance()->addSensor(readSensor(sensor.toObject()));
    }

    setIsModified(false);
}

// observer

void JsonManager::registerObserver(IJsonManagerObserver* _observer) {
    observers.push_back(_observer);
}

void JsonManager::unregisterObserver(IJsonManagerObserver* _observer) {
    for (auto it = observers.begin(); it != observers.end(); it++) {
        if (*it == _observer) {
            observers.erase(it);
            break;
        }
    }
}
