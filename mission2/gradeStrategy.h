#pragma once
#include <vector>
#include <memory>
#include "User.h"

constexpr int DEFAULT_GRADE = 0;
constexpr int NORMAL_GRADE = 1;
constexpr int SILVER_GRADE = 2;
constexpr int SILVER_GRADE_POINT = 30;
constexpr int GOLD_GRADE = 3;
constexpr int GOLD_GRADE_POINT = 50;

class IGradeStrategy {
public:
    virtual bool match(User& user) const = 0;
    virtual int getGrade() const = 0;
    virtual ~IGradeStrategy() {}
};

class GoldGradeStrategy : public IGradeStrategy {
public:
    bool match(User& user) const override {
        return user.getTotalPoint() >= GOLD_GRADE_POINT;
    }

    int getGrade() const override {
        return GOLD_GRADE;
    }
};

class SilverGradeStrategy : public IGradeStrategy {
public:
    bool match(User& user) const override {
        return user.getTotalPoint() >= SILVER_GRADE_POINT && user.getTotalPoint() < GOLD_GRADE_POINT;
    }

    int getGrade() const override {
        return SILVER_GRADE;
    }
};

class NormalGradeStrategy : public IGradeStrategy {
public:
    bool match(User& user) const override {
        return user.getTotalPoint() < SILVER_GRADE_POINT;
    }

    int getGrade() const override {
        return NORMAL_GRADE;
    }
};


class GradeAssigner {
private:
    vector<shared_ptr<IGradeStrategy>> strategies;
public:
    void addStrategy(shared_ptr<IGradeStrategy> s) {
        strategies.push_back(s);
    }

    int assign(User& user) {
        for (auto& strategy : strategies) {
            if (strategy->match(user)) return strategy->getGrade();
        }
        return DEFAULT_GRADE;
    }

    void checkWithdraw(User& user) {
        if (user.getGrade() == NORMAL_GRADE && user.getWednesdayCount() == 0 && user.getWeekendCount() == 0)
            user.setWithdraw();
    }

    GradeAssigner() {
        addStrategy(make_shared<GoldGradeStrategy>());
        addStrategy(make_shared<SilverGradeStrategy>());
        addStrategy(make_shared<NormalGradeStrategy>());
    }
};