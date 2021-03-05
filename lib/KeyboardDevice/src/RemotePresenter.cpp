#include "RemotePresenter.h"

#include <linux/input-event-codes.h>

#include <asio.hpp>
#include <iostream>
#include <string>

using namespace std;

ostream& operator<<(ostream& out, RemotePresenter::Key key)
{
    out << RemotePresenter::toString(key);
    return out;
}

RemotePresenter::RemotePresenter(asio::io_context& ioContext)
    : m_ioContext{ioContext}, m_keyActions{}
{
}

void RemotePresenter::registerKeyEventHandler(const Key& key,
                                              const InputEvent::Action& action,
                                              KeyEventHandler handler)
{
    m_keyActions[{key, action}].push_back(handler);
}

string RemotePresenter::toString(RemotePresenter::Key key)
{
    switch (key) {
        case RemotePresenter::Key::unknown:
            return "unknown";
        case RemotePresenter::Key::power:
            return "power";
        case RemotePresenter::Key::play_pause:
            return "play_pause";
        case RemotePresenter::Key::up:
            return "up";
        case RemotePresenter::Key::down:
            return "down";
        case RemotePresenter::Key::left:
            return "left";
        case RemotePresenter::Key::right:
            return "right";
        case RemotePresenter::Key::enter:
            return "enter";
        case RemotePresenter::Key::back:
            return "back";
        case RemotePresenter::Key::homepage:
            return "homepage";
        case RemotePresenter::Key::compose:
            return "compose";
        case RemotePresenter::Key::pageup:
            return "pageup";
        case RemotePresenter::Key::pagedown:
            return "pagedown";
        case RemotePresenter::Key::volumeup:
            return "volumeup";
        case RemotePresenter::Key::volumedown:
            return "volumedown";
        case RemotePresenter::Key::backspace:
            return "backspace";
        case RemotePresenter::Key::mute:
            return "mute";
        case RemotePresenter::Key::voicecommand:
            return "voicecommand";
    }
    return "";
}

void RemotePresenter::handleInputEvent(const InputEvent& event)
{
    cout << "Handle input event key " << event.key << " action " << event.action
         << "\n";
    if (auto key = decodeKeypress(event); key != Key::unknown) {
        if (auto eventHandlerIt = m_keyActions.find({key, event.action});
            eventHandlerIt != m_keyActions.end()) {
            for (const auto& eventHandler : eventHandlerIt->second) {
                eventHandler();
            }
        }
    }
}

RemotePresenter::Key RemotePresenter::decodeKeypress(const InputEvent& event)
{
    switch (event.key) {
        case KEY_POWER:
            return Key::power;
        case KEY_PLAYPAUSE:
            return Key::play_pause;
        case KEY_UP:
            return Key::up;
        case KEY_DOWN:
            return Key::down;
        case KEY_LEFT:
            return Key::left;
        case KEY_RIGHT:
            return Key::right;
        case KEY_ENTER:
            return Key::enter;
        case KEY_BACK:
            return Key::back;
        case KEY_HOMEPAGE:
            return Key::homepage;
        case KEY_COMPOSE:
            return Key::compose;
        case KEY_PAGEUP:
            return Key::pageup;
        case KEY_PAGEDOWN:
            return Key::pagedown;
        case KEY_VOLUMEUP:
            return Key::volumeup;
        case KEY_VOLUMEDOWN:
            return Key::volumedown;
        case KEY_BACKSPACE:
            return Key::backspace;
        case KEY_MUTE:
            return Key::mute;
        case KEY_VOICECOMMAND:
            return Key::voicecommand;
        default:
            return Key::unknown;
    }
}