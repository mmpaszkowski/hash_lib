//
// Created by noname on 09.01.2021.
//

#include <sstream>
#include <iomanip>
#include <cstddef>
#include "hash/sha512_256_hash.h"

namespace hash
{
    Sha512_256Hash::Sha512_256Hash(const Sha512_256Hash &other)
    {
        for(size_t i = 0; i < size(); i++)
            _data[i] = other._data[i];
    }

    Sha512_256Hash::Sha512_256Hash(Sha512_256Hash &&other) noexcept
    {
        for(size_t i = 0; i < size(); i++)
            _data[i] = std::move(other._data[i]);
    }

    Sha512_256Hash &Sha512_256Hash::operator=(const Sha512_256Hash &other)
    {
        return *this = Sha512_256Hash(other);
    }

    Sha512_256Hash &Sha512_256Hash::operator=(Sha512_256Hash &&other) noexcept
    {
        for(size_t i = 0; i < size(); i++)
            _data[i] = std::move(other._data[i]);
        return *this;
    }

    std::ostream &Sha512_256Hash::print(std::ostream &os) const
    {
        for (const auto &item : _data)
        {
            os << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(item);
        }
        return os;
    }

    std::string Sha512_256Hash::to_string() const
    {
        std::stringstream ss;
        print(ss);
        return ss.str();
    }

    bool Sha512_256Hash::operator==(const Hash &rhs) const
    {
        for (size_t i = 0; i < this->size(); i++)
            if (this->_data[i] != rhs.data()[i])
                return false;
        return true;
    }
}
