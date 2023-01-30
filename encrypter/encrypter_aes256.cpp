#include "encrypter_aes256.h"

uint8_t* encrypter_t::sha3_256(const std::string & s) {
    sha3_context c;
    sha3_Init256(&c);
    sha3_Update(&c, s.c_str(), s.size());
    uint8_t* res = new uint8_t[SHA3_256_BYTES_LEN];
    memcpy(res, (uint8_t *)sha3_Finalize(&c), SHA3_256_BYTES_LEN);
    return res;
}

void encrypter_t::check() {
    if (key == nullptr or iv == nullptr) {
        throw std::runtime_error("Encrypter contains null key or iv");
    }
}

void encrypter_t::setKey(const std::string & s) {
    if (s.empty()) {
        throw std::runtime_error("Encryption key is empty");
    }
    key = sha3_256(s);
}

void encrypter_t::setIV(const std::string & s) {
    if (s.empty()) {
        throw std::runtime_error("IV is empty");
    }
    iv = sha3_256(s);
}

std::string encrypter_t::encrypt(const std::string & s) {
    check();
    std::string res(s);
    AES_init_ctx_iv(&ctx, key, iv);
    AES_CTR_xcrypt_buffer(&ctx, (uint8_t *)res.c_str(), res.size());
    return res;
}

std::string encrypter_t::decrypt(const std::string & s) {
    check();
    std::string res(s);
    AES_init_ctx_iv(&ctx, key, iv);
    AES_CTR_xcrypt_buffer(&ctx, (uint8_t *)res.c_str(), res.size());
    return res;
}
