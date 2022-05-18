//
// Created by noname on 09.01.2021.
//

#ifndef HASH_LIB_SHA512_256_HASH_H
#define HASH_LIB_SHA512_256_HASH_H

#include "hash.h"
#include "sha512_256_hash.h"

namespace hash
{
    class Sha512_256Hash: public Hash
    {
    public:
        Sha512_256Hash() = default;

        template<typename T>
        constexpr Sha512_256Hash(const std::initializer_list<T> &&list);

        Sha512_256Hash(const Sha512_256Hash &other);

        Sha512_256Hash(Sha512_256Hash &&other) noexcept;

        ~Sha512_256Hash() override {};

        Sha512_256Hash &operator=(const Sha512_256Hash &other);

        Sha512_256Hash &operator=(Sha512_256Hash &&other) noexcept;

    public:
        size_t size() const override {return _size;}

        std::string to_string() const override;

        virtual std::ostream& print(std::ostream &os) const override;

        bool operator==(const Hash &rhs) const override;

    protected:
        const uint8_t* data() const override { return _data; }

    private:
        const static size_t _size = 32;
        value_type _data[_size];
    };

    template<typename T>
    constexpr Sha512_256Hash::Sha512_256Hash(const std::initializer_list<T> &&list)
    {
        size_t s = 0;
        for (const auto item : list)
        {
            auto size = sizeof(item);
            for (size_t i = 0; i < size; i++)
            {
                _data[s++] = (item >> ((size - i - 1) * 8)) & 0xFF;
            }
        }
    }
}

#endif //HASH_LIB_SHA512_256_HASH_H
