// #include <iostream>
// #include <memory>
// #include <list>
// #include <vector>

// struct Element {
//     int value;
//     Element(int value) : value(value) {}
// };

// Реализация функции make_safe_vector()

template <typename T>
std::vector<std::unique_ptr<Element>> make_safe_vector(T&& container) {
    std::vector<std::unique_ptr<Element>> result;

    for (auto& el : container)
        result.emplace_back(std::move(el));

    container.clear();

    return result;
}

// int main() {
//     std::vector<Element*> unsafe_vector;
//     unsafe_vector.emplace_back(new Element(0));
//     unsafe_vector.emplace_back(new Element(42));
//     unsafe_vector.emplace_back(new Element(900));

//     auto safe_vector_1 = make_safe_vector(unsafe_vector);
//     unsafe_vector.push_back(new Element(99));

//     auto safe_vector_2 = make_safe_vector(safe_vector_1);

//     auto safe_vector_3 = make_safe_vector(std::list<Element*>{new Element(1), new Element(2), new Element(3)});

//     std::cout << "unsafe_vector: " << std::endl;
//     for (auto& el : unsafe_vector) {
//         std::cout << el->value << std::endl;
//         delete el;
//     }

//     std::cout << "safe_vector_1: " << std::endl;
//     for (auto& el : safe_vector_1)
//         std::cout << el->value << std::endl;

//     std::cout << "safe_vector_2: " << std::endl;
//     for (auto& el : safe_vector_2)
//         std::cout << el->value << std::endl;

//     std::cout << "safe_vector_3: " << std::endl;
//     for (auto& el : safe_vector_3)
//         std::cout << el->value << std::endl;
// }

/*
unsafe_vector:
99
safe_vector_1:
safe_vector_2:
0
42
900
safe_vector_3:
1
2
3
*/