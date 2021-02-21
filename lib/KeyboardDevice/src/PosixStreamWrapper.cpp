#include "PosixStreamWrapper.h"

#include <linux/input.h>

using namespace std;

PosixStreamWrapper::PosixStreamWrapper(
    asio::io_context& ioContext,
    const std::string& pathname)
    : m_ioContext{ioContext}
{
    auto fd = open(pathname.c_str(), O_RDONLY);
    ioctl(fd, EVIOCGRAB, 1);
    m_sd = make_shared<asio::posix::stream_descriptor>(m_ioContext, fd);
}

PosixStreamWrapper::~PosixStreamWrapper()
{
    m_sd->close();
}

void PosixStreamWrapper::readAsync(const asio::mutable_buffer& buffer, Handler handler)
{
    m_sd->async_read_some(buffer, handler);
}