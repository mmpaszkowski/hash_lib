#include "crypto/cipher/Aes.h"

//
// Created by noname on 17.09.23.
//
Aes::Aes(const Key &key) : key_(key) { this->expand_key(key_); }

Aes::Aes(Key &&key) noexcept: key_(std::move(key)) { this->expand_key(key_); }


