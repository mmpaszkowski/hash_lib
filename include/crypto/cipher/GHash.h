//
// Created by noname on 23.09.23.
//

#ifndef CRYPTO_GHASH_H
#define CRYPTO_GHASH_H

#include <cstdint>
#include <cstddef>
#include <initializer_list>

class GHash {
public:
    GHash() {
        this->H[0] = 0;
        this->H[1] = 0;
        this->state[0] = 0;
        this->state[1] = 0;
    };

    explicit GHash(const uint8_t *H) {
        this->H[0] = get_long(H);
        this->H[1] = get_long(H + 8);
        this->state[0] = 0;
        this->state[1] = 0;
    }

    GHash(const GHash &ghash) {
        this->H[0] = ghash.H[0];
        this->H[1] = ghash.H[1];

        this->state[0] = ghash.state[0];
        this->state[1] = ghash.state[1];
    }

    GHash(GHash &&ghash) noexcept {
        this->H[0] = ghash.H[0];
        this->H[1] = ghash.H[1];

        this->state[0] = ghash.state[0];
        this->state[1] = ghash.state[1];
    }

    void init(const uint8_t *H)
    {
        this->H[0] = get_long(H);
        this->H[1] = get_long(H + 8);
        this->state[0] = 0;
        this->state[1] = 0;
    }

    void reset()
    {
        this->state[0] = 0;
        this->state[1] = 0;
    }

    static inline int64_t get_long(const uint8_t *buffer) {
        int64_t result = 0;
        for (size_t i = 0; i < 8; ++i) {
            result = (result << 8) + (buffer[i] & 0xFF);
        }
        return result;
    }

    void get_data(uint8_t *buffer) {
        int64_t st0 = this->state[0];
        for (size_t i = 0; i < 8; ++i) {
            buffer[7 - i] = static_cast<uint8_t>(st0);
            st0 >>= 8;
        }

        int64_t st1 = this->state[1];
        for (size_t i = 0; i < 8; ++i) {
            buffer[15 - i] = static_cast<uint8_t>(st1);
            st1 >>= 8;
        }
    }

    inline void update(const uint8_t *data) {
        this->state[0] ^= get_long(data);
        this->state[1] ^= get_long(data + 8);
        mul();
    }

private:
    inline void mul() {
        int64_t Z0 = 0;
        int64_t Z1 = 0;
        int64_t V0 = this->H[0];
        int64_t V1 = this->H[1];
        int64_t X;

        X = state[0];
        for (int i = 0; i < 64; i++) {
            int64_t mask = X >> 63;
            Z0 ^= V0 & mask;
            Z1 ^= V1 & mask;

            mask = (V1 << 63) >> 63;

            long carry = V0 & 1;
            V0 = (V0 >> 1) & 0x7FFFFFFFFFFFFFFFLL;
            V1 = ((V1 >> 1) & 0x7FFFFFFFFFFFFFFFLL) | (carry << 63);

            V0 ^= -2233785415175766016LL & mask;
            X <<= 1;
        }

        X = state[1];
        for (int i = 0; i < 63; i++) {
            int64_t mask = X >> 63;
            Z0 ^= V0 & mask;
            Z1 ^= V1 & mask;

            mask = (V1 << 63) >> 63;

            int64_t carry = V0 & 1;
            V0 = V0 >> 1 & 0x7FFFFFFFFFFFFFFFLL;
            V1 = ((V1 >> 1) & 0x7FFFFFFFFFFFFFFFLL) | (carry << 63);

            V0 ^= -2233785415175766016LL & mask;
            X <<= 1;
        }

        int64_t mask = X >> 63;
        Z0 ^= V0 & mask;
        Z1 ^= V1 & mask;

        this->state[0] = Z0;
        this->state[1] = Z1;
    }

private:
    int64_t H[2]{};
    int64_t state[2]{};
};

#endif //CRYPTO_GHASH_H
