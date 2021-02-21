#pragma once

#include <asio.hpp>
#include <functional>
#include <system_error>

class StreamWrapper
{
public:
    using Handler = std::function<void(std::error_code, size_t)>;
    virtual ~StreamWrapper() {}

    virtual void readAsync(const asio::mutable_buffer&, Handler) = 0;
};
