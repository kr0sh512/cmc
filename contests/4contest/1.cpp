#include <vector>
#include <cstdint>

void process(const std::vector<uint64_t>& from, std::vector<uint64_t>& into, int step) {
    auto iterf = from.begin();
    auto itert = into.rbegin();

    while (iterf < from.end() && itert != into.rend()) {
        *itert += *iterf;
        ++itert;
        iterf += step;
    }

    return;
}