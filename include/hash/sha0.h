//
// Created by noname on 23.12.2020.
//

#ifndef HASH_LIB_SHA0_H
#define HASH_LIB_SHA0_H

#include "hash_algorithm.h"
#include "sha0_hash.h"

namespace tool
{
    template<typename T, size_t s>
    class Chunk;
}

namespace hash
{
    class Sha0 : public HashAlgorithm
    {
        using Word = std::uint32_t;
        using Chunk16W = tool::Chunk<Word, 16>;
        using Chunk80W = tool::Chunk<Word, 80>;

        static constexpr Word H[] = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0};
        static constexpr Word k[] = {0x5A827999, 0x6ED9EBA1, 0x8F1BBCDC, 0xCA62C1D6};

    public:
        Sha0Hash *calculate(const std::string &message) const override;
    };
}
#endif //HASH_LIB_SHA0_H
