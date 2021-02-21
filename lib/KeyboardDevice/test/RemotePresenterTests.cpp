#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <linux/input-event-codes.h>

#include <asio.hpp>

#include "RemotePresenter.h"

using namespace testing;

struct RemotePresenterTests : public Test {
    asio::io_context ioContext;
    RemotePresenter presenter;

    RemotePresenterTests() : presenter{ioContext} {}
};

struct KeyEventHandlerFunction {
    virtual ~KeyEventHandlerFunction() {}
    virtual void keyEventHandler() = 0;
};

struct KeyEventHandlerMock : public KeyEventHandlerFunction {
    MOCK_METHOD(void, keyEventHandler, (), (override));
};

TEST_F(RemotePresenterTests, noRegisteredKeyHandler_sendKeyBoardEvent_noAction)
{
    EXPECT_NO_THROW(presenter.handleInputEvent(InputEvent{
        InputEvent::Type::keyboard, InputEvent::Action::press, KEY_PLAYPAUSE}));
}

TEST_F(RemotePresenterTests,
       registerPlayPauseKeyHandler_sendPlayPauseKeyEvent_handlerFunctionCalled)
{
    KeyEventHandlerMock playPauseHandler;
    EXPECT_CALL(playPauseHandler, keyEventHandler).Times(1);
    presenter.registerKeyEventHandler(
        RemotePresenter::Key::play_pause, InputEvent::Action::press,
        [&playPauseHandler] { playPauseHandler.keyEventHandler(); });
    presenter.handleInputEvent(InputEvent{
        InputEvent::Type::keyboard, InputEvent::Action::press, KEY_PLAYPAUSE});
}

TEST_F(RemotePresenterTests,
       registerPlayPauseKeyHandler_sendBackspaceKeyEvent_noAction)
{
    KeyEventHandlerMock playPauseHandler;
    EXPECT_CALL(playPauseHandler, keyEventHandler).Times(0);
    presenter.registerKeyEventHandler(
        RemotePresenter::Key::play_pause, InputEvent::Action::press,
        [&playPauseHandler] { playPauseHandler.keyEventHandler(); });
    presenter.handleInputEvent(InputEvent{
        InputEvent::Type::keyboard, InputEvent::Action::press, KEY_BACKSPACE});
}