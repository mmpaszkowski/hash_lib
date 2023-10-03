//
// Created by noname on 09.01.2021.
//

#include <sstream>
#include <iomanip>
#include "crypto/hash/Sha1.h"

namespace hash
{
    Sha1::Sha1(const Sha1 &other) : _data{}
    {
        for(size_t i = 0; i < _size; i++)
            _data[i] = other._data[i];
    }

    Sha1::Sha1(Sha1 &&other) noexcept : _data{}
    {
        for(size_t i = 0; i < _size; i++)
            _data[i] = other._data[i];
    }

    Sha1 &Sha1::operator=(const Sha1 &other)
    {
        return *this = Sha1(other);
    }

    Sha1 &Sha1::operator=(Sha1 &&other) noexcept
    {
        for(size_t i = 0; i < size(); i++)
            _data[i] = other._data[i];
        return *this;
    }

    std::ostream &Sha1::print(std::ostream &os) const
    {
        for (const auto &item : _data)
        {
            os << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(item);
        }
        return os;
    }

    std::string Sha1::to_string() const
    {
        std::stringstream ss;
        print(ss);
        return ss.str();
    }

    bool Sha1::operator==(const Hash &rhs) const
    {
        for (size_t i = 0; i < this->size(); i++)
            if (this->_data[i] != rhs.data()[i])
                return false;
        return true;
    }
}
