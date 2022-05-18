//
// Created by noname on 23.12.2020.
//

#ifndef HASH_LIB_CHUNK_H
#define HASH_LIB_CHUNK_H

#include <iostream>

namespace tool
{
    template<typename T, size_t s>
    class Chunk
    {
    public:
        typedef T value_type;
        typedef T *pointer;
        typedef const T *const_pointer;
        typedef value_type &reference;
        typedef const value_type &const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;

    public:
        Chunk() = default;

        Chunk(const Chunk &other);

        Chunk(Chunk &&other) noexcept;

        ~Chunk() = default;

        Chunk &operator=(const Chunk &other);

        Chunk &operator=(Chunk &&other) noexcept;

    public:
        T &operator[](size_t index) {return data[index];}

        const T &operator[](size_t index) const {return data[index];}

        static size_t size() {return s;}

        const T *begin() const {return data;}

        const T *end() const {return data + s;}

        template<typename _T, size_t _s>
        friend std::ostream &operator<<(std::ostream &os, const Chunk<_T, _s> &t);

    private:
        T data[s]{};
    };

    template<typename T, size_t s>
    Chunk<T, s>::Chunk(const Chunk &other)
    {
        std::copy(std::begin(other.data), std::end(other.data), &data[0]);
    }

    template<typename T, size_t s>
    Chunk<T, s>::Chunk(Chunk &&other) noexcept
    {
        std::move(std::begin(other.data), std::end(other.data), &data[0]);
    }

    template<typename T, size_t s>
    Chunk<T, s> &Chunk<T, s>::operator=(const Chunk &other)
    {
        return *this = chunk(other);
    }

    template<typename T, size_t s>
    Chunk<T, s> &Chunk<T, s>::operator=(Chunk &&other) noexcept
    {
        std::move(std::begin(other.data), std::end(other.data), &data[0]);
        return *this;
    }

    template<typename T, size_t s>
    std::ostream &operator<<(std::ostream &os, const Chunk<T, s> &t)
    {
        bool is_first = true;
        os << "[\n";
        for (const auto &item : t)
        {
            if (!is_first)
                os << ",\n";
            os << item;
            is_first = false;
        }
        os << "]\n";
        return os;
    }
}

#endif //HASH_LIB_CHUNK_H
