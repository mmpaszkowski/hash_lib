//
// Created by noname on 09.01.2021.
//

#include <sstream>
#include <iomanip>
#include "crypto/hash/Sha384.h"

namespace hash
{
    Sha384::Sha384(const Sha384 &other)
    {
        for(size_t i = 0; i < _size; i++)
            _data[i] = other._data[i];
    }

    Sha384::Sha384(Sha384 &&other) noexcept
    {
        for(size_t i = 0; i < _size; i++)
            _data[i] = std::move(other._data[i]);
    }

    Sha384 &Sha384::operator=(const Sha384 &other)
    {
        return *this = Sha384(other);
    }

    Sha384 &Sha384::operator=(Sha384 &&other) noexcept
    {
        for(size_t i = 0; i < size(); i++)
            _data[i] = other._data[i];
        return *this;
    }

    std::ostream &Sha384::print(std::ostream &os) const
    {
        for (const auto &item : _data)
        {
            os << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(item);
        }
        return os;
    }

    std::string Sha384::to_string() const
    {
        std::stringstream ss;
        print(ss);
        return ss.str();
    }

    bool Sha384::operator==(const Hash &rhs) const
    {
        for (size_t i = 0; i < this->size(); i++)
            if (this->_data[i] != rhs.data()[i])
                return false;
        return true;
    }
}
