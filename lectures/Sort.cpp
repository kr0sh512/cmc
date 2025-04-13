
/*
Сортировка

Необходимо реализовать функцию filter_sort, которая принимает контейнер с произвольным доступом к элементам и три лямбда-функции. Первая лямбда задаёт критерий фильтрации элементов контейнера, вторая - порядок первичной сортировки элементов, третья - вторичной сортировки. Файл с решением должен содержать только реализацию шаблонной функции filter_sort. Тип элементов контейнера при тестировании может быть любым.

После подстановки вашей реализации, приведенный ниже код должен работать (при тестировании код отличается) и выдавать для примера ввода ниже пример вывода ниже:

*/

// #include <iostream>
// #include <vector>
// #include <string>
// #include <optional>
// #include <algorithm>
// #include <iterator>

// struct Student {
//     std::string full_name;
//     int group_no;

//     void print() const {
//         std::cout << group_no << " " << full_name << std::endl;
//     }

//     static std::optional<Student> read() {
//         Student student;
//         if (!(std::cin >> student.group_no))
//             return {};
//         std::cin >> std::ws;
//         if (!std::getline(std::cin, student.full_name))
//             return {};
//         return student;
//     }
// };

// Your filter_sort is here!

template <typename Container, typename Filter, typename PrimarySort, typename SecondarySort>
void filter_sort(Container& container, Filter filter, PrimarySort primary_sort, SecondarySort secondary_sort) {
    auto it = std::remove_if(container.begin(), container.end(), [=](auto& item) { return !filter(item); });
    container.erase(it, container.end());

    std::stable_sort(container.begin(), container.end(), [=](auto item1, auto item2) { return secondary_sort(item1, item2); });
    std::stable_sort(container.begin(), container.end(), [=](auto item1, auto item2) { return primary_sort(item1, item2); });

    return;
}

// int main() {
//     std::vector<Student> students;
//     while (auto student = Student::read())
//         students.push_back(*student);

//     filter_sort(students, // the container
//         [](Student& stud) { return stud.group_no >= 0; }, // filter
//         // [](const Student stud_1, const Student stud_2) { return stud_1.group_no < stud_2.group_no; }, // primary sort
//         [](Student& stud_1, Student& stud_2) { return stud_1.group_no < stud_2.group_no; }, // primary sort
//         // [](const Student stud_1, const Student stud_2) { return stud_1.full_name < stud_2.full_name; }  // secondary sort
//         [](Student& stud_1, Student& stud_2) { return stud_1.full_name < stud_2.full_name; }  // secondary sort
//     );

//     // filter_sort(students, // the container
//     //     [](Student& stud) { return stud.group_no >= 0; }, // filter
//     //     [](Student& stud_1, Student& stud_2) { return stud_1.group_no < stud_2.group_no; }, // primary sort
//     //     [](Student& stud_1, Student& stud_2) { return stud_1.full_name < stud_2.full_name; }  // secondary sort
//     // );

//     for (auto& student : students)
//         student.print();

//     return 0;
// }

/*

Примеры
Входные данные

-100 Иванов Иван
300 Забугоркина Афродита
0 Смирнова Настя
0 Смирнова Анастасия

Результат работы

0 Смирнова Анастасия
0 Смирнова Настя
300 Забугоркина Афродита
*/