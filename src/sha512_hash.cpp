//
// Created by noname on 09.01.2021.
//

#include <sstream>
#include <iomanip>
#include <cstddef>
#include "hash/sha512_hash.h"

namespace hash
{
    Sha512Hash::Sha512Hash(const Sha512Hash &other)
    {
        for(size_t i = 0; i < size(); i++)
            _data[i] = other._data[i];
    }

    Sha512Hash::Sha512Hash(Sha512Hash &&other) noexcept
    {
        for(size_t i = 0; i < size(); i++)
            _data[i] = std::move(other._data[i]);
    }

    Sha512Hash &Sha512Hash::operator=(const Sha512Hash &other)
    {
        return *this = Sha512Hash(other);
    }

    Sha512Hash &Sha512Hash::operator=(Sha512Hash &&other) noexcept
    {
        for(size_t i = 0; i < size(); i++)
            _data[i] = std::move(other._data[i]);
        return *this;
    }

    std::ostream &Sha512Hash::print(std::ostream &os) const
    {
        for (const auto &item : _data)
        {
            os << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(item);
        }
        return os;
    }

    std::string Sha512Hash::to_string() const
    {
        std::stringstream ss;
        print(ss);
        return ss.str();
    }

    bool Sha512Hash::operator==(const Hash &rhs) const
    {
        for (size_t i = 0; i < this->size(); i++)
            if (this->_data[i] != rhs.data()[i])
                return false;
        return true;
    }
}
