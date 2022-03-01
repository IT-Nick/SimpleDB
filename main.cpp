#include <iostream>

class Date {
    int GetYear() const;
    int GetMounth() const;
    int GetDay() const;
};

bool operator < (const Date& lhs, const Date& rhs);

class Database {
public:
    void AddEvent(const Date& date, const std::string& event);
    bool DeleteEvent(const Date& date, const std::string& event);
    int DeleteDate(const Date& date);

    void Find(const Date& date) const;

    void Print() const;
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
                int date, events;
                std::cin >> date >> events;
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

                break;
            }
        }
    }

    return 0;
}
