//
// Created by noname on 09.01.2021.
//

#ifndef CRYPTO_SHA512_224_H
#define CRYPTO_SHA512_224_H

#include "Hash.h"
#include "Sha512_224.h"

namespace hash
{
    class Sha512_224: public Hash
    {
    public:
        Sha512_224() = default;

        template<typename T>
        constexpr Sha512_224(const std::initializer_list<T> &&list);

        Sha512_224(const Sha512_224 &other);

        Sha512_224(Sha512_224 &&other) noexcept;

        ~Sha512_224() override {};

        Sha512_224 &operator=(const Sha512_224 &other);

        Sha512_224 &operator=(Sha512_224 &&other) noexcept;

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
    constexpr Sha512_224::Sha512_224(const std::initializer_list<T> &&list)
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

#endif //CRYPTO_SHA512_224_H
