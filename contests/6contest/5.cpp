#include <iterator>
#include <functional>

template <typename ForwardIt, typename Compare = std::less<>>
void selection_sort(ForwardIt first, ForwardIt last, Compare comp = Compare()) {
    for (auto fit = first; fit != last; ++fit) {
        auto min_it = fit;

        for (auto sit = std::next(fit); sit != last; ++sit) {
            if (comp(*sit, *min_it)) {
                min_it = sit;
            }
        }

        std::swap(*fit, *min_it);
    }

    return;
}
