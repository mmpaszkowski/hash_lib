//
// Created by noname on 09.01.2021.
//

#include <sstream>
#include <iomanip>
#include <cstddef>
#include "hash/sha0_hash.h"

namespace hash
{
    Sha0Hash::Sha0Hash(const Sha0Hash &other)
    {
        for(size_t i = 0; i < size(); i++)
            _data[i] = other._data[i];
    }

    Sha0Hash::Sha0Hash(Sha0Hash &&other) noexcept
    {
        for(size_t i = 0; i < size(); i++)
            _data[i] = std::move(other._data[i]);
    }

    Sha0Hash &Sha0Hash::operator=(const Sha0Hash &other)
    {
        return *this = Sha0Hash(other);
    }

    Sha0Hash &Sha0Hash::operator=(Sha0Hash &&other) noexcept
    {
        for(size_t i = 0; i < size(); i++)
            _data[i] = std::move(other._data[i]);
        return *this;
    }

    std::ostream &Sha0Hash::print(std::ostream &os) const
    {
        for (const auto &item : _data)
        {
            os << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(item);
        }
        return os;
    }

    std::string Sha0Hash::to_string() const
    {
        std::stringstream ss;
        print(ss);
        return ss.str();
    }

    bool Sha0Hash::operator==(const Hash &rhs) const
    {
        for (size_t i = 0; i < this->size(); i++)
            if (this->_data[i] != rhs.data()[i])
                return false;
        return true;
    }
}
