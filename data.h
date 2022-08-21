#ifndef DATA_H
#define DATA_H

#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct data_t {
    const static char DATA_BEGIN = '{';
    const static char DATA_END = '}';
    const static char DELIMITER = ',';

    using string = std::string;
    using vecstr = std::vector<string>;
    using ostream = std::ostream;
    using istream = std::istream;

    vecstr tags;
    string name;
    string login;
    string password;
    string info;

    data_t() {}

    data_t(const vecstr & _tags, const string & _name, const string & _login, const string & _password, const string & _info) {
        tags = _tags;
        name = _name;
        login = _login;
        password = _password;
        info = _info;
    }

    static void writeString(ostream & out, const string & s) {
        uint64_t n = s.size();
        out << n << DELIMITER << s;
    }

    friend ostream & operator << (ostream & out, const data_t & elem) {
        out << DATA_BEGIN;
        uint64_t n = elem.tags.size();
        out << n;
        out << DATA_BEGIN;
        for (string tag : elem.tags) {
            writeString(out, tag);
        }
        out << DATA_END;
        writeString(out, elem.name);
        writeString(out, elem.login);
        writeString(out, elem.password);
        writeString(out, elem.info);
        out << DATA_END;
        return out;
    }

    static void readString(istream & in, string & s) {
        uint64_t n;
        in >> n;
        char c;
        in >> c;
        if (c != DELIMITER) {
            throw std::runtime_error("Invalid data (delimiter)!");
        }
        s.resize(n);
        for (uint64_t i = 0; i < n; ++i) {
            in >> s[i];
        }
    }

    friend istream & operator >> (istream & in, data_t & elem) {
        char c;
        in >> c;
        if (c != DATA_BEGIN) {
            return in;
        }
        uint64_t n;
        in >> n;
        elem.tags.resize(n);
        in >> c;
        if (c != DATA_BEGIN) {
            throw std::runtime_error("Invalid data (begin of tags)!");
        }
        for (uint64_t i = 0; i < n; ++i) {
            readString(in, elem.tags[i]);
        }
        in >> c;
        if (c != DATA_END) {
            throw std::runtime_error("Invalid data (end of tags)!");
        }
        readString(in, elem.name);
        readString(in, elem.login);
        readString(in, elem.password);
        readString(in, elem.info);
        in >> c;
        if (c != DATA_END) {
            throw std::runtime_error("Invalid data (end of structure)!");
        }
        return in;
    }
};

#endif // DATA_H
