// #include <iostream>
// #include <array>
// #include <cstdint>

class BlackHole {
    int mass;
public:
    BlackHole(size_t mass) : mass(mass) {}

    size_t get_mass() const {
        return mass;
    }

    template <typename T>
    void consume(T* arg) {
        if (arg == nullptr) {
            std::cout << "There is nothing to consume" << std::endl;
            return;
        }

        size_t arg_mass = sizeof(*arg);
        if (std::is_const<T>::value) {
            std::cout << "Black hole consumed " << arg_mass << " const bytes" << std::endl;
        } else {
            std::cout << "Black hole consumed " << arg_mass << " non-const bytes" << std::endl;
        }

        mass += arg_mass;
        delete arg;

        return;
    }

    void consume(void* arg) {
        throw std::runtime_error("Black hole has tried to consume void");

        return;
    }

    void consume(const void* arg) {
        throw std::runtime_error("Black hole has tried to consume void");

        return;
    }

    void consume(BlackHole* arg) {
        if (arg == this) {
            throw std::runtime_error("Black hole has tried to consume itself");

            return;
        }

        size_t arg_mass = arg->get_mass();
        if (std::is_const<BlackHole>::value) {
            std::cout << "Black hole consumed " << arg_mass << " const bytes" << std::endl;
        } else {
            std::cout << "Black hole consumed " << arg_mass << " non-const bytes" << std::endl;
        }

        mass += arg_mass;
        delete arg;

        return;
    }

    void consume(const BlackHole* arg) {
        if (arg == this) {
            throw std::runtime_error("Black hole has tried to consume itself");

            return;
        }

        size_t arg_mass = arg->get_mass();
        if (std::is_const<BlackHole>::value) {
            std::cout << "Black hole consumed " << arg_mass << " const bytes" << std::endl;
        } else {
            std::cout << "Black hole consumed " << arg_mass << " non-const bytes" << std::endl;
        }

        mass += arg_mass;
        delete arg;

        return;
    }

    template <typename T>
    void consume(T arg) {
        throw std::runtime_error("Black hole has tried to consume non-pointer");

        return;
    }

    ~BlackHole() = default;
};

/*
Требуется реализовать класс BlackHole.

1) Конструктор класса должен принимать аргумент типа size_t, задающий массу чёрной дыры.

2) У класса должен быть метод get_mass() возвращающий текущую массу.

3) У класса должен быть шаблонный метод consume(arg), предназначенный для "поглощения" указателей (см. ниже) и способный принимать аргументы любых типов.

Вызов consume должен вести себя следующим образом.

1) Он должен выбрасывать исключение типа runtime_error (тексты исключений следует взять из примера вывода ниже) в следующих ситуациях:

- При передаче ему аргумента, не являющегося указателем

- Если переданный указатель указывает на void (константный или неконстантный)

- Если чёрная дыра пытается поглотить саму себя

2) Если в качестве аргумента передан нулевой указатель, следует напечатать "There is nothing to consume" и ничего не делать.

3) Если ни одно из выше перечисленных условий не сработало, то аргумент считается корректным указателем и для него нужно выполнить следующие действия:

- Определить "массу" аргумента. Для BlackHole масса определяется через вызов get_mass(), для остальных - через размер указываемого типа в байтах.

- Напечатать "Black hole consumed N non-const bytes", где вместо N нужно подставить массу аргумента. Если в качестве аргумента передан указатель на константный тип, то вместо non-const следует печатать const.

- Добавить массу аргумента к текущей массе чёрной дыры.

- Удалить аргумент через вызов delete.

При подстановке решения студента, следующий код должен работать:
*/

// int main() {
//     BlackHole hole(100);
//     std::cout << "The initial mass is " << hole.get_mass() << " bytes" << std::endl;

//     hole.consume(new int64_t);
//     hole.consume(const_cast <const int64_t*>(new int64_t));
//     hole.consume(new int32_t);
//     hole.consume(static_cast<char*>(nullptr));
//     hole.consume(new BlackHole{ 50 });
//     hole.consume(new std::array<char, 64>);

//     try {
//         hole.consume(5);
//     }
//     catch (std::runtime_error& err) {
//         std::cout << "Error: " << err.what() << std::endl;
//     }

//     try {
//         hole.consume(&hole);
//     }
//     catch (std::runtime_error& err) {
//         std::cout << "Error: " << err.what() << std::endl;
//     }

//     try {
//         hole.consume((void*) nullptr);
//     }
//     catch (std::runtime_error& err) {
//         std::cout << "Error: " << err.what() << std::endl;
//     }

//     std::cout << "The total mass is: " << hole.get_mass() << " bytes" << std::endl;

//     return 0;
// }