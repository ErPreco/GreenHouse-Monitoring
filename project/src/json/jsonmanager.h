#ifndef JSON_MANAGER_H
#define JSON_MANAGER_H

#include <QString>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <vector>
#include "../logic/sensor/sensorsmanager.h"
#include "jsonreader.h"
#include "json_writer_visitor/jsonwritervisitor.h"
#include "interfaces/ijsonmanagerobserver.h"

class JsonManager {
    private:
        static JsonManager* ptr;

        QString path;
        QString fileName;
        bool isModified;
        std::vector<IJsonManagerObserver*> observers;

        JsonManager();
    
    public:
        JsonManager(const JsonManager&) = delete;
        ~JsonManager() = default;
        JsonManager& operator=(const JsonManager&) = delete;

        static JsonManager* instance();

        const QString& getPath() const;
        const QString& getFileName() const;
        bool getIsModified() const;

        void setIsModified(bool);

        // Saves the file with the given path (empty path means the file is untitled).
        void save(const QString& = "");
        // Loads the file with the given path.
        void load(const QString&);

        void registerObserver(IJsonManagerObserver*);
        void unregisterObserver(IJsonManagerObserver*);
};

#endif

