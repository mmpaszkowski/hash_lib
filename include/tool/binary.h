//
// Created by noname on 05.01.2021.
//

#ifndef HASH_LIB_BINARY_H
#define HASH_LIB_BINARY_H

namespace tool
{
    template<typename T, typename N>
    T left_rotate(T word, N n)
    {
        return (word << n) | (word >> (sizeof(T) * 8 - n));
    }

    template<typename T, typename N>
    T right_rotate(T word, N n)
    {
        return (word >> n) | (word << (sizeof(T) * 8 - n));
    }
}

#endif //HASH_LIB_BINARY_H
