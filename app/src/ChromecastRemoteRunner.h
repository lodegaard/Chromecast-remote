#pragma once

#include <asio.hpp>
#include <string>
#include <memory>

class KeyboardDeviceHandler;
class KeyboardDeviceList;
class Publisher;
class RemotePresenter;

class ChromecastRemoteRunner
{
public:
    ChromecastRemoteRunner(const std::string& destinationIp, unsigned short port);
    ~ChromecastRemoteRunner();

    void run();

private:
    std::string m_destinationIp;
    unsigned short m_destinationPort;

    std::unique_ptr<asio::io_context> m_ioContext;
    std::unique_ptr<asio::ip::udp::endpoint> m_endpoint;
    std::unique_ptr<asio::ip::udp::socket> m_socket;

    std::unique_ptr<KeyboardDeviceList> m_deviceList;
    std::shared_ptr<KeyboardDeviceHandler> m_deviceHandler;
    std::unique_ptr<Publisher> m_publisher;
    std::shared_ptr<RemotePresenter> m_remote;

    void registerKeyEventPublishers();
};