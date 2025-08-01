#pragma once
#include <string>
#include <map>
using namespace std;

class User {
private:
    int id;
    string name;
    map<int, int> dayCount;
    int totalPoint;
    int grade;
    bool bRemoved;
public:
    string getName();
    int getId();
    void setGrade(int grade);
    int getGrade();
    int getTotalPoint();
    int getWednesdayCount();
    int getWeekendCount();
    void setWithdraw();
    bool isRemoved();
    void addPoint(int point);
    void addAttendance(int day);
    User(int id, string name);
};