//
// Created by noname on 09.01.2021.
//

#ifndef CRYPTO_SHA224_H
#define CRYPTO_SHA224_H

#include "Hash.h"

namespace hash
{
    class Sha224: public Hash
    {
    public:
        Sha224() = default;

        template<typename T>
        constexpr Sha224(const std::initializer_list<T> &&list);

        Sha224(const Sha224 &other);

        Sha224(Sha224 &&other) noexcept;

        ~Sha224() override {};

        Sha224 &operator=(const Sha224 &other);

        Sha224 &operator=(Sha224 &&other) noexcept;

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
    constexpr Sha224::Sha224(const std::initializer_list<T> &&list)
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

#endif //CRYPTO_SHA224_H
