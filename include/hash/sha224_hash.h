//
// Created by noname on 09.01.2021.
//

#ifndef HASH_LIB_SHA224_HASH_H
#define HASH_LIB_SHA224_HASH_H

#include "hash.h"

namespace hash
{
    class Sha224Hash: public Hash
    {
    public:
        Sha224Hash() = default;

        template<typename T>
        constexpr Sha224Hash(const std::initializer_list<T> &&list);

        Sha224Hash(const Sha224Hash &other);

        Sha224Hash(Sha224Hash &&other) noexcept;

        ~Sha224Hash() override {};

        Sha224Hash &operator=(const Sha224Hash &other);

        Sha224Hash &operator=(Sha224Hash &&other) noexcept;

    public:
        size_t size() const override {return _size;}

        std::string to_string() const override;

        virtual std::ostream& print(std::ostream &os) const override;

        bool operator==(const Hash &rhs) const override;

    protected:
        const uint8_t* data() const override { return _data; }

    private:
        const static size_t _size = 28;
        value_type _data[_size];
    };

    template<typename T>
    constexpr Sha224Hash::Sha224Hash(const std::initializer_list<T> &&list)
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

#endif //HASH_LIB_SHA224_HASH_H
