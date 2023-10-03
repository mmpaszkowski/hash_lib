//
// Created by noname on 05.08.23.
//

#ifndef CRYPTO_AES_H
#define CRYPTO_AES_H

#include "Cipher.h"
#include <cstddef>
#include <array>
#include <vector>
#include <iomanip>
#include <iostream>
#include "Key.h"

class Key;

class Aes : public Cipher {

public:
    [[maybe_unused]] explicit Aes(const Key &key);

    [[maybe_unused]] explicit Aes(Key &&key) noexcept;

    Aes(const Aes &other) = default;

    Aes(Aes &&other) noexcept = default;

    ~Aes() = default;

public:
    Aes &operator=(const Aes &other) = default;

    Aes &operator=(Aes &&other) noexcept = default;

public:
    void encrypt(const uint8_t *x, uint8_t *y) override;

    void decrypt(const uint8_t *x, uint8_t *y) override;

private:
    static std::vector<uint32_t> state_from_bytes(const uint8_t *bytes);

    static uint32_t rot_word(uint32_t word) { return (word >> 8) | (word << 24); }

    static uint32_t sub_word(uint32_t word);

    static uint32_t rcon(uint32_t i);

    static uint32_t xor_bytes(uint32_t v1, uint32_t v2) { return v1 ^ v2; }

    void expand_key(const Key &key);

    void add_round_key(const uint8_t *x, uint8_t *y, size_t round) const;

    static void sub_bytes(const uint8_t *x, uint8_t *y);

    static void inv_sub_bytes(const uint8_t *x, uint8_t *y);

    static void shift_rows(uint8_t *x);

    static void inv_shift_rows(uint8_t *x);

    static void inv_mix_columns(uint8_t *x);

    static void mix_columns(uint8_t *x);

    static uint8_t xtime(uint8_t a);

    static uint8_t xtimes_0e(uint8_t b) { return xtime(xtime(xtime(b) ^ b) ^ b); }

    static uint8_t xtimes_0b(uint8_t b) { return xtime(xtime(xtime(b)) ^ b) ^ b; }

    static uint8_t xtimes_0d(uint8_t b) { return xtime(xtime(xtime(b) ^ b)) ^ b; }

    static uint8_t xtimes_09(uint8_t b) { return xtime(xtime(xtime(b))) ^ b; }

private:
    Key key_;
    std::vector<std::array<uint32_t, 4>> key_schedule_;
    size_t nr{};

    constexpr static uint8_t s_box[] = {
            0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
            0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
            0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
            0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
            0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
            0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
            0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
            0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
            0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
            0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
            0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
            0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
            0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
            0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
            0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
            0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
    };

    constexpr static uint8_t inv_s_box[] = {
            0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
            0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
            0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
            0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
            0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
            0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
            0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
            0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
            0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
            0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
            0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
            0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
            0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
            0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
            0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
            0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d,
    };
};

inline void Aes::encrypt(const uint8_t *x, uint8_t *y) {
    add_round_key(x, y, 0);
    for (size_t round = 1; round < nr; round++) {
        sub_bytes(y, y);
        shift_rows(y);
        mix_columns(y);
        add_round_key(y, y, round);
    }

    sub_bytes(y, y);
    shift_rows(y);
    add_round_key(y, y, nr);
}

inline void Aes::decrypt(const uint8_t *x, uint8_t *y) {
    add_round_key(x, y, nr);
    for (size_t round = nr - 1; round > 0; round--) {
        inv_shift_rows(y);
        inv_sub_bytes(y, y);
        add_round_key(y, y, round);
        inv_mix_columns(y);
    }

    inv_shift_rows(y);
    inv_sub_bytes(y, y);
    add_round_key(y, y, 0);
}

inline std::vector<uint32_t> Aes::state_from_bytes(const uint8_t *bytes) {
    const auto *data = reinterpret_cast<const uint32_t *>(bytes);
    std::vector<uint32_t> state;
    for (size_t i = 0; i < 4; i++) {
        state.push_back(data[i]);
    }
    return state;
}

inline uint32_t Aes::sub_word(uint32_t word) {
    uint32_t result;
    auto result_p = reinterpret_cast<uint8_t *>(&result);
    auto word_p = reinterpret_cast<uint8_t *>(&word);

    for (size_t i = 0; i < 4; i++) {
        result_p[i] = s_box[word_p[i]];
    }
    return result;
}

inline uint32_t Aes::rcon(uint32_t i) {
    const static uint32_t rcon_lookup[] = {0x00000001, 0x00000002, 0x00000004, 0x00000008, 0x00000010, 0x00000020, 0x00000040,
                                           0x00000080, 0x0000001b, 0x00000036};
    return rcon_lookup[i - 1];
}

inline void Aes::expand_key(const Key &key) {
    auto nk = key.length() / 32;

    if (key.length() == 128) // #128-bit keys
        nr = 10;
    else if (key.length() == 192) // #192-bit keys
        nr = 12;
    else if (key.length() == 256) // #256-bit keys
        nr = 14;
    else
        throw std::runtime_error("Key length not allowed");

    auto w = state_from_bytes(key.data());
    uint32_t temp;
    for (size_t i = nk; i < 4 * (nr + 1); i++) {
        temp = w[i - 1];
        if (i % nk == 0) {
            temp = xor_bytes(sub_word(rot_word(temp)), rcon(i / nk));
        } else if (nk > 6 and i % nk == 4)
            temp = sub_word(temp);
        w.push_back(xor_bytes(w[i - nk], temp));
    }

    for (size_t i = 0; i < w.size() / 4; i++)
        this->key_schedule_.push_back(
                std::array<uint32_t, 4>{{w[4 * i + 0], w[4 * i + 1], w[4 * i + 2], w[4 * i + 3]}});
}

inline void Aes::add_round_key(const uint8_t *x, uint8_t *y, size_t round) const {
    reinterpret_cast<uint64_t *>(y)[0] = reinterpret_cast<const uint64_t *>(x)[0] ^
                                         reinterpret_cast<const uint64_t *>(this->key_schedule_[round].data())[0];
    reinterpret_cast<uint64_t *>(y)[1] = reinterpret_cast<const uint64_t *>(x)[1] ^
                                         reinterpret_cast<const uint64_t *>(this->key_schedule_[round].data())[1];
}

inline void Aes::sub_bytes(const uint8_t *x, uint8_t *y) {
    y[0] = s_box[x[0]];
    y[1] = s_box[x[1]];
    y[2] = s_box[x[2]];
    y[3] = s_box[x[3]];
    y[4] = s_box[x[4]];
    y[5] = s_box[x[5]];
    y[6] = s_box[x[6]];
    y[7] = s_box[x[7]];
    y[8] = s_box[x[8]];
    y[9] = s_box[x[9]];
    y[10] = s_box[x[10]];
    y[11] = s_box[x[11]];
    y[12] = s_box[x[12]];
    y[13] = s_box[x[13]];
    y[14] = s_box[x[14]];
    y[15] = s_box[x[15]];
}

inline void Aes::inv_sub_bytes(const uint8_t *x, uint8_t *y) {
    y[0] = inv_s_box[x[0]];
    y[1] = inv_s_box[x[1]];
    y[2] = inv_s_box[x[2]];
    y[3] = inv_s_box[x[3]];
    y[4] = inv_s_box[x[4]];
    y[5] = inv_s_box[x[5]];
    y[6] = inv_s_box[x[6]];
    y[7] = inv_s_box[x[7]];
    y[8] = inv_s_box[x[8]];
    y[9] = inv_s_box[x[9]];
    y[10] = inv_s_box[x[10]];
    y[11] = inv_s_box[x[11]];
    y[12] = inv_s_box[x[12]];
    y[13] = inv_s_box[x[13]];
    y[14] = inv_s_box[x[14]];
    y[15] = inv_s_box[x[15]];
}

inline void Aes::shift_rows(uint8_t *x) {
    auto state_p_0 = x;
    auto state_p_1 = x + 4;
    auto state_p_2 = x + 8;
    auto state_p_3 = x + 12;

    uint32_t tmp = state_p_0[1];
    state_p_0[1] = state_p_1[1];
    state_p_1[1] = state_p_2[1];
    state_p_2[1] = state_p_3[1];
    state_p_3[1] = tmp;

    std::swap(state_p_0[2], state_p_2[2]);
    std::swap(state_p_1[2], state_p_3[2]);

    tmp = state_p_0[3];
    state_p_0[3] = state_p_3[3];
    state_p_3[3] = state_p_2[3];
    state_p_2[3] = state_p_1[3];
    state_p_1[3] = tmp;
}

inline void Aes::inv_shift_rows(uint8_t *x) {
    auto state_p_0 = reinterpret_cast<uint8_t *>(x);
    auto state_p_1 = reinterpret_cast<uint8_t *>(x + 4);
    auto state_p_2 = reinterpret_cast<uint8_t *>(x + 8);
    auto state_p_3 = reinterpret_cast<uint8_t *>(x + 12);

    uint32_t tmp = state_p_3[1];
    state_p_3[1] = state_p_2[1];
    state_p_2[1] = state_p_1[1];
    state_p_1[1] = state_p_0[1];
    state_p_0[1] = tmp;

    std::swap(state_p_0[2], state_p_2[2]);
    std::swap(state_p_1[2], state_p_3[2]);

    tmp = state_p_3[3];
    state_p_3[3] = state_p_0[3];
    state_p_0[3] = state_p_1[3];
    state_p_1[3] = state_p_2[3];
    state_p_2[3] = tmp;
}

inline void Aes::inv_mix_columns(uint8_t *x) {
    uint8_t x0 = x[0];
    uint8_t x1 = x[1];
    uint8_t x2 = x[2];
    uint8_t x3 = x[3];
    x[0] = xtimes_0e(x0) ^ xtimes_0b(x1) ^ xtimes_0d(x2) ^ xtimes_09(x3);
    x[1] = xtimes_09(x0) ^ xtimes_0e(x1) ^ xtimes_0b(x2) ^ xtimes_0d(x3);
    x[2] = xtimes_0d(x0) ^ xtimes_09(x1) ^ xtimes_0e(x2) ^ xtimes_0b(x3);
    x[3] = xtimes_0b(x0) ^ xtimes_0d(x1) ^ xtimes_09(x2) ^ xtimes_0e(x3);

    uint8_t x4 = x[4];
    uint8_t x5 = x[5];
    uint8_t x6 = x[6];
    uint8_t x7 = x[7];
    x[4] = xtimes_0e(x4) ^ xtimes_0b(x5) ^ xtimes_0d(x6) ^ xtimes_09(x7);
    x[5] = xtimes_09(x4) ^ xtimes_0e(x5) ^ xtimes_0b(x6) ^ xtimes_0d(x7);
    x[6] = xtimes_0d(x4) ^ xtimes_09(x5) ^ xtimes_0e(x6) ^ xtimes_0b(x7);
    x[7] = xtimes_0b(x4) ^ xtimes_0d(x5) ^ xtimes_09(x6) ^ xtimes_0e(x7);

    uint8_t x8 = x[8];
    uint8_t x9 = x[9];
    uint8_t x10 = x[10];
    uint8_t x11 = x[11];
    x[8] = xtimes_0e(x8) ^ xtimes_0b(x9) ^ xtimes_0d(x10) ^ xtimes_09(x11);
    x[9] = xtimes_09(x8) ^ xtimes_0e(x9) ^ xtimes_0b(x10) ^ xtimes_0d(x11);
    x[10] = xtimes_0d(x8) ^ xtimes_09(x9) ^ xtimes_0e(x10) ^ xtimes_0b(x11);
    x[11] = xtimes_0b(x8) ^ xtimes_0d(x9) ^ xtimes_09(x10) ^ xtimes_0e(x11);

    uint8_t x12 = x[12];
    uint8_t x13 = x[13];
    uint8_t x14 = x[14];
    uint8_t x15 = x[15];
    x[12] = xtimes_0e(x12) ^ xtimes_0b(x13) ^ xtimes_0d(x14) ^ xtimes_09(x15);
    x[13] = xtimes_09(x12) ^ xtimes_0e(x13) ^ xtimes_0b(x14) ^ xtimes_0d(x15);
    x[14] = xtimes_0d(x12) ^ xtimes_09(x13) ^ xtimes_0e(x14) ^ xtimes_0b(x15);
    x[15] = xtimes_0b(x12) ^ xtimes_0d(x13) ^ xtimes_09(x14) ^ xtimes_0e(x15);
}

inline void Aes::mix_columns(uint8_t *x) {
    auto c_0 = x[0];
    uint8_t all_xor = x[0] ^ x[1] ^ x[2] ^ x[3];
    x[0] ^= all_xor ^ xtime(x[0] ^ x[1]);
    x[1] ^= all_xor ^ xtime(x[1] ^ x[2]);
    x[2] ^= all_xor ^ xtime(x[2] ^ x[3]);
    x[3] ^= all_xor ^ xtime(c_0 ^ x[3]);

    c_0 = x[4];
    all_xor = x[4] ^ x[5] ^ x[6] ^ x[7];
    x[4] ^= all_xor ^ xtime(x[4] ^ x[5]);
    x[5] ^= all_xor ^ xtime(x[5] ^ x[6]);
    x[6] ^= all_xor ^ xtime(x[6] ^ x[7]);
    x[7] ^= all_xor ^ xtime(c_0 ^ x[7]);

    c_0 = x[8];
    all_xor = x[8] ^ x[9] ^ x[10] ^ x[11];
    x[8] ^= all_xor ^ xtime(x[8] ^ x[9]);
    x[9] ^= all_xor ^ xtime(x[9] ^ x[10]);
    x[10] ^= all_xor ^ xtime(x[10] ^ x[11]);
    x[11] ^= all_xor ^ xtime(c_0 ^ x[11]);

    c_0 = x[12];
    all_xor = x[12] ^ x[13] ^ x[14] ^ x[15];
    x[12] ^= all_xor ^ xtime(x[12] ^ x[13]);
    x[13] ^= all_xor ^ xtime(x[13] ^ x[14]);
    x[14] ^= all_xor ^ xtime(x[14] ^ x[15]);
    x[15] ^= all_xor ^ xtime(c_0 ^ x[15]);
}

inline uint8_t Aes::xtime(uint8_t a) {
    if (a & 0x80) return ((a << 1) ^ 0x1b) & 0xff;
    return a << 1;
}

#endif //CRYPTO_AES_H
