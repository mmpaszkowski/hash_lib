//
// Created by noname on 28.12.2020.
//

#include <vector>

#include "hash/sha1.h"
#include "tool/chunk.h"
#include "tool/binary.h"
#include "hash/sha1_hash.h"

namespace hash
{
    Sha1Hash *Sha1::calculate(const std::string &message) const
    {
        auto message_ = message;
        Word h0 = H[0];
        Word h1 = H[1];
        Word h2 = H[2];
        Word h3 = H[3];
        Word h4 = H[4];

        uint64_t length = message_.length() * 8;
        message_ += static_cast<unsigned char>(0x80);
        std::vector<Chunk80W> chunks;

        for (size_t i = 0; i < message_.length(); i++)
        {
            if (i % (Chunk16W::size() * sizeof(Word)) == 0)
            {
                chunks.emplace_back();
            }
            std::size_t chunk_index = i / (Chunk16W::size() * sizeof(Word));
            std::size_t word_index = i / sizeof(Word) % Chunk16W::size();
            std::size_t byte_index = i % Chunk16W::size() % sizeof(Word);
            chunks[chunk_index][word_index] |=
                    static_cast<uint64_t>(static_cast<std::byte>(message_[i])) << (8 * (sizeof(Word) - byte_index - 1));
        }

        if ((length / 8) % 64 >= 56)
            chunks.emplace_back();

        chunks.back()[14] = (length & 0xFFFFFFFF00000000) >> 32;
        chunks.back()[15] = length & 0xFFFFFFFF;

        for (auto &&chunk : chunks)
        {
            Word a = h0;
            Word b = h1;
            Word c = h2;
            Word d = h3;
            Word e = h4;
            Word s1;
            Word s2;

            for (size_t i = 0; i < 80; i++)
            {
                if (i >= 16)
                {
                    chunk[i] = tool::left_rotate(chunk[i - 3] ^ chunk[i - 8] ^ chunk[i - 14] ^ chunk[i - 16], 1);
                }
                if (i < 20)
                {
                    s1 = (b & c) | ((~b) & d);
                    s2 = k[0];
                } else if (i < 40)
                {
                    s1 = b ^ c ^ d;
                    s2 = k[1];
                } else if (i < 60)
                {
                    s1 = (b & c) | (b & d) | (c & d);
                    s2 = k[2];
                } else if (i < 80)
                {
                    s1 = b ^ c ^ d;
                    s2 = k[3];
                }
                auto temp = tool::left_rotate(a, 5) + s1 + e + s2 + chunk[i];
                e = d;
                d = c;
                c = tool::left_rotate(b, 30);
                b = a;
                a = temp;
            }
            h0 = h0 + a;
            h1 = h1 + b;
            h2 = h2 + c;
            h3 = h3 + d;
            h4 = h4 + e;
        }
        return new Sha1Hash{h0, h1, h2, h3, h4};
    }
}
