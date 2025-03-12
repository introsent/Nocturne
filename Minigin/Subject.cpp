#include "Subject.h"

#include "Observer.h"

namespace dae
{
    void Subject::AddObserver(Observer* observer)
    {
        m_observers.emplace_back(observer);
    }

    void Subject::RemoveObserver(Observer* observer)
    {
        std::erase(m_observers, observer);
    }

    void Subject::NotifyObservers(Event event, Subject* subject)
    {
        for (auto observer : m_observers) {
            observer->Notify(event, subject);
        }
    }
}



