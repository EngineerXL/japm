#include "pattern_text_search.h"

pattern_text_t::pattern_text_t(const string& _p, bool _case_sence)
    : p(_p), m(_p.size()), case_sence(_case_sence) {
    if (!case_sence) {
        for (char& c : p) {
            c = std::tolower(c);
        }
    }
}

bool pattern_text_t::searchIn(string t) {
    size_t n = t.size();
    if (n < m) {
        return false;
    }
    if (!case_sence) {
        for (char& c : t) {
            c = std::tolower(c);
        }
    }
    std::string pattern_and_text = p + '\0' + t;
    std::vector<size_t> z = z_func(pattern_and_text);
    for (size_t i = 0; i < z.size(); ++i) {
        if (z[i] == m) {
            return true;
        }
    }
    return false;
}

std::vector<size_t> pattern_text_t::z_func(const std::string& s) {
    size_t n = s.size();
    std::vector<size_t> z(n);
    size_t l = 0, r = 0;
    for (size_t i = 1; i < n; ++i) {
        if (i <= r) {
            z[i] = std::min(r - i, z[i - l]);
        }
        while (i + z[i] < n and s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] > r) {
            r = i + z[i];
            l = i;
        }
    }
    return z;
}
