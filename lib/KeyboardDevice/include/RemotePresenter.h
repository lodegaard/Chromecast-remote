#pragma once

#include <functional>
#include <map>
#include <memory>
#include <ostream>
#include <vector>

#include "Device.h"
#include "InputEvent.h"

namespace asio
{
class io_context;
}

class RemotePresenter : public Device
{
public:
    using KeyEventHandler = std::function<void()>;

    enum class Key {
        unknown,
        power,
        play_pause,
        up,
        down,
        left,
        right,
        enter,
        back,
        homepage,
        compose,
        pageup,
        pagedown,
        volumeup,
        volumedown,
        backspace,
        mute,
        voicecommand
    };

    RemotePresenter(asio::io_context& ioContext);

    void registerKeyEventHandler(const Key& key,
                                 const InputEvent::Action& action,
                                 KeyEventHandler handler);

    static std::string toString(Key key);

    /// Device interface implementation
    void handleInputEvent(const InputEvent& event) override;

private:
    using KeyEvent = std::pair<Key, InputEvent::Action>;

    asio::io_context& m_ioContext;
    std::map<KeyEvent, std::vector<KeyEventHandler>> m_keyActions;

    void onKeyEvent(Key key);
    Key decodeKeypress(const InputEvent& event);
};

std::ostream& operator<<(std::ostream& out, RemotePresenter::Key key);