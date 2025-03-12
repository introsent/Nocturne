#pragma once
#include <vector>

#include "Event.h"

namespace dae
{
    class Observer;
    class Subject {
    public:
        Subject() = default;
        virtual ~Subject() = default;

        void AddObserver(Observer* observer);

        void RemoveObserver(Observer* observer);

    protected:
        void NotifyObservers(Event event, Subject* subject);

    private:
        std::vector<Observer*> m_observers;
    };
}

