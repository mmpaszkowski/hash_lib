//
// Created by noname on 09.01.2021.
//

#ifndef CRYPTO_SHA384_H
#define CRYPTO_SHA384_H

#include "Hash.h"

namespace hash
{
    class Sha384: public Hash
    {
    public:
        Sha384() = default;

        template<typename T>
        constexpr Sha384(const std::initializer_list<T> &&list);

        Sha384(const Sha384 &other);

        Sha384(Sha384 &&other) noexcept;

        ~Sha384() override {};

        Sha384 &operator=(const Sha384 &other);

        Sha384 &operator=(Sha384 &&other) noexcept;

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
    constexpr Sha384::Sha384(const std::initializer_list<T> &&list)
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

#endif //CRYPTO_SHA384_H
