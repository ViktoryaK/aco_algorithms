#include "tests.h"
#include <vector>
#include <unordered_map>


bool is_stable(size_t man, size_t woman, const std::vector<std::unordered_map<size_t, size_t>> &preferences,
               std::vector<std::pair<size_t, size_t>> &matches, size_t n) {
    size_t woman_to_man_pref = preferences[woman + n].at(man);
    std::vector<size_t> all_men_she_likes_more;
    for (size_t i = 0; i < n; ++i) {
        if (preferences[woman + n].at(i) < woman_to_man_pref) {
            all_men_she_likes_more.push_back(i);
        }
    }
    for (size_t i: all_men_she_likes_more) {
        for (size_t match = 0; match < n; ++match) {
            if (matches[match].first == i) {
                if (preferences[i].at(woman) < preferences[i].at(matches[match].second)) {
                    return false;
                }
            }
        }

    }
    return true;
}


double percent_of_stable_m(const std::vector<std::unordered_map<size_t, size_t>> &preferences,
                           std::vector<std::pair<size_t, size_t>> &matches, size_t n) {
    int stable_count = 0;
    for (size_t i = 0; i < n; ++i) {
        if (is_stable(matches[i].first, matches[i].second, preferences, matches, n)) {
            stable_count++;
        }
    }
    return (double) stable_count * 100 / (double) n;
}


double average_preference(const std::vector<std::unordered_map<size_t, size_t>> &preferences,
                          std::vector<std::pair<size_t, size_t>> &matches, size_t n, bool woman) {
    size_t prefs = 0;
    if (!woman) {
        for (size_t i = 0; i < n; ++i) {
            prefs += preferences[matches[i].first].at(matches[i].second);
        }
    } else {
        for (size_t i = 0; i < n; ++i) {
            prefs += preferences[matches[i].second + n].at(matches[i].first);
        }
    }
    return (double) prefs / (double) n;
}

