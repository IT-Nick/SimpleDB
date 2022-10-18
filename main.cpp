#include <iostream>
#include <sstream>
#include <set>
#include <map>
#include <iomanip>
#include <stdexcept>

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
    int year;
    int month;
    int day;
public:
    void SetDate(int new_year, int new_month, int new_day) {
        year = new_year;
        if (new_month > 12 || new_month < 1) {
            throw std::logic_error("Month value is invalid: " + std::to_string(new_month));
        }
        month = new_month;
        if (new_day > 31 || new_day < 1) {
            throw std::logic_error("Day value is invalid: " + std::to_string(new_day));
        }
        day = new_day;
    }
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

bool operator<(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            return lhs.GetDay() < rhs.GetDay();
        }
        return lhs.GetMonth() < rhs.GetMonth();
    }
    return lhs.GetYear() < rhs.GetYear();
}

std::istream& operator>>(std::istream& input, Date& date) {
    string dateStr;
    input >> dateStr;
    stringstream ss(dateStr);
    bool ok = true;
    int year;
    ok = bool(ss >> year);
    ok = ok && (ss.peek() == '-');
    ss.ignore(1);

    int month;
    ok = ok && (ss >> month);
    ok = ok && (ss.peek() == '-');
    ss.ignore(1);

    int day;
    ok = ok && (ss >> day);
    ok = ok && ss.eof();

    if (!ok) {
        throw std::logic_error("Wrong date format: " + dateStr);
    }

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
    size_t DeleteDate(const Date& date) {
        size_t eCount = 0;
        if(db.count(date)) {
            eCount = db[date].size();
        }
        db.erase(date);
        return eCount;
    }

    set<string> Find(const Date& date) const {
        set<string> events;
        if(db.count(date)) {
            for (const auto &event: db.at(date)) {
                events.insert(event);
            }
        }
        return events;
    }

    void Print() const {
        for(const auto& i : db) {
            for(const auto& j : i.second) {
                if(i.first.GetYear() != -1) {
                    cout << setfill('0');
                    cout << setw(4) << i.first.GetYear() << '-' << setw(2)
                         << i.first.GetMonth() << '-' << setw(2) << i.first.GetDay()
                         << ' ' << j << endl;
                }
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
        try {
            ss >> cmd;
            if (cmd == "Add") {
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
                if (event.empty()) {
                    cout << "Deleted " << db.DeleteDate(date) << " events" << endl;
                } else {
                    if (db.DeleteEvent(date, event)) {
                        cout << "Deleted successfully" << endl;
                    } else {
                        cout << "Event not found" << endl;
                    }
                }
            } else if (cmd == "Print") {
                db.Print();
            }  else if (!cmd.empty()) {
                throw std::logic_error("Unknown command: " + command);
            }
        } catch (const std::exception& e) {
            cout << e.what() << endl;
        }
    }

    return 0;
}
