#pragma once

#include <memory>
#include <string>

#include "StreamWrapper.h"

class PosixStreamWrapper : public StreamWrapper
{
public:
    PosixStreamWrapper(asio::io_context& ioContext,
                       const std::string& pathname);
    ~PosixStreamWrapper();

    // No copy or move
    PosixStreamWrapper(const PosixStreamWrapper&) = delete;
    PosixStreamWrapper& operator=(PosixStreamWrapper&) = delete;
    PosixStreamWrapper(const PosixStreamWrapper&&) = delete;
    PosixStreamWrapper& operator=(PosixStreamWrapper&&) = delete;

    void readAsync(const asio::mutable_buffer& buffer,
                   Handler handler) override;

private:
    asio::io_context& m_ioContext;
    std::shared_ptr<asio::posix::stream_descriptor> m_sd;
};
