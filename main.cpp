#include <iostream>
#include <sstream>
#include <map>
#include <set>

class Date {
public:
    Date(std::string date) {
        std::stringstream ss;
        ss << date;
        ss >> year;
        ss.ignore(1);
        ss >> month;
        ss.ignore(1);
        ss >> day;
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
private:
    int year;
    int month;
    int day;
};

bool operator < (const Date& lhs, const Date& rhs) {
    return lhs.GetYear() < rhs.GetYear();
}

std::ostream& operator << (std::ostream& os, const std::set<std::string>& s) {
    for(auto it = s.begin(); it != s.end(); ++it) {
        os << *it;
    }
    return os;
}


class Database {
public:
    void AddEvent(const Date& date, const std::string& event) {
        db[date].insert(event);
    }
    bool DeleteEvent(const Date& date, const std::string& event);
    int DeleteDate(const Date& date);

    void Find(const Date& date) const;

    std::map<Date, std::set<std::string>> Print() const {
        return db;
    }
private:
    std::map<Date, std::set<std::string>> db;
};

enum class RequestEvents {
    ADD,
    DEL,
    FIND,
    PRINT
};

int main() {
    int request_num;
    std::cin >> request_num;
    RequestEvents request;
    request = static_cast<RequestEvents>(request_num);
    Database db;
    std::string command;
    while (getline(std::cin, command)) {
        switch (request) {
            //добавление события
            case RequestEvents::ADD: {
                std::string input, event;
                std::cin >> input >> event;
                Date date(input);
                db.AddEvent(date, event);
                break;
            }
                //удаление события
            case RequestEvents::DEL: {
                int date, events;
                std::cin >> date >> events;
                break;
            }
                //поиск событий за конкретную дату
            case RequestEvents::FIND: {
                int date;
                std::cin >> date;
                break;
            }
                //печать всех событий за все даты
            case RequestEvents::PRINT: {
                std::map<Date, std::set<std::string>> s = db.Print();
                for(auto it = s.begin(); it != s.end(); ++it) {
                    std::cout << it->first.GetYear() << " "
                    << it->first.GetMonth() << " "
                    << it->first.GetDay() << " "
                    << it->second << " ";
                }
                break;
            }
        }
    }

    return 0;
}
