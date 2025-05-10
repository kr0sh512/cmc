#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

std::chrono::system_clock::time_point parse_date(const std::string& date_str) {
    std::tm tm = {};
    std::istringstream ss(date_str);
    ss >> std::get_time(&tm, "%Y-%m-%d");

    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

int days_between(const std::chrono::system_clock::time_point& start, const std::chrono::system_clock::time_point& end) {
    auto duration = end - start;

    return std::chrono::duration_cast<std::chrono::hours>(duration).count() / 24;
}

int main() {
    int sum = 0;

    std::string date1, date2;
    std::cin >> date1;

    while (std::cin >> date2) {
        auto start = parse_date(date1);
        auto end = parse_date(date2);

        sum += std::abs(days_between(start, end));

        date1 = date2;
    }

    std::cout << sum << std::endl;

    return 0;
}