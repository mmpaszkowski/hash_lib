//
// Created by noname on 23.12.2020.
//

#ifndef HASH_LIB_WORD_H
#define HASH_LIB_WORD_H

#include <iomanip>
#include <cstddef>

namespace tool
{
    template<size_t s>
    class Word
    {
    public:
        typedef std::byte value_type;
        typedef std::byte *pointer;
        typedef const std::byte *const_pointer;
        typedef value_type &reference;
        typedef const value_type &const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;

    public:
        Word() = default;

        constexpr Word(std::initializer_list<std::byte> &&list)
        {
            size_t i = 0;
            for (auto &&item : list)
            {
                data[i++] = item;
            }
        }

        Word(const Word &other);

        Word(Word &&other) noexcept;

        ~Word() = default;

        Word &operator=(const Word &other);

        Word &operator=(Word &&other) noexcept;

    public:
        std::byte &operator[](size_t index) {return data[index];}

        const std::byte &operator[](size_t index) const {return data[index];}

        static size_t size() {return s;}

        const std::byte *begin() const {return data;}

        const std::byte *end() const {return data + s;}

        std::string to_string() const;

        Word operator+(const Word &rhs) const;

        Word operator^(const Word &rhs) const;

        Word operator&(const Word &rhs) const;

        Word operator|(const Word &rhs) const;

        bool operator==(const Word &rhs) const;

        bool operator!=(const Word &rhs) const;

        Word operator~() const;

        Word left_rotate(std::size_t count) const;

        Word right_rotate(std::size_t count) const;

        Word left_shift(std::size_t count) const;

        Word right_shift(std::size_t count) const;

        template<size_t ss>
        friend std::ostream &operator<<(std::ostream &os, const Word<ss> &t);

    private:
        std::byte data[s]{};
    };

    template<size_t s>
    Word<s>::Word(const Word<s> &other)
    {
        std::copy(std::begin(other.data), std::end(other.data), &data[0]);
    }

    template<size_t s>
    Word<s>::Word(Word<s> &&other) noexcept
    {
        std::move(std::begin(other.data), std::end(other.data), &data[0]);
    }

    template<size_t s>
    Word<s> &Word<s>::operator=(const Word<s> &other)
    {
        return *this = Word(other);
    }

    template<size_t s>
    Word<s> &Word<s>::operator=(Word<s> &&other) noexcept
    {
        std::move(std::begin(other.data), std::end(other.data), &data[0]);
        return *this;
    }

    template<size_t s>
    std::string Word<s>::to_string() const
    {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    template<size_t s>
    Word<s> Word<s>::operator+(const Word<s> &rhs) const
    {
        Word result;
        bool overloaded = false;
        for (size_t i = 0; i < s; i++)
        {
            result[s - i - 1] = static_cast<std::byte>(static_cast<unsigned char>(this->data[s - i - 1]) +
                                                       static_cast<unsigned char>(rhs.data[s - i - 1]));
            if (overloaded)
            {
                result[s - i - 1] = static_cast<std::byte>(static_cast<unsigned char>(result[s - i - 1]) + 1);
                if(this->data[s - i - 1] == static_cast<std::byte>(255) && this->data[s - i - 1] == static_cast<std::byte>(255))
                    overloaded = true;
                else
                    overloaded = false;
            }

            if (result[s - i - 1] < this->data[s - i - 1] || result[s - i - 1] < rhs.data[s - i - 1])
                overloaded = true;
        }
        return result;
    }

    template<size_t s>
    Word<s> Word<s>::operator^(const Word<s> &rhs) const
    {
        Word result;
        for (size_t i = 0; i < s; i++)
            result[i] = this->data[i] ^ rhs.data[i];
        return result;
    }

    template<size_t s>
    Word<s> Word<s>::operator&(const Word<s> &rhs) const
    {
        Word result;
        for (size_t i = 0; i < s; i++)
            result[i] = this->data[i] & rhs.data[i];
        return result;
    }

    template<size_t s>
    Word<s> Word<s>::operator|(const Word<s> &rhs) const
    {
        Word result;
        for (size_t i = 0; i < s; i++)
            result[i] = this->data[i] | rhs.data[i];
        return result;
    }

    template<size_t s>
    bool Word<s>::operator==(const Word<s> &rhs) const
    {
        for (size_t i = 0; i < s; i++)
            if (this->data[i] != rhs.data[i])
                return false;
        return true;
    }

    template<size_t s>
    bool Word<s>::operator!=(const Word<s> &rhs) const
    {
        if (!(*this == rhs))
            return true;
        return false;
    }

    template<size_t s>
    Word<s> Word<s>::operator~() const
    {
        Word result;
        for (size_t i = 0; i < s; i++)
            result[i] = ~this->data[i];
        return result;
    }

    template<size_t s>
    Word<s> Word<s>::left_rotate(std::size_t count) const
    {
        if (count == 0)
            return *this;
        Word<s> result;
        Word<s> tmp = *this;

        for (std::size_t i = 0; i < count; i++)
        {
            std::byte last_bit = (tmp.data[0] & static_cast<std::byte>(0x80)) >> 7;
            for (std::size_t j = 0; j < s; j++)
            {
                result[s - j - 1] = (tmp.data[s - j - 1] << 1) | last_bit;
                last_bit = (tmp.data[s - j - 1] & static_cast<std::byte>(0x80)) >> 7;
            }
            tmp = result;
        }
        return result;
    }

    template<size_t s>
    Word<s> Word<s>::right_rotate(std::size_t count) const
    {
        return left_rotate(s * 8 - (count % (s * 8)));
    }

    template<size_t s>
    Word<s> Word<s>::left_shift(std::size_t count) const
    {
        if (count == 0)
            return *this;
        Word<s> result;
        Word<s> tmp = *this;

        for (std::size_t i = 0; i < count; i++)
        {
            std::byte last_bit = static_cast<std::byte>(0x00);
            for (std::size_t j = 0; j < s; j++)
            {
                result[s - j - 1] = (tmp.data[s - j - 1] << 1) | last_bit;
                last_bit = (tmp.data[s - j - 1] & static_cast<std::byte>(0x80)) >> 7;
            }
            tmp = result;
        }
        return result;
    }

    template<size_t s>
    Word<s> Word<s>::right_shift(std::size_t count) const
    {
        if (count == 0)
            return *this;
        Word<s> result;
        Word<s> tmp = *this;

        for (std::size_t i = 0; i < count; i++)
        {
            std::byte last_bit = static_cast<std::byte>(0x00);
            for (std::size_t j = 0; j < s; j++)
            {
                result[j] = (tmp.data[j] >> 1) | (last_bit << 7);
                last_bit = (tmp.data[j] & static_cast<std::byte>(0x01));
            }
            tmp = result;
        }
        return result;
    }

    template<size_t _s>
    std::ostream &operator<<(std::ostream &os, const Word<_s> &t)
    {
        for (const auto &item : t)
        {
            os << std::hex << std::setfill('0') << std::setw(2) << std::to_integer<int>(item);
        }
        return os;
    }
}

#endif //HASH_LIB_WORD_H
