//
// Created by noname on 09.01.2021.
//

#include <sstream>
#include <iomanip>
#include <cstddef>
#include "hash/sha224_hash.h"

namespace hash
{
    Sha224Hash::Sha224Hash(const Sha224Hash &other)
    {
        for(size_t i = 0; i < size(); i++)
            _data[i] = other._data[i];
    }

    Sha224Hash::Sha224Hash(Sha224Hash &&other) noexcept
    {
        for(size_t i = 0; i < size(); i++)
            _data[i] = std::move(other._data[i]);
    }

    Sha224Hash &Sha224Hash::operator=(const Sha224Hash &other)
    {
        return *this = Sha224Hash(other);
    }

    Sha224Hash &Sha224Hash::operator=(Sha224Hash &&other) noexcept
    {
        for(size_t i = 0; i < size(); i++)
            _data[i] = std::move(other._data[i]);
        return *this;
    }

    std::ostream &Sha224Hash::print(std::ostream &os) const
    {
        for (const auto &item : _data)
        {
            os << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(item);
        }
        return os;
    }

    std::string Sha224Hash::to_string() const
    {
        std::stringstream ss;
        print(ss);
        return ss.str();
    }

    bool Sha224Hash::operator==(const Hash &rhs) const
    {
        for (size_t i = 0; i < this->size(); i++)
            if (this->_data[i] != rhs.data()[i])
                return false;
        return true;
    }
}
