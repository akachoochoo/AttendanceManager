#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "gradeStrategy.h"
#include "user.h"

TEST(GradeAssigner, assign_normal) {

    GradeAssigner gradeAssigner;
    User user(10, "no_name");
    user.addPoint(10);
    ASSERT_EQ(gradeAssigner.assign(user), NORMAL_GRADE);
}

TEST(GradeAssigner, assign_silver) {

    GradeAssigner gradeAssigner;
    User user(10, "no_name");
    user.addPoint(40);
    ASSERT_EQ(gradeAssigner.assign(user), SILVER_GRADE);
}

TEST(GradeAssigner, assign_gold) {

    GradeAssigner gradeAssigner;
    User user(10, "no_name");
    user.addPoint(60);
    ASSERT_EQ(gradeAssigner.assign(user), GOLD_GRADE);
}

TEST(GradeAssigner, checkWithdraw) {
    GradeAssigner gradeAssigner;
    User user(10, "no_name");
    user.addPoint(10);
    user.setGrade(gradeAssigner.assign(user));
    gradeAssigner.checkWithdraw(user);
    ASSERT_EQ(user.isRemoved(), true);
}