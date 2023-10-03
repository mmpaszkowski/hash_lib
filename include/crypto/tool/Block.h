//
// Created by noname on 15.09.23.
//

#ifndef CRYPTO_BLOCK_H
#define CRYPTO_BLOCK_H

#include <cstdint>

class Block
{
public:
    Block(const uint8_t* data, std::size_t size) {
        for(std::size_t i = 0; i < size; i++)
            this->data_[i] = data[i];
    }

    const uint8_t* data() { return data_; }

private:
    uint8_t* data_;
};

#endif //CRYPTO_BLOCK_H
