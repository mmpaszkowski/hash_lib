//
// Created by noname on 09.01.2021.
//

#ifndef CRYPTO_SHA512_H
#define CRYPTO_SHA512_H

#include "Hash.h"
#include "Sha512.h"

namespace hash
{
    class Sha512: public Hash
    {
    public:
        Sha512() = default;

        template<typename T>
        constexpr Sha512(const std::initializer_list<T> &&list);

        Sha512(const Sha512 &other);

        Sha512(Sha512 &&other) noexcept;

        ~Sha512() override {};

        Sha512 &operator=(const Sha512 &other);

        Sha512 &operator=(Sha512 &&other) noexcept;

    public:
        size_t size() const override {return _size;}

        std::string to_string() const override;

        virtual std::ostream& print(std::ostream &os) const override;

        bool operator==(const Hash &rhs) const override;

    protected:
        const uint8_t* data() const override { return _data; }

    private:
        const static size_t _size = 64;
        value_type _data[_size];
    };

    template<typename T>
    constexpr Sha512::Sha512(const std::initializer_list<T> &&list)
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

#endif //CRYPTO_SHA512_H
