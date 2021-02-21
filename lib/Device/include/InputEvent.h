#pragma once

#include <tuple>
#include <string>
#include <ostream>

struct InputEvent
{
    enum class Type
    {
        unknown,
        keyboard
    };

    enum class Action
    {
        unknown,
        press,
        release,
        hold
    };
    
    Type type;
    Action action;
    int key;
};

std::string toString(InputEvent::Action action);

inline std::ostream& operator<<(std::ostream& out, InputEvent::Action action)
{
    out << toString(action);
    return out;
}

inline bool operator==(const InputEvent& lhs, const InputEvent& rhs)
{
    return std::tie(lhs.type, lhs.action, lhs.key) == std::tie(rhs.type, rhs.action, rhs.key);
}
