#pragma once

#include <memory>

class Device;

class DeviceHandler
{
public:
    virtual ~DeviceHandler(){};

    virtual void setDevice(std::shared_ptr<Device>) = 0;
};
