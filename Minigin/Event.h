// Event.h
#pragma once
#include <functional>
#include <vector>
#include <algorithm>

template<typename... Args>
class Event {
public:
    using HandlerFunc = std::function<void(Args...)>;

    // subscribe to the event
    int Subscribe(HandlerFunc handler) {
        m_currentId++;
        m_handlers.push_back({ m_currentId, std::move(handler) });
        return m_currentId;
    }

    // unsubscribe using the token
    void Unsubscribe(int token) {
        m_handlers.erase(
            std::remove_if(m_handlers.begin(), m_handlers.end(),
                [token](const std::pair<int, HandlerFunc>& pair) {
                    return pair.first == token;
                }),
            m_handlers.end());
    }

    // invoke all subscribers immediately
    void Invoke(Args... args) const {
        auto handlersCopy = m_handlers;  // make a copy of the handlers, so we can unsubscribe safely
        for (const auto& handlerPair : handlersCopy) {
            handlerPair.second(args...);
        }
    }

    // convenience
    void operator()(Args... args) const {
        Invoke(args...);
    }

private:
    int m_currentId{ 0 };
    std::vector<std::pair<int, HandlerFunc>> m_handlers;
};
