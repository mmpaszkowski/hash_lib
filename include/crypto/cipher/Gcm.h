//
// Created by noname on 05.08.23.
//

#ifndef CRYPTO_AES_GCM_H
#define CRYPTO_AES_GCM_H

#include <cstdint>
#include <cstddef>
#include <array>
#include <vector>
#include <chrono>
#include "Aes.h"
#include "GHash.h"
#include "OperationMode.h"


class Gcm : public OperationMode {
public:
    explicit Gcm(const Aes &aes);

    explicit Gcm(Aes &&aes);

    Gcm(const Gcm &other);

    Gcm(Gcm &&other) noexcept;

    ~Gcm();

    Gcm& operator=(const Gcm &other);
    Gcm& operator=(Gcm &&other) noexcept;

public:
    void encrypt(const uint8_t *x, size_t data_len, uint8_t *y) override;
    void decrypt(const uint8_t *x, size_t data_len, uint8_t *y) override;
    void init(const uint8_t *iv, size_t iv_len, const uint8_t *associated_data, size_t associated_data_len);

private:
    void calc_J_0();

    static void xor_bytes(const uint8_t *a, uint8_t *b);
    static void xor_n_bytes(const uint8_t *a, uint8_t *b, size_t n);
    static void inc_32(uint8_t *Y_bytes);

    void gctr(uint8_t *icb, const uint8_t *x, uint8_t *y, size_t data_len);
    static void get_data(uint8_t *buffer, uint64_t n);
    void update_ghash(const uint8_t * data, size_t len);

private:
    Aes aes;
    GHash ghash;
    uint8_t J_0[16]{};
    uint8_t *iv;
    size_t iv_len;
    uint8_t *associated_data;
    size_t associated_data_len;
};


inline void Gcm::xor_bytes(const uint8_t *a, uint8_t *b) {
    for (size_t i = 0; i < 16; i++)
        b[i] = a[i] ^ b[i];
}

inline void Gcm::xor_n_bytes(const uint8_t *a, uint8_t *b, size_t n) {
    for (size_t i = 0; i < n; i++)
        b[i] = a[i] ^ b[i];
}

inline void Gcm::gctr(uint8_t *icb, const uint8_t *x, uint8_t *y, size_t data_len) {
    if (data_len == 0) {
        return;
    }

    size_t n = data_len / 16;
    size_t i = 0;
    for (; i < n; i++) {
        aes.encrypt(icb, y + i * 16);
        xor_bytes(x + i * 16, y + i * 16);
        inc_32(icb);
    }

    if (data_len % 16 != 0) {
        aes.encrypt(icb, y + i * 16);
        xor_n_bytes(x + i * 16, y + i * 16, data_len % 16);
    }
}

inline void Gcm::get_data(uint8_t *buffer, uint64_t n) {
    for (size_t i = 0; i < 8; ++i) {
        buffer[7 - i] = static_cast<uint8_t>(n);
        n >>= 8;
    }
}

inline void Gcm::encrypt(const uint8_t *x, size_t data_len, uint8_t *y) {
    ghash.reset();
    uint8_t icb[16];
    for (size_t i = 0; i < 16; i++) icb[i] = J_0[i];
    inc_32(icb);
    gctr(icb, x, y, data_len);

    uint8_t sizes[16];
    get_data(sizes, associated_data_len * 8);
    get_data(sizes + 8, data_len * 8);

    update_ghash(associated_data, associated_data_len);
    update_ghash(y, data_len);
    update_ghash(sizes, 16);

    uint8_t S[16];
    ghash.get_data(S);
    gctr(J_0, S, y + data_len, 16);
}

inline void Gcm::decrypt(const uint8_t *x, size_t data_len, uint8_t *y) {
    ghash.reset();
    data_len -= 16;
    uint8_t icb[16];
    for (size_t i = 0; i < 16; i++) icb[i] = J_0[i];
    inc_32(icb);
    gctr(icb, x, y, data_len);

    uint8_t sizes[16];
    get_data(sizes, associated_data_len * 8);
    get_data(sizes + 8, data_len * 8);

    update_ghash(associated_data, associated_data_len);
    update_ghash(x, data_len);
    update_ghash(sizes, 16);

    uint8_t S[16];
    ghash.get_data(S);

    uint8_t T[16];
    gctr(J_0, S, T, 16);

    for (size_t i = 0; i < 16; i++)
        if (T[i] != x[i + data_len]) throw std::runtime_error("Tag is not the same");
}

inline void Gcm::update_ghash(const uint8_t *data, size_t len) {
    size_t n = len / 16 * 16;
    for(size_t i = 0; i < n; i += 16)
    {
        ghash.update(data + i);
    }

    if(n == len) return;

    uint8_t buffer[16]{};
    for(size_t j = 0; j < len % 16; j++)
        buffer[j] = data[n + j];
    ghash.update(buffer);
}

inline void Gcm::inc_32(uint8_t *Y_bytes) {
    if (++Y_bytes[15] == 0)
        if (++Y_bytes[14] == 0)
            if (++Y_bytes[13] == 0)
                ++Y_bytes[12];
}



#endif //CRYPTO_AES_GCM_H
