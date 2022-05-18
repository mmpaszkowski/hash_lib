//
// Created by noname on 05.01.2021.
//

#ifndef HASH_LIB_HASH_ALGORITHM_H
#define HASH_LIB_HASH_ALGORITHM_H

#include <string>

namespace hash
{
    class Hash;

    class HashAlgorithm
    {
    public:
        virtual Hash *calculate(const std::string &message) const = 0;
    };
}

#endif //HASH_LIB_HASH_ALGORITHM_H
