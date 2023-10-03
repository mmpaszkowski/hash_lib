//
// Created by noname on 09.01.2021.
//

#ifndef CRYPTO_SHA1_H
#define CRYPTO_SHA1_H

#include "Hash.h"

namespace hash
{
    class Sha1: public Hash
    {
    public:
        Sha1() = default;

        template<typename T>
        constexpr Sha1(const std::initializer_list<T> &&list);

        Sha1(const Sha1 &other);

        Sha1(Sha1 &&other) noexcept;

        ~Sha1() override = default;

        Sha1 &operator=(const Sha1 &other);

        Sha1 &operator=(Sha1 &&other) noexcept;

    public:
        [[nodiscard]] size_t size() const override {return _size;}

        [[nodiscard]] std::string to_string() const override;

        std::ostream& print(std::ostream &os) const override;

        bool operator==(const Hash &rhs) const override;

    protected:
        [[nodiscard]] const uint8_t* data() const override { return _data; }

    private:
        const static size_t _size = 20;
        value_type _data[_size];
    };

    template<typename T>
    constexpr Sha1::Sha1(const std::initializer_list<T> &&list) : _data{}
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

#endif //CRYPTO_SHA1_H
