//
// Created by noname on 15.09.23.
//

#include "crypto/cipher/Key.h"

Key::Key(const uint8_t *data, size_t size) : size_(size) {
    this->data_ = new uint8_t[size_];
    for (size_t i = 0; i < size; i++)
        this->data_[i] = data[i];
}

Key::Key(const std::initializer_list<uint8_t> &data) : size_(data.size()) {
    this->data_ = new uint8_t[size_];

    size_t i = 0;
    for (auto &&item: data) {
        this->data_[i++] = item;
    }
}

Key::Key(const Key &k) {
    this->size_ = k.size_;
    this->data_ = new uint8_t[size_];
    for (size_t i = 0; i < k.size_; i++)
        this->data_[i] = k.data_[i];
}

Key::Key(Key &&k) noexcept {
    this->size_ = k.size_;
    this->data_ = k.data_;
    k.data_ = nullptr;
}

Key::~Key() { delete[] this->data_; }

Key &Key::operator=(const Key &k) {
    this->size_ = k.size_;
    this->data_ = new uint8_t[size_];
    for (size_t i = 0; i < k.size_; i++)
    for (size_t i = 0; i < k.size_; i++)
        this->data_[i] = k.data_[i];
    return *this;
}

Key &Key::operator=(Key &&k) noexcept {
    this->size_ = k.size_;
    this->data_ = k.data_;
    k.data_ = nullptr;
    return *this;
}

size_t Key::size() const { return size_; }
