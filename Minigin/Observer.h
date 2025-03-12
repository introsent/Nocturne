#pragma once
#include <xstring>

class Subject;
class Observer {
public:
    virtual ~Observer() = default;
    virtual void Notify(const std::string& event, Subject* subject) = 0;
};
