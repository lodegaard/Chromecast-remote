#pragma once

#include <asio.hpp>
// namespace asio
// {
// class io_context;
// }
#include <string>

class Publisher
{
public:
    Publisher(asio::io_context& ioContext, asio::ip::udp::socket& socket, asio::ip::udp::endpoint& endpoint);

    void publish(const std::string& json);

private:
    asio::io_context& m_ioContext;
    asio::ip::udp::socket& m_socket;
    asio::ip::udp::endpoint& m_endpoint;
};