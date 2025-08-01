#include "attendancemanager.h"
#include "user.h"
#include "gradeStrategy.h"

AttendanceManager::AttendanceManager()
{
	userCount = 1;
}

Days AttendanceManager::getDayIndex(const string& day)
{
	if (day == "monday") return MON;
	else if (day == "tuesday") return TUE;
	else if (day == "wednesday") return WED;
	else if (day == "thursday") return THU;
	else if (day == "friday") return FRI;
	else if (day == "saturday") return SAT;
	else if (day == "sunday") return SUN;

	return MAX_DAYS;
}

int AttendanceManager::getPoint(Days day) {
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

void AttendanceManager::loadData()
{
	ifstream fin{ "attendance_weekday_500.txt" }; //500개 데이터 입력

	string name, day;
	while (fin >> name >> day) {
		Days dayIndex = getDayIndex(day);
		if (dayIndex == Days::MAX_DAYS) continue;

		if (users.count(name) == 0) {
			users[name] = make_shared<User>(userCount, name);
			userCount++;
		}

		auto& user = users[name];
		int point = AttendanceManager::getPoint(dayIndex);
		user->addPoint(point);
		user->addAttendance(static_cast<int>(dayIndex));
	}
}

void AttendanceManager::setGrade() {
	GradeAssigner gradeAssigner;

	// 등급 산정
	for (auto& user : users) {
		if (user.second->getWednesdayCount() >= BONUS_POINT_CUTOFF) user.second->addPoint(BONUS_POINT);
		if (user.second->getWeekendCount() >= BONUS_POINT_CUTOFF) user.second->addPoint(BONUS_POINT);
		user.second->setGrade(gradeAssigner.assign(*(user.second)));
		gradeAssigner.checkWithdraw(*(user.second));
	}
}
void AttendanceManager::displayUserGrade() {
	// 결과 출력
	for (auto user : users) {		
		cout << "NAME : " << user.second->getName() << ", ";
		cout << "POINT : " << user.second->getTotalPoint() << ", ";
		cout << "GRADE : ";

		int grade = user.second->getGrade();
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

void AttendanceManager::displayRemovedUser() {
	removedUserCount = 0;
	std::cout << "Removed player\n";
	std::cout << "==============\n";
	for (auto user : users) {
		if (user.second->isRemoved()) {
			std::cout << user.second->getName() << "\n";
			removedUserCount++;
		}
	}
}

void AttendanceManager::displayAttendanceResult() {
	displayUserGrade();
	std::cout << "\n";
	displayRemovedUser();
}

int AttendanceManager::getTotalUserCount()
{
	return userCount;
}

int AttendanceManager::getRemovedUserCount()
{
	return removedUserCount;
}
