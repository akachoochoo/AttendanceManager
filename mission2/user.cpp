#include "user.h"

User::User(int id, string name) {
    User::id = id;
    User::name = name;
    totalPoint = 0;
    grade = 0;
    bRemoved = false;
}

string User::getName() {
    return name;
}

int User::getId() {
    return id;
}

void User::setGrade(int grade) {
    User::grade = grade;
}

int User::getGrade() {
    return grade;
}

int User::getTotalPoint() {
    return totalPoint;
}

int User::getWednesdayCount() {
    return dayCount[2];
}

int User::getWeekendCount() {
    return dayCount[5] + dayCount[6];
}

void User::setWithdraw() {
    bRemoved = true;
}

bool User::isRemoved() {
    return bRemoved;
}

void User::addPoint(int point) {
    totalPoint += point;
}

void User::addAttendance(int day) {
    dayCount[day] += 1;
}



