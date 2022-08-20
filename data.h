#ifndef DATA_H
#define DATA_H

#include <exception>
#include <iostream>
#include <string>

class data_t {
    const static char DATA_BEGIN = '{';
    const static char DATA_END = '}';

    using string = std::string;
    using ostream = std::ostream;
    using istream = std::istream;

    string name;
    string login;
    string password;

public:
    data_t(const string & _name, const string & _login, const string & _password) {
        name = _name;
        login = _login;
        password = _password;
    }

    static void printString(ostream & out, const string & s) {
        int64_t n = s.size();
        out << n;
        for (char elem : s) {
            out << elem;
        }
    }

    friend ostream & operator << (ostream & out, const data_t & elem) {
        out << DATA_BEGIN;
        printString(out, elem.name);
        printString(out, elem.login);
        printString(out, elem.password);
        out << DATA_END;
        return out;
    }

    static void readString(istream & in, string & s) {
        int64_t n;
        in >> n;
        s.resize(n);
        for (int64_t i = 0; i < n; ++i) {
            in >> s[i];
        }
    }

    friend istream & operator >> (istream & in, data_t & elem) {
        char c;
        in >> c;
        if (c != DATA_BEGIN) {
            throw std::runtime_error("Invalid data");
        }
        readString(in, elem.name);
        readString(in, elem.login);
        readString(in, elem.password);
        in >> c;
        if (c != DATA_END) {
            throw std::runtime_error("Invalid data");
        }
        return in;
    }
};

#endif // DATA_H
