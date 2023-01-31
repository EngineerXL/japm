#ifndef PATTERN_TEXT_SEARCH_H
#define PATTERN_TEXT_SEARCH_H

#include <string>
#include <vector>

struct pattern_text_t {
    using string = std::string;
    string p;
    size_t m;
    bool case_sence;

    pattern_text_t(const string &, bool);

    bool searchIn(string);

    std::vector<size_t> z_func(const std::string &);
};

#endif  // PATTERN_TEXT_SEARCH_H
