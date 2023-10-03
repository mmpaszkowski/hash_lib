//
// Created by noname on 09.01.2021.
//

#include <sstream>
#include <iomanip>
#include "crypto/hash/Sha512_256.h"

namespace hash
{
    Sha512_256::Sha512_256(const Sha512_256 &other)
    {
        for(size_t i = 0; i < _size; i++)
            _data[i] = other._data[i];
    }

    Sha512_256::Sha512_256(Sha512_256 &&other) noexcept
    {
        for(size_t i = 0; i < _size; i++)
            _data[i] = other._data[i];
    }

    Sha512_256 &Sha512_256::operator=(const Sha512_256 &other)
    {
        return *this = Sha512_256(other);
    }

    Sha512_256 &Sha512_256::operator=(Sha512_256 &&other) noexcept
    {
        for(size_t i = 0; i < size(); i++)
            _data[i] = other._data[i];
        return *this;
    }

    std::ostream &Sha512_256::print(std::ostream &os) const
    {
        for (const auto &item : _data)
        {
            os << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(item);
        }
        return os;
    }

    std::string Sha512_256::to_string() const
    {
        std::stringstream ss;
        print(ss);
        return ss.str();
    }

    bool Sha512_256::operator==(const Hash &rhs) const
    {
        for (size_t i = 0; i < this->size(); i++)
            if (this->_data[i] != rhs.data()[i])
                return false;
        return true;
    }
}
