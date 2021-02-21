#pragma once

#include <string>

#include "RemotePresenter.h"

class EventSerializer
{
public:
    static std::string serializeEvent(RemotePresenter::Key key);
};