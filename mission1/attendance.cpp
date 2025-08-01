#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

constexpr int MAX_DAYS = 7;
constexpr int MAX_USER = 100;
constexpr int MAX_INPUT = 500;
// POINT
constexpr int DEFAULT_POINT = 1;
constexpr int WEEKEND_POINT = 2;
constexpr int WEDNESDAY_POINT = 3;
constexpr int BONUS_POINT_CUTOFF = 10;
constexpr int BONUS_POINT = 10;
// GRADE
constexpr int NORMAL_GRADE = 1;
constexpr int SILVER_GRADE = 2;
constexpr int SILVER_GRADE_POINT = 30;
constexpr int GOLD_GRADE = 3;
constexpr int GOLD_GRADE_POINT = 50;

// map user_name to user_id
map<string, int> nameToIDMap;
int id_cnt = 0;

//dat[사용자ID][요일]
int attendanceData[MAX_USER][MAX_DAYS];
int points[MAX_USER];
int grade[MAX_USER];
string names[MAX_USER];

enum class Days { 
	MON, 
	TUE, 
	WED, 
	THU,
	FRI, 
	SAT, 
	SUN,
	MAX_DAYS
};

int getWednesdayAttendance(int id) {
	return attendanceData[id][static_cast<int>(Days::WED)];
}

int getWeekendAttendance(int id) {
	return attendanceData[id][static_cast<int>(Days::SAT)] + attendanceData[id][static_cast<int>(Days::SUN)];
}

Days getDayIndex(const string& day)
{
	if (day == "monday") return Days::MON;
	else if (day == "tuesday") return Days::TUE;
	else if (day == "wednesday") return Days::WED;
	else if (day == "thursday") return Days::THU;
	else if (day == "friday") return Days::FRI;
	else if (day == "saturday") return Days::SAT;
	else if (day == "sunday") return Days::SUN;

	return Days::MAX_DAYS;
}

int getPoint(int id, Days day) {
	switch (day)	
	{
	case Days::MON:
	case Days::TUE:
		return DEFAULT_POINT;
	case Days::WED:
		return WEDNESDAY_POINT;
	case Days::THU:
	case Days::FRI:
		return DEFAULT_POINT;
	case Days::SAT:
	case Days::SUN:
		return WEEKEND_POINT;
	default:
		break;
	}

	return 0;
}

int getUserID(string name) {
	if (nameToIDMap.count(name) == 0) {
		nameToIDMap.insert({ name, ++id_cnt });
		names[id_cnt] = name;
	}

	return nameToIDMap[name];
}

string getUserName(int id) {
	return names[id];
}

int getTotalPoint(int id) {
	return points[id];
}

int getGrade(int id) {
	return grade[id];
}

void updateUserData(string name, string day) {
	//ID 부여
	int id = getUserID(name);	
	Days index = getDayIndex(day);
	int add_point = getPoint(id, index);

	if (index == Days::MAX_DAYS) return;
	if (add_point < DEFAULT_POINT) return;

	//사용자ID별 요일 데이터에 1씩 증가
	attendanceData[id][static_cast<int>(index)] += 1;
	points[id] += add_point;
}

void updateBonusScore() {
	for (int id = 1; id <= id_cnt; id++) {
		if (getWednesdayAttendance(id) >= BONUS_POINT_CUTOFF) {
			points[id] += BONUS_POINT;
		}

		if (getWeekendAttendance(id) >= BONUS_POINT_CUTOFF) {
			points[id] += BONUS_POINT;
		}
	}
}

void updateGrade() {
	for (int id = 1; id <= id_cnt; id++) {
		if (points[id] >= GOLD_GRADE_POINT) {
			grade[id] = GOLD_GRADE;
		}
		else if (points[id] >= SILVER_GRADE_POINT) {
			grade[id] = SILVER_GRADE;
		}
		else {
			grade[id] = NORMAL_GRADE;
		}
	}
}

void loadAttendance() {
	ifstream fin{ "attendance_weekday_500.txt" }; //500개 데이터 입력

	for (int i = 0; i < MAX_INPUT; i++) {
		string name, day;
		fin >> name >> day;
		updateUserData(name, day);
	}

	updateBonusScore();
	updateGrade();
}

void displayUserGade() {
	for (int id = 1; id <= id_cnt; id++) {
		cout << "NAME : " << getUserName(id) << ", ";
		cout << "POINT : " << getTotalPoint(id) << ", ";
		cout << "GRADE : ";

		int grade = getGrade(id);
		if (grade == GOLD_GRADE) {
			cout << "GOLD" << "\n";
		}
		else if (grade == SILVER_GRADE) {
			cout << "SILVER" << "\n";
		}
		else {
			cout << "NORMAL" << "\n";
		}
	}
}

bool isRemoved(int id) {
	int grade = getGrade(id);
	if (grade == NORMAL_GRADE && getWednesdayAttendance(id) == 0 && getWeekendAttendance(id) == 0) return true;
	else return false;
}

void displayRemovedPalyer() {
	std::cout << "Removed player\n";
	std::cout << "==============\n";
	for (int id = 1; id <= id_cnt; id++) {
		if (isRemoved(id))
			std::cout << names[id] << "\n";
	}
}

void displayAttendaceResult() {
	displayUserGade();
	std::cout << "\n";
	displayRemovedPalyer();
}

int main() {
	loadAttendance();
	displayAttendaceResult();
}
