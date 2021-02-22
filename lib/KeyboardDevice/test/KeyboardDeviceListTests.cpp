#include <dirent.h>
#include <gtest/gtest.h>

#include <asio.hpp>
#include <cstring>
#include <experimental/filesystem>
// #include <filesystem>
#include <iostream>

#include "KeyboardDeviceList.h"

using namespace std;
using namespace std::experimental;
using namespace testing;

struct KeyboardDeviceListTests : public Test {
    asio::io_context ioContext;
    KeyboardDeviceList deviceList;

    KeyboardDeviceListTests() : deviceList{ioContext} {}

    static int numInputDevices()
    {
        // vector<filesystem::path> eventPaths;
        // for (const auto& entry : filesystem::directory_iterator{"/dev/input"}) {
        //     if (strncmp("event", entry.path().filename().c_str(), 5) == 0) {
        //         eventPaths.push_back(entry.path());
        //     }
        // }

        // return eventPaths.size();
        return 0;
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
