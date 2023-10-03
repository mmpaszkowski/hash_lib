//
// Created by noname on 09.01.2021.
//

#ifndef CRYPTO_SHA256_H
#define CRYPTO_SHA256_H

#include "Hash.h"

namespace hash
{
    class Sha256: public Hash
    {
    public:
        Sha256() = default;

        template<typename T>
        constexpr Sha256(const std::initializer_list<T> &&list);

        Sha256(const Sha256 &other);

        Sha256(Sha256 &&other) noexcept;

        ~Sha256() override {};

        Sha256 &operator=(const Sha256 &other);

        Sha256 &operator=(Sha256 &&other) noexcept;

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
    constexpr Sha256::Sha256(const std::initializer_list<T> &&list)
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

#endif //CRYPTO_SHA256_H
