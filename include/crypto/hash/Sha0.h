//
// Created by noname on 09.01.2021.
//

#ifndef CRYPTO_SHA0_H
#define CRYPTO_SHA0_H

#include "Hash.h"

namespace hash
{
    class Sha0: public Hash
    {
    public:
        Sha0() = default;

        template<typename T>
        constexpr Sha0(const std::initializer_list<T> &&list);

        Sha0(const Sha0 &other);

        Sha0(Sha0 &&other) noexcept;

        ~Sha0() override {};

        Sha0 &operator=(const Sha0 &other);

        Sha0 &operator=(Sha0 &&other) noexcept;

    public:
        size_t size() const override {return _size;}

        std::string to_string() const override;

        virtual std::ostream& print(std::ostream &os) const override;

        bool operator==(const Hash &rhs) const override;

    protected:
        const uint8_t* data() const override { return _data; }

    private:
        const static size_t _size = 20;
        value_type _data[_size];
    };

    template<typename T>
    constexpr Sha0::Sha0(const std::initializer_list<T> &&list)
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

#endif //CRYPTO_SHA0_H
