#include "InputEvent.h"

#include <string>

using namespace std;

string toString(InputEvent::Action action)
{
    switch (action) {
        case InputEvent::Action::unknown:
            return "unknown";
        case InputEvent::Action::press:
            return "press";
        case InputEvent::Action::release:
            return "release";
        case InputEvent::Action::hold:
            return "hold";
    }
    return "";
}