#pragma once
#include "Event.h"

namespace dae
{
    class Subject;
    class Observer {
    public:
        virtual ~Observer() = default;
        virtual void Notify(Event event, Subject* subject) = 0;
    };
}
