#include "Subject.h"

void Subject::AddObserver(Observer* observer)
{
    m_observers.push_back(observer);
}

void Subject::RemoveObserver(Observer* observer)
{
    std::erase(m_observers, observer);
}

void Subject::NotifyObservers(const std::string& event)
{
    for (auto observer : m_observers) {
        observer->Notify(event, this);
    }
}


