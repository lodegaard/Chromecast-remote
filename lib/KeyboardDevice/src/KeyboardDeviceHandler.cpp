#include "KeyboardDeviceHandler.h"

#include <sys/ioctl.h>

#include <asio.hpp>
#include <iostream>

#include "Device.h"
#include "StreamWrapper.h"

using namespace std;

KeyboardDeviceHandler::KeyboardDeviceHandler(
    asio::io_context& ioContext,
    const std::vector<std::shared_ptr<StreamWrapper>>& streams)
    : m_ioContext{ioContext}, m_streams{streams}
{
}

void KeyboardDeviceHandler::setDevice(shared_ptr<Device> device)
{
    m_device = device;
    readloop();
}

void KeyboardDeviceHandler::readloop()
{
    m_events.resize(32);
    for (auto& stream : m_streams) {
        stream->readAsync(asio::buffer(m_events),
                          [this](const asio::error_code& ec, size_t bytes) {
                              handleInput(ec, bytes);
                          });
    }
}

void KeyboardDeviceHandler::handleInput(const asio::error_code& ec,
                                        size_t bytes)
{
    if (!ec) {
        const auto numEvents = bytes / sizeof(input_event);
        int currentEvent = 0;
        for (const auto& event : m_events) {
            if (currentEvent >= numEvents) break;

            if (m_device) {
                auto e = getInputEvent(event);
                m_device->handleInputEvent(e);
            }
            currentEvent++;
        }
        cout << "\n";
        readloop();
    } else {
        cerr << "Read error: " << ec.message() << "\n";
    }
}

InputEvent KeyboardDeviceHandler::getInputEvent(const input_event& event)
{
    InputEvent::Action action = InputEvent::Action::unknown;
    InputEvent::Type type = InputEvent::Type::unknown;
    if (event.type == EV_KEY) {
        type = InputEvent::Type::keyboard;
        if (event.value == 0)
            action = InputEvent::Action::press;
        else if (event.value == 1)
            action = InputEvent::Action::release;
        else if (event.value == 2)
            action = InputEvent::Action::hold;
    }
    return InputEvent{type, action, event.code};
}