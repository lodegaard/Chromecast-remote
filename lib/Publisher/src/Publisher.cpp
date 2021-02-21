#include "Publisher.h"

#include <iostream>

using namespace std;
using namespace asio;
using namespace asio::ip;

// , m_endpoint{asio::ip::address::from_string(destinationIp), port}
Publisher::Publisher(io_context& ioContext, udp::socket& socket, udp::endpoint& endpoint)
    : m_ioContext{ioContext}
    , m_socket{socket}
    , m_endpoint{endpoint}
{
}

void Publisher::publish(const std::string& json)
{
    cout << "Sending " << json << "\n";
    m_socket.send_to(asio::buffer(json), m_endpoint);
}