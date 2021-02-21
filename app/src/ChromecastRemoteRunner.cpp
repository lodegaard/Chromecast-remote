#include "ChromecastRemoteRunner.h"

#include <iostream>

#include "EventSerializer.h"
#include "InputEvent.h"
#include "KeyboardDeviceHandler.h"
#include "KeyboardDeviceList.h"
#include "Publisher.h"
#include "RemotePresenter.h"

using namespace std;
using namespace asio;

namespace
{
constexpr int vendorId = 6421;
constexpr int productId = 4133;
}  // namespace

ChromecastRemoteRunner::ChromecastRemoteRunner(const std::string& destinationIp,
                                               unsigned short port)
    : m_destinationIp{destinationIp}
    , m_destinationPort{port}
    , m_ioContext{make_unique<io_context>()}
    , m_endpoint{make_unique<ip::udp::endpoint>(
          ip::address::from_string(m_destinationIp), m_destinationPort)}
    , m_socket{make_unique<ip::udp::socket>(*m_ioContext, ip::udp::v4())}
    , m_deviceList{make_unique<KeyboardDeviceList>(*m_ioContext)}
    , m_deviceHandler{m_deviceList->getDeviceHandler({vendorId, productId})}
    , m_publisher{make_unique<Publisher>(*m_ioContext, *m_socket, *m_endpoint)}
    , m_remote{make_shared<RemotePresenter>(*m_ioContext)}
{
    cout << "Publishing events to " << m_destinationIp << ":"
         << m_destinationPort << "\n";
    m_deviceHandler->setDevice(m_remote);
    registerKeyEventPublishers();
}

ChromecastRemoteRunner::~ChromecastRemoteRunner() {}

void ChromecastRemoteRunner::run() { m_ioContext->run(); }

void ChromecastRemoteRunner::registerKeyEventPublishers()
{
    for (const auto& key :
         {RemotePresenter::Key::play_pause, RemotePresenter::Key::volumeup,
          RemotePresenter::Key::volumedown, RemotePresenter::Key::mute,
          RemotePresenter::Key::power}) {
        cout << "Register key handler for " << key << "\n";
        m_remote->registerKeyEventHandler(
            key, InputEvent::Action::press, [this, key]() {
                m_publisher->publish(EventSerializer::serializeEvent(key));
            });
    }
}