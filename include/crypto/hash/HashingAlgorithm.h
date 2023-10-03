//
// Created by noname on 05.01.2021.
//

#ifndef CRYPTO_HASHING_ALGORITHM_H
#define CRYPTO_HASHING_ALGORITHM_H

#include <string>

namespace hash
{
    class Hash;

    class HashingAlgorithm
    {
    public:
        [[nodiscard]] virtual Hash *calculate(const std::string &message) const = 0;
    };
}

#endif //CRYPTO_HASHING_ALGORITHM_H
