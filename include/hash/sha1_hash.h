//
// Created by noname on 09.01.2021.
//

#ifndef HASH_LIB_SHA1_HASH_H
#define HASH_LIB_SHA1_HASH_H

#include "hash.h"

namespace hash
{
    class Sha1Hash: public Hash
    {
    public:
        Sha1Hash() = default;

        template<typename T>
        constexpr Sha1Hash(const std::initializer_list<T> &&list);

        Sha1Hash(const Sha1Hash &other);

        Sha1Hash(Sha1Hash &&other) noexcept;

        ~Sha1Hash() override {};

        Sha1Hash &operator=(const Sha1Hash &other);

        Sha1Hash &operator=(Sha1Hash &&other) noexcept;

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
    constexpr Sha1Hash::Sha1Hash(const std::initializer_list<T> &&list)
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

#endif //HASH_LIB_SHA1_HASH_H
