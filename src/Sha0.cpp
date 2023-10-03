//
// Created by noname on 09.01.2021.
//

#include <sstream>
#include <iomanip>
#include <cstddef>
#include "crypto/hash/Sha0.h"

namespace hash
{
    Sha0::Sha0(const Sha0 &other)
    {
        for(size_t i = 0; i < _size; i++)
            _data[i] = other._data[i];
    }

    Sha0::Sha0(Sha0 &&other) noexcept
    {
        for(size_t i = 0; i < _size; i++)
            _data[i] = other._data[i];
    }

    Sha0 &Sha0::operator=(const Sha0 &other)
    {
        return *this = Sha0(other);
    }

    Sha0 &Sha0::operator=(Sha0 &&other) noexcept
    {
        for(size_t i = 0; i < size(); i++)
            _data[i] = other._data[i];
        return *this;
    }

    std::ostream &Sha0::print(std::ostream &os) const
    {
        for (const auto &item : _data)
        {
            os << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(item);
        }
        return os;
    }

    std::string Sha0::to_string() const
    {
        std::stringstream ss;
        print(ss);
        return ss.str();
    }

    bool Sha0::operator==(const Hash &rhs) const
    {
        for (size_t i = 0; i < this->size(); i++)
            if (this->_data[i] != rhs.data()[i])
                return false;
        return true;
    }
}
