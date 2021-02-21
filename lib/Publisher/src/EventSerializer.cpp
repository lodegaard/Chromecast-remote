#include "EventSerializer.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::string EventSerializer::serializeEvent(RemotePresenter::Key key)
{
    json j;
    j["key"] = RemotePresenter::toString(key);
    return j.dump();
}