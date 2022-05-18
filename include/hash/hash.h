//
// Created by noname on 04.01.2021.
//

#ifndef HASH_LIB_HASH_H
#define HASH_LIB_HASH_H

#include <cstdint>
#include <cstddef>
#include <string>

namespace hash
{
    class Hash
    {
    public:
        typedef uint8_t value_type;
        typedef size_t size_type;
        typedef value_type *pointer;
        typedef const pointer const_pointer;

    public:
        virtual ~Hash() {};

        virtual size_type size() const = 0; // {return this->data.size();}

        virtual std::string to_string() const = 0;

        virtual std::ostream& print(std::ostream &os) const = 0;

        virtual bool operator==(const Hash &rhs) const = 0;

        friend std::ostream &operator<<(std::ostream &os, const Hash &t);

        virtual const uint8_t* data() const = 0;
    };

    inline std::ostream &operator<<(std::ostream &os, const Hash &t)
    {
        return t.print(os);
    }
}

#endif //HASH_LIB_HASH_H
