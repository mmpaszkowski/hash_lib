//
// Created by noname on 14.09.23.
//

#ifndef CRYPTO_CIPHER_H
#define CRYPTO_CIPHER_H

#include <cstdint>

class Cipher
{
public:
    virtual void encrypt(const uint8_t *x, uint8_t *y) = 0;
    virtual void decrypt(const uint8_t *x, uint8_t *y) = 0;
};

#endif //CRYPTO_CIPHER_H
