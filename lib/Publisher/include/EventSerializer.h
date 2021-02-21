#pragma once

#include "RemotePresenter.h"

#include <string>

class EventSerializer
{
public:
    static std::string serializeEvent(RemotePresenter::Key key);
};