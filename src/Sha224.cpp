//
// Created by noname on 09.01.2021.
//

#include <sstream>
#include <iomanip>
#include "crypto/hash/Sha224.h"

namespace hash
{
    Sha224::Sha224(const Sha224 &other)
    {
        for(size_t i = 0; i < _size; i++)
            _data[i] = other._data[i];
    }

    Sha224::Sha224(Sha224 &&other) noexcept
    {
        for(size_t i = 0; i < _size; i++)
            _data[i] = other._data[i];
    }

    Sha224 &Sha224::operator=(const Sha224 &other)
    {
        return *this = Sha224(other);
    }

    Sha224 &Sha224::operator=(Sha224 &&other) noexcept
    {
        for(size_t i = 0; i < _size; i++)
            _data[i] = other._data[i];
        return *this;
    }

    std::ostream &Sha224::print(std::ostream &os) const
    {
        for (const auto &item : _data)
        {
            os << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(item);
        }
        return os;
    }

    std::string Sha224::to_string() const
    {
        std::stringstream ss;
        print(ss);
        return ss.str();
    }

    bool Sha224::operator==(const Hash &rhs) const
    {
        for (size_t i = 0; i < this->size(); i++)
            if (this->_data[i] != rhs.data()[i])
                return false;
        return true;
    }
}
