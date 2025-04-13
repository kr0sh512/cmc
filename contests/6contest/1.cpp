#include <iterator>

template <typename Container>
typename Container::value_type process(const Container& container) {
    using ValueType = typename Container::value_type;

    if (container.empty()) {
        return ValueType{};
    }

    auto it = container.rbegin();
    ValueType sum = *it;

    for (int i = 0; it != container.rend() && i < 5; ++i, ++it) {
        if (i == 2 || i == 4) {
            sum += *it;
        }
    }

    return sum;
}