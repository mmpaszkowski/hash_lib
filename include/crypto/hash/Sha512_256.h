//
// Created by noname on 09.01.2021.
//

#ifndef CRYPTO_SHA512_256_H
#define CRYPTO_SHA512_256_H

#include "Hash.h"
#include "Sha512_256.h"

namespace hash
{
    class Sha512_256: public Hash
    {
    public:
        Sha512_256() = default;

        template<typename T>
        constexpr Sha512_256(const std::initializer_list<T> &&list);

        Sha512_256(const Sha512_256 &other);

        Sha512_256(Sha512_256 &&other) noexcept;

        ~Sha512_256() override {};

        Sha512_256 &operator=(const Sha512_256 &other);

        Sha512_256 &operator=(Sha512_256 &&other) noexcept;

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
    constexpr Sha512_256::Sha512_256(const std::initializer_list<T> &&list)
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

#endif //CRYPTO_SHA512_256_H
