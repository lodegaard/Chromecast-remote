#pragma once

struct InputEvent;

class Device
{
public:
    virtual ~Device() {};

    virtual void handleInputEvent(const InputEvent&) = 0;
};

