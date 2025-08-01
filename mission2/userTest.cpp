#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "user.h"
using ::testing::Test;

TEST(UserTest, getName) {
    User user(10, "no_name");

    ASSERT_EQ(user.getName(), "no_name");
}

TEST(UserTest, getId) {
    User user(10, "no_name");

    ASSERT_EQ(user.getId(), 10);
}

TEST(UserTest, getTotalPoint) {
    User user(10, "no_name");
    user.addPoint(3);

    ASSERT_EQ(user.getTotalPoint(), 3);
}

TEST(UserTest, getGrade) {
    User user(10, "no_name");
    user.setGrade(3);

    ASSERT_EQ(user.getGrade(), 3);
}

TEST(UserTest, increaseWednesdayCount) {
    User user(10, "no_name");
    user.addAttendance(2);
    
    ASSERT_EQ(user.getWednesdayCount(), 1);
}

TEST(UserTest, increaseWeekendCount) {
    User user(10, "no_name");
    user.addAttendance(5);

    ASSERT_EQ(user.getWeekendCount(), 1);
}