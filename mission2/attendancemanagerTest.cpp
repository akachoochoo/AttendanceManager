#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "attendancemanager.h"
#include "user.h"

TEST(AttendaceManager, getPoint_NULL) {
    AttendanceManager app = AttendanceManager();

    int ret = app.getPoint(Days::MAX_DAYS);

    ASSERT_EQ(ret, 0);
}

TEST(AttendaceManager, getPoint_Mon) {
    AttendanceManager app = AttendanceManager();

    int ret = app.getPoint(Days::MON);

    ASSERT_EQ(ret, DEFAULT_POINT);
}

TEST(AttendaceManager, getPoint_Wen) {
    AttendanceManager app = AttendanceManager();

    int ret = app.getPoint(Days::WED);

    ASSERT_EQ(ret, WEDNESDAY_POINT);
}

TEST(AttendaceManager, getPoint_Thu) {
    AttendanceManager app = AttendanceManager();

    int ret = app.getPoint(Days::MON);

    ASSERT_EQ(ret, DEFAULT_POINT);
}

TEST(AttendaceManager, getPoint_Sat) {
    AttendanceManager app = AttendanceManager();

    int ret = app.getPoint(Days::SAT);

    ASSERT_EQ(ret, WEEKEND_POINT);
}

TEST(AttendaceManager, getDayIndex) {
    AttendanceManager app = AttendanceManager();

    ASSERT_EQ(app.getDayIndex("monday"), Days::MON);
    ASSERT_EQ(app.getDayIndex("tuesday"), Days::TUE);
    ASSERT_EQ(app.getDayIndex("wednesday"), Days::WED);
    ASSERT_EQ(app.getDayIndex("thursday"), Days::THU);
    ASSERT_EQ(app.getDayIndex("friday"), Days::FRI);
    ASSERT_EQ(app.getDayIndex("saturday"), Days::SAT);
    ASSERT_EQ(app.getDayIndex("sunday"), Days::SUN);
    ASSERT_EQ(app.getDayIndex("saturday"), Days::SAT);
    ASSERT_EQ(app.getDayIndex("null"), Days::MAX_DAYS);
}

TEST(AttendaceManager, getTotalUserCount) {
    AttendanceManager app = AttendanceManager();
    app.loadData();
    ASSERT_EQ(app.getTotalUserCount(), 20);
}

TEST(AttendaceManager, setGrade) {
    AttendanceManager app = AttendanceManager();
    app.loadData();
    app.setGrade();
    app.displayAttendanceResult();
    ASSERT_EQ(app.getRemovedUserCount(), 2);
}