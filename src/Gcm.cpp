//
// Created by noname on 02.10.23.
//
#include "crypto/cipher/Gcm.h"

Gcm::Gcm(const Aes &aes) : aes(aes), ghash(), J_0{}, iv{}, iv_len(0), associated_data{}, associated_data_len(0) {
    calc_J_0();
}

Gcm::Gcm(Aes &&aes) : aes(std::move(aes)), J_0{}, iv{}, iv_len(0), associated_data{}, associated_data_len(0) {
    calc_J_0();
}

Gcm::Gcm(const Gcm &other) : aes(other.aes), ghash(other.ghash), iv(nullptr), iv_len(other.iv_len),
                             associated_data(nullptr),
                             associated_data_len(other.associated_data_len) {
    for (size_t i = 0; i < 16; i++) {
        J_0[i] = other.J_0[i];
    }
    iv = new uint8_t[iv_len];
    for (size_t i = 0; i < iv_len; i++) {
        iv[i] = other.iv[i];
    }
    associated_data = new uint8_t[associated_data_len];
    for (size_t i = 0; i < associated_data_len; i++) {
        associated_data[i] = other.associated_data[i];
    }
}

Gcm::Gcm(Gcm &&other) noexcept: aes(std::move(other.aes)), ghash(std::move(other.ghash)), iv(other.iv),
                                iv_len(other.iv_len),
                                associated_data(other.associated_data),
                                associated_data_len(other.associated_data_len) {
    for (size_t i = 0; i < 16; i++) {
        J_0[i] = other.J_0[i];
    }
    other.iv_len = 0;
    other.iv = nullptr;
    other.associated_data_len = 0;
    other.associated_data = nullptr;
}

Gcm &Gcm::operator=(const Gcm &other) {
    if(this == &other)
        return *this;

    this->aes = other.aes;
    this->iv_len = other.iv_len;
    this->associated_data_len = other.associated_data_len;

    for (size_t i = 0; i < 16; i++) {
        this->J_0[i] = other.J_0[i];
    }
    this->iv = new uint8_t[iv_len];
    for (size_t i = 0; i < iv_len; i++) {
        this->iv[i] = other.iv[i];
    }
    this->associated_data = new uint8_t[associated_data_len];
    for (size_t i = 0; i < associated_data_len; i++) {
        this->associated_data[i] = other.associated_data[i];
    }

    return *this;
}

Gcm &Gcm::operator=(Gcm &&other) noexcept {
    this->aes = other.aes;
    this->iv_len = other.iv_len;
    this->iv = other.iv;
    this->associated_data_len = other.associated_data_len;
    this->associated_data = other.associated_data;
    for (size_t i = 0; i < 16; i++) {
        this->J_0[i] = other.J_0[i];
    }
    other.iv = nullptr;
    other.associated_data = nullptr;

    return *this;
}

Gcm::~Gcm() {
    delete[] this->iv;
    delete[] this->associated_data;
}

void Gcm::init(const uint8_t *iv, size_t iv_len, const uint8_t *associated_data, size_t associated_data_len) {
    this->iv_len = iv_len;
    this->iv = new uint8_t[iv_len];
    for (size_t i = 0; i < iv_len; i++)
        this->iv[i] = iv[i];

    this->associated_data_len = associated_data_len;
    this->associated_data = new uint8_t[associated_data_len];
    for (size_t i = 0; i < associated_data_len; i++)
        this->associated_data[i] = associated_data[i];

    calc_J_0();
}

void Gcm::calc_J_0() {
    uint8_t init_data[]{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                        0x00};
    uint8_t H[16];
    aes.encrypt(init_data, H);
    ghash.init(H);

    if (iv_len == 12) {
        for (int i = 0; i < 12; i++)
            J_0[i] = iv[i];
        J_0[12] = 0x00;
        J_0[13] = 0x00;
        J_0[14] = 0x00;
        J_0[15] = 0x01;
    } else {
        uint8_t iv_len_p[16]{};
        get_data(iv_len_p + 8, iv_len * 8);

        std::vector<uint8_t> result;
        update_ghash(iv, iv_len);
        update_ghash(iv_len_p, 16);
        ghash.get_data(J_0);
        ghash.reset();
    }
}

