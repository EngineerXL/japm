#include "pattern_text_search.h"

pattern_text_t::pattern_text_t(const string & _p, bool _case_sence) : p(_p), m(_p.size()), case_sence(_case_sence) {
    if (!case_sence) {
        for (char & c : p) {
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
        for (char & c : t) {
            c = std::tolower(c);
        }
    }
    for (size_t i = 0; i <= n - m; ++i) {
        std::string sub = t.substr(i, m);
        if (sub == p) {
            return true;
        }
    }
    return false;
}
