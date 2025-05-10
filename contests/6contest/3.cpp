#include <iostream>
#include <vector>
#include <functional>


template <typename It, typename F>
void myapply(It first, It last, F f) {
    for (It it = first; it != last; ++it) {
        f(*it);
    }

    return;
}

template <typename It, typename Pred>
std::vector<std::reference_wrapper<typename std::iterator_traits<It>::value_type>> myfilter2(It first, It last, Pred f) {
    std::vector<std::reference_wrapper<typename std::iterator_traits<It>::value_type>> result;

    for (It it = first; it != last; ++it) {
        if (f(*it)) {
            result.push_back(std::ref(*it));
        }
    }

    return result;
}
