#include <set>

template <typename It1, typename It2>
It2 myremove(It1 first1, It1 last1, It2 first2, It2 last2) {
    std::set to_remove(first1, last1);
    It2 result = first2;

    for (It2 it = first2; it != last2; ++it) {
        if (to_remove.find(std::distance(first2, it)) == to_remove.end()) {
            std::iter_swap(result, it);
            ++result;
        }
    }

    return result;
}
