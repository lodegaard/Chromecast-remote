#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

struct dirent;
class KeyboardDeviceHandler;
namespace asio
{
class io_context;
}

class KeyboardDeviceList
{
public:
    struct DeviceInfo {
        int vendor;
        int product;
    };

    KeyboardDeviceList(asio::io_context& ioContext);

    std::shared_ptr<KeyboardDeviceHandler> getDeviceHandler(
        const DeviceInfo& deviceInfo) const;

    std::string getDeviceListString() const;

    size_t size() const { return m_devices.size(); }

private:
    asio::io_context& m_ioContext;
    const std::string m_inputDevicePath{"/dev/input"};
    std::map<DeviceInfo, std::vector<std::string>> m_devices;

    void scan();
};

bool operator<(const KeyboardDeviceList::DeviceInfo& lhs,
               const KeyboardDeviceList::DeviceInfo& rhs);
