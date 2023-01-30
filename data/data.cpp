#include "data.h"

data_t::data_t(const vecstr & _tags, const string & _name, const string & _login, const string & _password, const string & _info) {
    tags = _tags;
    name = _name;
    login = _login;
    password = _password;
    info = _info;
}

std::string data_t::tagsToString() const {
    std::string res;
    for (size_t i = 0; i < tags.size(); ++i) {
        if (i) {
            res += ", ";
        }
        res += tags[i];
    }
    return res;
}
