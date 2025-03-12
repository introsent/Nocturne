#pragma once
#include <vector>
#include "Observer.h"


class Subject {
public:
    void AddObserver(Observer* observer);

    void RemoveObserver(Observer* observer);

protected:
    void NotifyObservers(const std::string& event);

private:
    std::vector<Observer*> m_observers;
};

