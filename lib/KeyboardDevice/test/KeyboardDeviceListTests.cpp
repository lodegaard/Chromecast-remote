#include <gtest/gtest.h>

#include "KeyboardDeviceList.h"

#include <asio.hpp>
#include <dirent.h>
#include <cstring>
#include <iostream>

#include <filesystem>

using namespace std;
using namespace testing;

struct KeyboardDeviceListTests : public Test
{
    asio::io_context ioContext;
    KeyboardDeviceList deviceList;

    KeyboardDeviceListTests() : deviceList{ioContext} {}

    static int numInputDevices()
    {
        vector<filesystem::path> eventPaths;
        for (const auto& entry : filesystem::directory_iterator{"/dev/input"})
        {
            if (strncmp("event", entry.path().filename().c_str(), 5) == 0)
            {
                eventPaths.push_back(entry.path());
            }
        }

        return eventPaths.size();
    }
};

TEST_F(KeyboardDeviceListTests, getDeviceListSize_shouldBeLessThanInputDevices)
{
    EXPECT_LE(deviceList.size(), numInputDevices());
}

TEST_F(KeyboardDeviceListTests, openNonExistingDevice_shouldThrow)
{
    EXPECT_THROW(deviceList.getDeviceHandler({123, 456}), std::runtime_error);
}
