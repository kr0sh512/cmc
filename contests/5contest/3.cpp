#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>
#include <iomanip>
#include <set>

struct Date {
    int Y;
    int M;
    int D;

    Date(std::string s) {
        std::stringstream ss;
        ss << s;
        
        char tmp;
        ss >> Y >> tmp >> M >> tmp >> D;
    }

    Date(int Y, int M, int D) : Y(Y), M(M), D(D) {}

    bool operator<(const Date d) const {
        if (Y < d.Y) return true;
        if (Y > d.Y) return false;

        if (M < d.M) return true;
        if (M > d.M) return false;

        if (D < d.D) return true;
        
        return false;
    }

};

struct Student {
    std::map<Date, int> scores;
    std::string name;

    Student(std::string name) : name(name) {}

    Student(const Student& s) {
        scores = s.scores;
        name = s.name;
    }

    bool operator==(const std::string n) {
        return n == name;
    }

    bool operator<(const Student st) const {
        return name < st.name;
    }
};

int main() {
    std::set<Student> studs;
    std::set<Date> dates;

    std::string name, date;
    int grade;
    while (std::cin >> name >> date >> grade) {
        std::set<Student>::iterator iter = studs.find(name);
        Date d(date);
        
        if (iter == studs.end()) {
            Student s(name);
            s.scores[d] = grade;
            studs.insert(s);
        } else {
            Student s(*iter);
            s.scores[d] = grade;
            studs.erase(iter);
            studs.insert(s);
        }

        dates.insert(d);
    }

    // std::cout << studs.size() << std::endl;
    // std::cout << studs[0].name << studs[0].scores.size() << std::endl;

    // std::sort(dates.begin(), dates.end());
    // std::sort(studs.begin(), studs.end());

    std::cout << '.' << "\t";
    for (auto& date : dates) {
        std::cout << std::setfill('0')
              << std::setw(4) << date.Y << '/'
              << std::setw(2) << date.M << '/'
              << std::setw(2) << date.D << '\t';
    }
    std::cout << std::endl;

    for (auto st : studs) {
        std::cout << st.name << '\t';

        for (auto date : dates) {
            if (st.scores.find(date) == st.scores.end()) {
                std::cout << '.' << '\t';
            } else {
                std::cout << st.scores[date] << '\t';
            }
        }

        std::cout << std::endl;
    }

    return 0;
}

