#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "EventSerializer.h"
#include "RemotePresenter.h"

using namespace testing;

struct EventSerializerTest : public Test
{};

TEST_F(EventSerializerTest, serializeKeyEnter_equalsExpectedString)
{
    EXPECT_EQ(EventSerializer::serializeEvent(RemotePresenter::Key::enter), "{\"key\":\"enter\"}");
}