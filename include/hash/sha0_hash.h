//
// Created by noname on 09.01.2021.
//

#ifndef HASH_LIB_SHA0_HASH_H
#define HASH_LIB_SHA0_HASH_H

#include "hash.h"

namespace hash
{
    class Sha0Hash: public Hash
    {
    public:
        Sha0Hash() = default;

        template<typename T>
        constexpr Sha0Hash(const std::initializer_list<T> &&list);

        Sha0Hash(const Sha0Hash &other);

        Sha0Hash(Sha0Hash &&other) noexcept;

        ~Sha0Hash() override {};

        Sha0Hash &operator=(const Sha0Hash &other);

        Sha0Hash &operator=(Sha0Hash &&other) noexcept;

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
    constexpr Sha0Hash::Sha0Hash(const std::initializer_list<T> &&list)
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

#endif //HASH_LIB_SHA0_HASH_H
