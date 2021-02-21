#include <fcntl.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <asio.hpp>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Device.h"
#include "InputEvent.h"
#include "KeyboardDeviceHandler.h"
#include "StreamWrapper.h"

using namespace std;
using namespace testing;
using asio::posix::stream_descriptor;

struct DeviceMock : public Device {
    MOCK_METHOD(void, handleInputEvent, (const InputEvent&), (override));
};

struct KeyboardDeviceHandlerTests : public Test {
    asio::io_context ioContext;
    shared_ptr<DeviceMock> device;

    KeyboardDeviceHandlerTests() : device{make_shared<DeviceMock>()} {}
};

class DummyStream : public StreamWrapper
{
public:
    using EventMap = std::unordered_map<int, std::vector<input_event>>;

    DummyStream(const error_code& _error, const EventMap& _events)
        : events{_events}, iterator{events.begin()}, error{_error}
    {
    }

    void readAsync(const asio::mutable_buffer& buffer, Handler handler)
    {
        if (iterator != events.end()) {
            auto currentEvent = iterator;
            iterator++;
            memcpy(buffer.data(), currentEvent->second.data(),
                   currentEvent->second.size() * sizeof(input_event));
            handler(error, currentEvent->second.size() * sizeof(input_event));
        }
    }

private:
    EventMap events;
    EventMap::iterator iterator;
    error_code error;
};

TEST_F(KeyboardDeviceHandlerTests,
       constructDeviceHandle_sendKeyEventNoError_deviceHandleFunctionCalledOnce)
{
    EXPECT_CALL(*device, handleInputEvent(InputEvent{InputEvent::Type::keyboard,
                                                     InputEvent::Action::press,
                                                     KEY_PLAYPAUSE}))
        .Times(1);

    auto stream = make_shared<DummyStream>(
        error_code{},
        DummyStream::EventMap{{0, {{{0, 0}, EV_KEY, KEY_PLAYPAUSE, 0}}}});
    KeyboardDeviceHandler keyboardDeviceHandler{ioContext, {stream}};

    keyboardDeviceHandler.setDevice(device);
}

TEST_F(KeyboardDeviceHandlerTests,
       constructDeviceHandle_noKeyEventNoError_deviceHandleFunctionNotCalled)
{
    EXPECT_CALL(*device, handleInputEvent(InputEvent{InputEvent::Type::keyboard,
                                                     InputEvent::Action::press,
                                                     KEY_PLAYPAUSE}))
        .Times(0);

    auto stream =
        make_shared<DummyStream>(error_code{}, DummyStream::EventMap{});
    KeyboardDeviceHandler keyboardDeviceHandler{ioContext, {stream}};

    keyboardDeviceHandler.setDevice(device);
}

TEST_F(
    KeyboardDeviceHandlerTests,
    constructDeviceHandle_sendKeyEventWithError_deviceHandleFunctionNotCalled)
{
    EXPECT_CALL(*device, handleInputEvent(InputEvent{InputEvent::Type::keyboard,
                                                     InputEvent::Action::press,
                                                     KEY_PLAYPAUSE}))
        .Times(0);

    auto stream = make_shared<DummyStream>(
        asio::error::bad_descriptor,
        DummyStream::EventMap{{0, {{{0, 0}, EV_KEY, KEY_PLAYPAUSE, 0}}}});
    KeyboardDeviceHandler keyboardDeviceHandler{ioContext, {stream}};

    keyboardDeviceHandler.setDevice(device);
}

TEST_F(
    KeyboardDeviceHandlerTests,
    constructDeviceHandle_sendNonKeyEventNoError_deviceHandleFunctionCalledOnce)
{
    EXPECT_CALL(*device, handleInputEvent(
                             InputEvent{InputEvent::Type::unknown,
                                        InputEvent::Action::unknown, REL_RX}))
        .Times(1);

    auto stream = make_shared<DummyStream>(
        error_code{},
        DummyStream::EventMap{{0, {{{0, 0}, EV_REL, REL_RX, 0}}}});
    KeyboardDeviceHandler keyboardDeviceHandler{ioContext, {stream}};

    keyboardDeviceHandler.setDevice(device);
}