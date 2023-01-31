#ifndef ENCRYPTER_AES256_H
#define ENCRYPTER_AES256_H

#include <cstring>
#include <stdexcept>
#include <string>

#include "aes/aes.hpp"
#include "sha3/sha3.h"

class encrypter_t {
   private:
    const static size_t SHA3_256_BYTES_LEN = 32;
    uint8_t *sha3_256(const std::string &);

    AES_ctx ctx;

    uint8_t *key = nullptr;
    uint8_t *iv = nullptr;

    void check();

   public:
    encrypter_t() {}

    encrypter_t(std::string s) { setKey(s); }

    void setKey(const std::string &);
    void setIV(const std::string &);

    std::string encrypt(const std::string &);
    std::string decrypt(const std::string &);

    ~encrypter_t() {
        delete[] key;
        delete[] iv;
    }
};

#endif  // ENCRYPTER_AES256_H
