//
// Created by noname on 09.01.2021.
//

#ifndef HASH_LIB_SHA384_HASH_H
#define HASH_LIB_SHA384_HASH_H

#include "hash.h"

namespace hash
{
    class Sha384Hash: public Hash
    {
    public:
        Sha384Hash() = default;

        template<typename T>
        constexpr Sha384Hash(const std::initializer_list<T> &&list);

        Sha384Hash(const Sha384Hash &other);

        Sha384Hash(Sha384Hash &&other) noexcept;

        ~Sha384Hash() override {};

        Sha384Hash &operator=(const Sha384Hash &other);

        Sha384Hash &operator=(Sha384Hash &&other) noexcept;

    public:
        size_t size() const override {return _size;}

        std::string to_string() const override;

        virtual std::ostream& print(std::ostream &os) const override;

        bool operator==(const Hash &rhs) const override;

    protected:
        const uint8_t* data() const override { return _data; }

    private:
        const static size_t _size = 48;
        value_type _data[_size];
    };

    template<typename T>
    constexpr Sha384Hash::Sha384Hash(const std::initializer_list<T> &&list)
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

#endif //HASH_LIB_SHA384_HASH_H
