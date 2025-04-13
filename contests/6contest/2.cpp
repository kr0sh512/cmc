// #include <iostream>
// #include <vector>
#include <iterator>

template <typename Container, typename Predicate>
Container myfilter(const Container& container, Predicate pred) {
    Container result;

    for (const auto& x : container) {
        if (pred(x)) {
            result.insert(result.end(), x);
        }
    }

    return result;
}
