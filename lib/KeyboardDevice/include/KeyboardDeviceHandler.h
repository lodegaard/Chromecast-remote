#pragma once

#include "InputEvent.h"
#include "DeviceHandler.h"

#include <asio.hpp>
#include <memory>
#include <vector>
#include <linux/input.h>

class Device;
class StreamWrapper;

class KeyboardDeviceHandler : public DeviceHandler
{
public:
    KeyboardDeviceHandler(
        asio::io_context& ioContext, 
        const std::vector<std::shared_ptr<StreamWrapper>>& streams);

    /// DeviceHandler interface implementation
    void setDevice(std::shared_ptr<Device> device) override;

private:
    asio::io_context& m_ioContext;
    std::vector<std::shared_ptr<StreamWrapper>> m_streams;
    std::vector<input_event> m_events;
    std::shared_ptr<Device> m_device;

    void readloop();
    void handleInput(const asio::error_code& ec, size_t bytes);

    InputEvent getInputEvent(const input_event& event);
};