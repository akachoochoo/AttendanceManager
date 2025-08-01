#pragma once
#include <string>
#include <memory>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "user.h"
using namespace std;

constexpr int DEFAULT_POINT = 1;
constexpr int WEEKEND_POINT = 2;
constexpr int WEDNESDAY_POINT = 3;
constexpr int BONUS_POINT_CUTOFF = 10;
constexpr int BONUS_POINT = 10;

enum Days {
	MON,
	TUE,
	WED,
	THU,
	FRI,
	SAT,
	SUN,
	MAX_DAYS
};

class AttendanceManager {
private:
	int userCount;
	int removedUserCount;
	map<string, shared_ptr<User>> users;
public:
	AttendanceManager();
	void loadData();
	void setGrade();
	Days getDayIndex(const string& day);
	int getPoint(Days day);
	void displayUserGrade();
	void displayRemovedUser();
	void displayAttendanceResult();
	int getTotalUserCount();
	int getRemovedUserCount();
};