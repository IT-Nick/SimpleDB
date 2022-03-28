// Реализуйте функции и методы классов и при необходимости добавьте свои
#include <iostream>
#include <sstream>
#include <set>
#include <map>
#include <iomanip>

using std::map;
using std::set;
using std::stringstream;
using std::setw;
using std::setfill;
using std::string;
using std::cout;
using std::cin;
using std::endl;

class Date {
private:
    int year = 0;
    int month = 0;
    int day = 0;
public:
    void SetDate(int new_year, int new_month, int new_day) {
        year = new_year;
        month = new_month;
        day = new_day;
    };
    int GetYear() const {
        return year;
    }
    int GetMonth() const {
        return month;
    }
    int GetDay() const {
        return day;
    }
};

bool operator<(const Date& lhs, const Date& rhs);

std::istream& operator>>(std::istream& input, Date& date) {
    int year, month, day;
    input >> year;
    input.ignore(1);
    input >> month;
    input.ignore(1);
    input >> day;
    date.SetDate(year, month, day);
    return input;
}

std::ostream& operator<<(std::ostream& output, const set<string>& events) {
    for(const auto& event : events) {
        output << event << endl;
    }
    return output;
}

class Database {
private:
    map<Date, set<string>> db;
public:
    void AddEvent(const Date& date, const string& event) {
        db[date].insert(event);
    }
    bool DeleteEvent(const Date& date, const string& event) {
        if (db.count(date) && db[date].count(event)) {
            db[date].erase(event);
            return true;
        }
        return false;
    }
    size_t  DeleteDate(const Date& date) {
        size_t eCount = 0;
        if(db.count(date)) {
            eCount = db[date].size();
        }
        db.erase(date);
        return eCount;
    }

    set<string> Find(const Date& date) const {
        set<string> events;
        for(const auto &event : db.at(date)) {
            events.insert(event);
        }
        return events;
    }

    void Print() const {
        for(const auto& i : db) {
            for(const auto& j : i.second) {
                cout << setfill('0');
                cout << setw(4) << i.first.GetYear() << '-' << setw(2)
                << i.first.GetMonth() << '-' << setw(2) << i.first.GetDay()
                << ' ' << j << endl;
            }
        }
    }
};

int main() {
    Database db;

    string command;
    while (getline(cin, command)) {

        stringstream ss(command);

        string cmd;
        ss >> cmd;
        if(cmd == "Add") {
            Date date;
            string event;
            ss >> date;
            ss >> event;
            db.AddEvent(date, event);
        } else if (cmd == "Find") {
            Date date;
            ss >> date;
            cout << db.Find(date);
        } else if (cmd == "Del") {
            Date date;
            ss >> date;
            string event;
            ss >> event;
            if(event.empty()) {
                db.DeleteDate(date);
            } else {
                db.DeleteEvent(date, event);
            }
        } else if (cmd == "Print") {
            Date date;
            ss >> date;
            db.Print();
        }
    }

    return 0;
}