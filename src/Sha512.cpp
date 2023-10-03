//
// Created by noname on 09.01.2021.
//

#include <sstream>
#include <iomanip>
#include "crypto/hash/Sha512.h"

namespace hash
{
    Sha512::Sha512(const Sha512 &other)
    {
        for(size_t i = 0; i < _size; i++)
            _data[i] = other._data[i];
    }

    Sha512::Sha512(Sha512 &&other) noexcept
    {
        for(size_t i = 0; i < _size; i++)
            _data[i] = other._data[i];
    }

    Sha512 &Sha512::operator=(const Sha512 &other)
    {
        return *this = Sha512(other);
    }

    Sha512 &Sha512::operator=(Sha512 &&other) noexcept
    {
        for(size_t i = 0; i < size(); i++)
            _data[i] = other._data[i];
        return *this;
    }

    std::ostream &Sha512::print(std::ostream &os) const
    {
        for (const auto &item : _data)
        {
            os << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(item);
        }
        return os;
    }

    std::string Sha512::to_string() const
    {
        std::stringstream ss;
        print(ss);
        return ss.str();
    }

    bool Sha512::operator==(const Hash &rhs) const
    {
        for (size_t i = 0; i < this->size(); i++)
            if (this->_data[i] != rhs.data()[i])
                return false;
        return true;
    }
}
