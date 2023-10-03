//
// Created by noname on 15.09.23.
//

#ifndef CRYPTO_OPERATION_MODE_H
#define CRYPTO_OPERATION_MODE_H


#include <cstdint>
#include <cstddef>

class OperationMode {
public:
    virtual void encrypt(const uint8_t *x, size_t data_len, uint8_t *y) = 0;
    virtual void decrypt(const uint8_t *x, size_t data_len, uint8_t *y) = 0;
};


#endif //CRYPTO_OPERATION_MODE_H
