#include "KeyboardDeviceList.h"

#include "KeyboardDeviceHandler.h"
#include "PosixStreamWrapper.h"
#include "StreamWrapper.h"

#include <asio.hpp>
#include <cstring>
#include <dirent.h>
#include <filesystem>
#include <fcntl.h>
#include <iostream>
#include <linux/input.h>
#include <sstream>
#include <tuple>
#include <unistd.h>
#include <stdexcept>

using namespace std;

bool operator<(const KeyboardDeviceList::DeviceInfo& lhs, const KeyboardDeviceList::DeviceInfo& rhs)
{
    return std::tie(lhs.vendor, lhs.product) < std::tie(rhs.vendor, rhs.product);
}

KeyboardDeviceList::KeyboardDeviceList(asio::io_context& ioContext)
    : m_ioContext{ioContext}
{
    scan();
}

shared_ptr<KeyboardDeviceHandler> KeyboardDeviceList::getDeviceHandler(const DeviceInfo& deviceInfo) const
{
    if (auto device = m_devices.find(deviceInfo); device != m_devices.end())
    {
        vector<shared_ptr<StreamWrapper>> streams;
        for (const auto& stream : device->second)
        {
            streams.push_back(make_shared<PosixStreamWrapper>(m_ioContext, stream));
        }
        return make_shared<KeyboardDeviceHandler>(
                m_ioContext, 
                streams);
    }

    throw runtime_error("No such device");
}

string KeyboardDeviceList::getDeviceListString() const
{
    stringstream ss;
    int deviceNumber = 0;
    for (const auto& [deviceInfo, paths] : m_devices)
    {
        ss << deviceNumber++ << ": "
           << "Vendor " << deviceInfo.vendor << ", "
           << "Product " << deviceInfo.product << " - ";
        for (const auto& path : paths)
        {
            ss << path << ", ";
        }
        ss << "\n";
    }
    return ss.str();
}

void KeyboardDeviceList::scan()
{
    vector<filesystem::path> eventPaths;
    for (const auto& entry : filesystem::directory_iterator{m_inputDevicePath})
    {
        if (strncmp("event", entry.path().filename().c_str(), 5) == 0)
        {
            eventPaths.push_back(entry.path());
        }
    }

    for (const auto& device : eventPaths)
    {
        int fd = open(device.c_str(), O_RDONLY);
        if (fd < 0)
        {
            cerr << "Unable to open " << device << "\n";
            continue;
        }
        struct input_id ev_info;
        ioctl(fd, EVIOCGID, &ev_info);
        close(fd);

        m_devices[{ev_info.vendor, ev_info.product}].push_back(device);
    }

}
