// Team_Project_Source.cpp
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include <chrono>

namespace ui {

void clearLine()
{
    std::cout << std::string(60, '-') << '\n';
}

void pause()
{
    std::cout << "계속하려면 Enter 키를 누르세요...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

template <typename T>
T input(const std::string& prompt,
        const std::function<bool(T)>& validator = [](T) { return true; })
{
    T value{};
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && validator(value))
            break;

        std::cout << "입력이 잘못되었습니다. 다시 시도하세요.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flush '\n'
    return value;
}

std::string inputLine(const std::string& prompt,
                      const std::function<bool(const std::string&)>& validator =
                          [](const std::string&) { return true; })
{
    std::string value;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, value);
        if (validator(value))
            break;
        std::cout << "입력이 잘못되었습니다. 다시 시도하세요.\n";
    }
    return value;
}

} // namespace ui

struct Student {
    int          number{};
    std::string  name;
    std::string  subject;
    std::string  place;
    int          month{};
    int          day{};
    int          hour{};
    int          minute{};
};

enum class Menu {
    None   = 0,
    Insert = 1,
    Delete,
    Search,
    Output,
    Exit
};

class ReservationSystem {
public:
    void run();

private:
    // CRUD 기능
    void insertStudent();
    void deleteStudent();
    void searchStudent() const;
    void outputStudents() const;

    // 내부 헬퍼
    Student* findByName(const std::string& name);
    const Student* findByName(const std::string& name) const;

    // 데이터
    std::vector<Student> students_;
    int nextNumber_ = 1;
};

void ReservationSystem::run()
{
    while (true) {
        ui::clearLine();
        std::cout <<
            "     --------<  자격증 시험 예약 프로그램 >---------\n"
            "    |                                               |\n"
            "    |  1. 자격증 시험 예약하기                      |\n"
            "    |  2. 자격증 시험 취소하기                      |\n"
            "    |  3. 자격증 시험 수험생 탐색하기               |\n"
            "    |  4. 자격증 시험 수험생 전체 출력하기          |\n"
            "    |  5. 종료하기                                  |\n"
            "     -----------------------------------------------\n";

        int choice = ui::input<int>("메뉴를 선택하세요: ",
                                    [](int v) { return v >= 1 && v <= 5; });

        switch (static_cast<Menu>(choice)) {
            case Menu::Insert:  insertStudent();  break;
            case Menu::Delete:  deleteStudent();  break;
            case Menu::Search:  searchStudent();  break;
            case Menu::Output:  outputStudents(); break;
            case Menu::Exit:    std::cout << "프로그램을 종료합니다.\n"; return;
            default:            break;
        }
        ui::pause();
    }
}

void ReservationSystem::insertStudent()
{
    ui::clearLine();
    std::cout << "========== 자격증 시험 예약 입력 ==========\n";

    Student s;
    s.number  = nextNumber_++;
    s.name    = ui::inputLine("이름을 입력하세요: ",
                              [](const std::string& v){ return !v.empty(); });
    s.subject = ui::inputLine("응시 종목을 입력하세요: ",
                              [](const std::string& v){ return !v.empty(); });
    s.place   = ui::inputLine("시험 장소를 입력하세요: ",
                              [](const std::string& v){ return !v.empty(); });

    s.month  = ui::input<int>("시험 월(1~12): ",
                              [](int m){ return m >= 1 && m <= 12; });
    s.day    = ui::input<int>("시험 일(1~31): ",
                              [](int d){ return d >= 1 && d <= 31; });
    s.hour   = ui::input<int>("시험 시(0~23): ",
                              [](int h){ return h >= 0 && h <= 23; });
    s.minute = ui::input<int>("시험 분(0~59): ",
                              [](int m){ return m >= 0 && m <= 59; });

    students_.push_back(std::move(s));
    std::cout << "예약이 완료되었습니다.\n";
}

void ReservationSystem::deleteStudent()
{
    if (students_.empty()) {
        std::cout << "삭제할 예약이 없습니다.\n";
        return;
    }

    ui::clearLine();
    std::string name = ui::inputLine("삭제할 수험생 이름: ");

    auto it = std::remove_if(students_.begin(), students_.end(),
                             [&](const Student& s){ return s.name == name; });

    if (it == students_.end()) {
        std::cout << "일치하는 수험생이 없습니다.\n";
        return;
    }

    students_.erase(it, students_.end());
    std::cout << "삭제가 완료되었습니다.\n";
}

void ReservationSystem::searchStudent() const
{
    if (students_.empty()) {
        std::cout << "검색할 예약이 없습니다.\n";
        return;
    }

    ui::clearLine();
    std::string name = ui::inputLine("검색할 수험생 이름: ");

    const Student* s = findByName(name);
    if (!s) {
        std::cout << "일치하는 수험생이 없습니다.\n";
        return;
    }

    int currentYear = std::chrono::year_month_day(
        std::chrono::floor<std::chrono::days>(
            std::chrono::system_clock::now())).year();

    std::cout << s->number << "번째 수험생\n"
              << "이름       : " << s->name    << '\n'
              << "응시 종목  : " << s->subject << '\n'
              << currentYear << "년 "
              << s->month  << "월 "
              << s->day    << "일\n"
              << s->hour   << "시 "
              << s->minute << "분\n";
}

void ReservationSystem::outputStudents() const
{
    if (students_.empty()) {
        std::cout << "등록된 예약이 없습니다.\n";
        return;
    }

    ui::clearLine();
    int currentYear = std::chrono::year_month_day(
        std::chrono::floor<std::chrono::days>(
            std::chrono::system_clock::now())).year();

    for (const auto& s : students_) {
        std::cout << s.number << "번째 수험생\n"
                  << "이름       : " << s.name    << '\n'
                  << "응시 종목  : " << s.subject << '\n'
                  << currentYear << "년 "
                  << s.month  << "월 "
                  << s.day    << "일\n"
                  << s.hour   << "시 "
                  << s.minute << "분\n";
        ui::clearLine();
    }
}

Student* ReservationSystem::findByName(const std::string& name)
{
    auto it = std::find_if(students_.begin(), students_.end(),
                           [&](const Student& s){ return s.name == name; });
    return it == students_.end() ? nullptr : &(*it);
}

const Student* ReservationSystem::findByName(const std::string& name) const
{
    auto it = std::find_if(students_.cbegin(), students_.cend(),
                           [&](const Student& s){ return s.name == name; });
    return it == students_.cend() ? nullptr : &(*it);
}

// ---------- 프로그램 시작점 ----------
int main()
{
    std::ios::sync_with_stdio(false); // I/O 성능 향상
    std::cin.tie(nullptr);

    ReservationSystem app;
    app.run();
    return 0;
}
