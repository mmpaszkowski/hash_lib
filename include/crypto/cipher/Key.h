//
// Created by noname on 15.09.23.
//

#ifndef CRYPTO_KEY_H
#define CRYPTO_KEY_H

#include <cstdint>
#include <cstddef>
#include <initializer_list>

class Key {
public:
    Key(const uint8_t *data, size_t size);
    Key(const std::initializer_list<uint8_t>& data);
    Key(const Key &k);
    Key(Key &&k) noexcept;
    ~Key();

    Key &operator=(const Key &k);
    Key &operator=(Key &&k) noexcept;

public:
    [[nodiscard]] size_t size() const;
    [[nodiscard]] size_t length() const { return size_ * 8; }
    [[nodiscard]] const uint8_t *data() const { return data_; }

private:
    size_t size_;
    uint8_t *data_;
};

#endif //CRYPTO_KEY_H
