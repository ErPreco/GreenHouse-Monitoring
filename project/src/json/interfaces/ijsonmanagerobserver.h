#ifndef I_JSON_MANAGER_OBSERVER_H
#define I_JSON_MANAGER_OBSERVER_H

class IJsonManagerObserver {
    public:
        virtual ~IJsonManagerObserver() = default;
        virtual void notifyModifiedFile() = 0;
        virtual void notifySavedFile() = 0;
};

#endif
