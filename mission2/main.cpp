#include "gmock/gmock.h"
#include "attendancemanager.h"
#include "user.h"
#include "gradeStrategy.h"

using namespace std;

#ifdef _DEBUG

int main(int argc, char** argv) {
	::testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}

#else 
int main() {
    AttendanceManager app = AttendanceManager();
    app.loadData();
    app.setGrade();
    app.displayAttendanceResult();
}
#endif



/*
#include <iostream>
#include <fstream>
#include <map>
#include <memory>
#include "User.h"
#include "Days.h"
#include "ScoreStrategy.h"
#include "GradeStrategy.h"

using namespace std;

int main() {
    ifstream fin("attendance_weekday_500.txt");
    if (!fin.is_open()) {
        cerr << "������ �� �� �����ϴ�.\n";
        return 1;
    }

    map<string, shared_ptr<User>> users;
    int idCounter = 1;

    // ���� ��ü ����
    DefaultScoreStrategy scoreStrategy;
    GradeAssigner gradeAssigner;
    gradeAssigner.addStrategy(make_shared<GoldGradeStrategy>());
    gradeAssigner.addStrategy(make_shared<SilverGradeStrategy>());
    gradeAssigner.addStrategy(make_shared<NormalGradeStrategy>());

    string name, dayStr;

    // ������ �Է� ó��
    while (fin >> name >> dayStr) {
        Days day = getDayIndex(dayStr);
        if (day == Days::MAX_DAYS) continue;

        if (users.count(name) == 0) {
            users[name] = make_shared<User>();
            users[name]->id = idCounter++;
            users[name]->name = name;
        }

        auto& user = users[name];
        int point = scoreStrategy.calculatePoint(*user, day);
        user->addPoint(point);
        user->addAttendance(day);
    }

    // ���ʽ� ���� ����
    for (auto& [_, user] : users) {
        if (user->attendance[Days::WED] >= 10) user->addPoint(10);
        int weekendCount = user->attendance[Days::SAT] + user->attendance[Days::SUN];
        if (weekendCount >= 10) user->addPoint(10);
    }

    // ��� ����
    for (auto& [_, user] : users) {
        user->grade = gradeAssigner.assign(*user);
    }

    // ��� ���
    cout << "=== ����� ��� ��Ȳ ===\n";
    for (auto& [_, user] : users) {
        cout << "ID: " << user->id
             << ", Name: " << user->name
             << ", Point: " << user->totalPoint
             << ", Grade: ";
        if (user->grade == 3) cout << "GOLD";
        else if (user->grade == 2) cout << "SILVER";
        else cout << "NORMAL";
        cout << "\n";
    }

    // Ż�� ����� ���
    cout << "\n=== Ż�� �ǰ� ����� ===\n";
    for (auto& [_, user] : users) {
        if (user->grade == 1 &&
            user->attendance[Days::WED] == 0 &&
            user->attendance[Days::SAT] + user->attendance[Days::SUN] == 0) {
            cout << user->name << "\n";
        }
    }

    return 0;
}
*/