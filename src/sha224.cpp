//
// Created by noname on 29.12.2020.
//

#include <vector>

#include "hash/sha224.h"
#include "tool/chunk.h"
#include "tool/binary.h"

namespace hash
{
    Sha224Hash *Sha224::calculate(const std::string &message) const
    {
        auto message_ = message;
        Word h0 = H[0];
        Word h1 = H[1];
        Word h2 = H[2];
        Word h3 = H[3];
        Word h4 = H[4];
        Word h5 = H[5];
        Word h6 = H[6];
        Word h7 = H[7];

        uint64_t length = message_.length() * 8;
        message_ += static_cast<unsigned char>(0x80);
        std::vector<Chunk64W> chunks;

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
            Word f = h5;
            Word g = h6;
            Word h = h7;

            Word s0;
            Word s1;

            for (size_t i = 16; i < 64; i++)
            {
                s0 = tool::right_rotate(chunk[i - 15], 7) ^ tool::right_rotate(chunk[i - 15], 18) ^
                     (chunk[i - 15] >> 3);
                s1 = tool::right_rotate(chunk[i - 2], 17) ^ tool::right_rotate(chunk[i - 2], 19) ^
                     (chunk[i - 2] >> 10);
                chunk[i] = chunk[i - 16] + s0 + chunk[i - 7] + s1;
            }

            for (size_t i = 0; i < 64; i++)
            {
                s1 = tool::right_rotate(e, 6) ^ tool::right_rotate(e, 11) ^ tool::right_rotate(e, 25);
                Word ch = (e & f) ^((~e) & g);
                Word t1 = h + s1 + ch + k[i] + chunk[i];
                s0 = tool::right_rotate(a, 2) ^ tool::right_rotate(a, 13) ^ tool::right_rotate(a, 22);
                Word maj = (a & b) ^ (a & c) ^ (b & c);
                Word t2 = s0 + maj;

                h = g;
                g = f;
                f = e;
                e = d + t1;
                d = c;
                c = b;
                b = a;
                a = t1 + t2;
            }

            h0 = h0 + a;
            h1 = h1 + b;
            h2 = h2 + c;
            h3 = h3 + d;
            h4 = h4 + e;
            h5 = h5 + f;
            h6 = h6 + g;
            h7 = h7 + h;
        }
        return new Sha224Hash{h0, h1, h2, h3, h4, h5, h6};
    }
}
