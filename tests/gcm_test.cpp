//
// Created by noname on 26.08.23.
//

#include <gtest/gtest.h>
#include "crypto/cipher/Gcm.h"


TEST(gcm, encryption_gcm_1) {
    Key key({0x11, 0x75, 0x4c, 0xd7, 0x2a, 0xec, 0x30, 0x9b, 0xf5, 0x2f, 0x76, 0x87, 0x21, 0x2e, 0x89, 0x57});
    uint8_t iv[] = {0x3c, 0x81, 0x9d, 0x9a, 0x9b, 0xed, 0x08, 0x76, 0x15, 0x03, 0x0b, 0x65};
    uint8_t* data = nullptr;
    uint8_t* associated_data = nullptr;

    uint8_t cryptogram[16];

    Gcm aes((Aes(key)));
    aes.init(iv, sizeof(iv), associated_data, 0);
    aes.encrypt(data, 0, cryptogram);

    std::vector<uint8_t> expected_cryptogram = {0x25, 0x03, 0x27, 0xc6, 0x74, 0xaa, 0xf4, 0x77, 0xae, 0xf2, 0x67, 0x57, 0x48, 0xcf, 0x69, 0x71};

    for(size_t i = 0; i < 16; i++)
    {
        GTEST_ASSERT_EQ(cryptogram[i], expected_cryptogram[i]);
    }
}


TEST(gcm, encryption_gcm_2) {
    Key key({0xfe, 0x47, 0xfc, 0xce, 0x5f, 0xc3, 0x26, 0x65, 0xd2, 0xae, 0x39, 0x9e, 0x4e, 0xec, 0x72, 0xba});
    uint8_t iv[] = {0x5a, 0xdb, 0x96, 0x09, 0xdb, 0xae, 0xb5, 0x8c, 0xbd, 0x6e, 0x72, 0x75};
    uint8_t data[] = {0x7c, 0x0e, 0x88, 0xc8, 0x88, 0x99, 0xa7, 0x79, 0x22, 0x84, 0x65, 0x07, 0x47, 0x97, 0xcd, 0x4c, 0x2e, 0x14, 0x98, 0xd2, 0x59, 0xb5, 0x43, 0x90, 0xb8, 0x5e, 0x3e, 0xef, 0x1c, 0x02, 0xdf, 0x60, 0xe7, 0x43, 0xf1, 0xb8, 0x40, 0x38, 0x2c, 0x4b, 0xcc, 0xaf, 0x3b, 0xaf, 0xb4, 0xca, 0x84, 0x29, 0xbe, 0xa0, 0x63};
    uint8_t associated_data[] = {0x88, 0x31, 0x9d, 0x6e, 0x1d, 0x3f, 0xfa, 0x5f, 0x98, 0x71, 0x99, 0x16, 0x6c, 0x8a, 0x9b, 0x56, 0xc2, 0xae, 0xba, 0x5a};

    uint8_t cryptogram[sizeof(data) + 16];

    Gcm aes((Aes(key)));
    aes.init(iv, sizeof(iv), associated_data, sizeof(associated_data));
    aes.encrypt(data, sizeof(data), cryptogram);

    uint8_t expected_cryptogram[] = {0x98, 0xf4, 0x82, 0x6f, 0x05, 0xa2, 0x65, 0xe6, 0xdd, 0x2b, 0xe8, 0x2d, 0xb2, 0x41, 0xc0, 0xfb, 0xbb, 0xf9, 0xff, 0xb1, 0xc1, 0x73, 0xaa, 0x83, 0x96, 0x4b, 0x7c, 0xf5, 0x39, 0x30, 0x43, 0x73, 0x63, 0x65, 0x25, 0x3d, 0xdb, 0xc5, 0xdb, 0x87, 0x78, 0x37, 0x14, 0x95, 0xda, 0x76, 0xd2, 0x69, 0xe5, 0xdb, 0x3e, 0x29, 0x1e, 0xf1, 0x98, 0x2e, 0x4d, 0xef, 0xed, 0xaa, 0x22, 0x49, 0xf8, 0x98, 0x55, 0x6b, 0x47};

    for(size_t i = 0; i < sizeof(expected_cryptogram); i++)
    {
        GTEST_ASSERT_EQ(cryptogram[i], expected_cryptogram[i]);
    }
}


TEST(gcm, encryption_gcm_3) {
    Key key({0xc7, 0xd9, 0x35, 0x8a, 0xf0, 0xfd, 0x73, 0x7b, 0x11, 0x8d, 0xbf, 0x43, 0x47, 0xfd, 0x25, 0x2a});
    uint8_t iv[] = {0x83, 0xde, 0x9f, 0xa5, 0x22, 0x80, 0x52, 0x2b, 0x55, 0x29, 0x0e, 0xbe, 0x3b, 0x06, 0x72, 0x86, 0xd8, 0x76, 0x90, 0x56, 0x01, 0x79, 0x55, 0x41, 0x53, 0xcb, 0x33, 0x41, 0xa0, 0x4e, 0x15, 0xc5, 0xf3, 0x53, 0x90, 0x60, 0x2f, 0xa0, 0x7e, 0x5b, 0x5f, 0x16, 0xdc, 0x38, 0xcf, 0x08, 0x2b, 0x11, 0xad, 0x6d, 0xd3, 0xfa, 0xb8, 0x55, 0x2d, 0x2b, 0xf8, 0xd9, 0xc8, 0x98, 0x1b, 0xbf, 0xc5, 0xf3, 0xb5, 0x7e, 0x5e, 0x30, 0x66, 0xe3, 0xdf, 0x23, 0xf0, 0x78, 0xfa, 0x25, 0xbc, 0xe6, 0x3d, 0x3d, 0x6f, 0x86, 0xce, 0x9f, 0xbc, 0x2c, 0x67, 0x96, 0x55, 0xb9, 0x58, 0xb0, 0x9a, 0x99, 0x13, 0x92, 0xeb, 0x93, 0xb4, 0x53, 0xba, 0x6e, 0x7b, 0xf8, 0x24, 0x2f, 0x8f, 0x61, 0x32, 0x9e, 0x3a, 0xfe, 0x75, 0xd0, 0xf8, 0x53, 0x6a, 0xa7, 0xe5, 0x07, 0xd7, 0x58, 0x91, 0xe5, 0x40, 0xfb, 0x1d, 0x7e};
    uint8_t data[] = {0x42, 0x2f, 0x46, 0x22, 0x3f, 0xdd, 0xff, 0x25, 0xfc, 0x7a, 0x6a, 0x89, 0x7d, 0x20, 0xdc, 0x8a, 0xf6, 0xcc, 0x8a, 0x37, 0x82, 0x8c, 0x90, 0xbd, 0x95, 0xfa, 0x9b, 0x94, 0x3f, 0x46, 0x0e, 0xb0, 0xa2, 0x6f, 0x29, 0xff, 0xc4, 0x83, 0x59, 0x2e, 0xfb, 0x64, 0x83, 0x57, 0x74, 0x16, 0x0a, 0x1b, 0xb5, 0xc0, 0xcd};
    uint8_t associated_data[] = {0x5d, 0x2b, 0x9a, 0x4f, 0x99, 0x4f, 0xfa, 0xa0, 0x30, 0x00, 0x14, 0x99, 0x56, 0xc8, 0x93, 0x2e, 0x85, 0xb1, 0xa1, 0x67, 0x29, 0x45, 0x14, 0xe3, 0x88, 0xb7, 0x3b, 0x10, 0x80, 0x8f, 0x50, 0x9e, 0xa7, 0x3c, 0x07, 0x5e, 0xcb, 0xf4, 0x3c, 0xec, 0xfe, 0xc1, 0x3c, 0x20, 0x2a, 0xfe, 0xd6, 0x21, 0x10, 0xda, 0xbf, 0x80, 0x26, 0xd2, 0x37, 0xf4, 0xe7, 0x65, 0x85, 0x3b, 0xc0, 0x78, 0xf3, 0xaf, 0xe0, 0x81, 0xd0, 0xa1, 0xf8, 0xd8, 0xf7, 0x55, 0x6b, 0x8e, 0x42, 0xac, 0xc3, 0xcc, 0xe8, 0x88, 0x26, 0x21, 0x85, 0x04, 0x8d, 0x67, 0xc5, 0x5b, 0x2d, 0xf1};

    uint8_t cryptogram[sizeof(data) + 16];

    Gcm aes((Aes(key)));
    aes.init(iv, sizeof(iv), associated_data, sizeof(associated_data));
    aes.encrypt(data, sizeof(data), cryptogram);

    uint8_t expected_ciphertext[] = {0x86, 0xeb, 0xa4, 0x91, 0x15, 0x78, 0xac, 0x72, 0xac, 0x30, 0xc2, 0x5f, 0xe4, 0x24, 0xda, 0x9a, 0xb6, 0x25, 0xf2, 0x9b, 0x5c, 0x00, 0xe3, 0x6d, 0x2c, 0x24, 0xa2, 0x73, 0x3d, 0xc4, 0x01, 0x23, 0xdc, 0x57, 0xa8, 0xc9, 0xf1, 0x7a, 0x24, 0xa2, 0x6c, 0x09, 0xc7, 0x3a, 0xd4, 0xef, 0xbc, 0xba, 0x3b, 0xab, 0x5b, 0x49, 0x23, 0x05, 0x19, 0x03, 0x44, 0x61, 0x8c, 0xab, 0x8b, 0x40, 0xf0, 0x06, 0xa5, 0x71, 0x86};
    for(size_t i = 0; i < sizeof(cryptogram); i++)
    {
        std::cout << i;
        GTEST_ASSERT_EQ(cryptogram[i], expected_ciphertext[i]);
    }
}

TEST(gcm, decryption_gcm_1) {
    Key key({0x11, 0x75, 0x4c, 0xd7, 0x2a, 0xec, 0x30, 0x9b, 0xf5, 0x2f, 0x76, 0x87, 0x21, 0x2e, 0x89, 0x57});
    uint8_t iv[] = {0x3c, 0x81, 0x9d, 0x9a, 0x9b, 0xed, 0x08, 0x76, 0x15, 0x03, 0x0b, 0x65};
    uint8_t cryptogram[] = {0x25, 0x03, 0x27, 0xc6, 0x74, 0xaa, 0xf4, 0x77, 0xae, 0xf2, 0x67, 0x57, 0x48, 0xcf, 0x69, 0x71};
    uint8_t* associated_data = nullptr;

    uint8_t* data = nullptr;

    Gcm aes((Aes(key)));
    aes.init(iv, sizeof(iv), associated_data, 0);
    aes.decrypt(cryptogram, sizeof(cryptogram), data);
}

TEST(gcm, decryption_gcm_2) {
    Key key({0xfe, 0x47, 0xfc, 0xce, 0x5f, 0xc3, 0x26, 0x65, 0xd2, 0xae, 0x39, 0x9e, 0x4e, 0xec, 0x72, 0xba});
    uint8_t iv[] = {0x5a, 0xdb, 0x96, 0x09, 0xdb, 0xae, 0xb5, 0x8c, 0xbd, 0x6e, 0x72, 0x75};
    uint8_t cryptogram[] = {0x98, 0xf4, 0x82, 0x6f, 0x05, 0xa2, 0x65, 0xe6, 0xdd, 0x2b, 0xe8, 0x2d, 0xb2, 0x41, 0xc0, 0xfb, 0xbb, 0xf9, 0xff, 0xb1, 0xc1, 0x73, 0xaa, 0x83, 0x96, 0x4b, 0x7c, 0xf5, 0x39, 0x30, 0x43, 0x73, 0x63, 0x65, 0x25, 0x3d, 0xdb, 0xc5, 0xdb, 0x87, 0x78, 0x37, 0x14, 0x95, 0xda, 0x76, 0xd2, 0x69, 0xe5, 0xdb, 0x3e, 0x29, 0x1e, 0xf1, 0x98, 0x2e, 0x4d, 0xef, 0xed, 0xaa, 0x22, 0x49, 0xf8, 0x98, 0x55, 0x6b, 0x47};
    uint8_t associated_data[] = {0x88, 0x31, 0x9d, 0x6e, 0x1d, 0x3f, 0xfa, 0x5f, 0x98, 0x71, 0x99, 0x16, 0x6c, 0x8a, 0x9b, 0x56, 0xc2, 0xae, 0xba, 0x5a};

    uint8_t data[sizeof(cryptogram) - 16];

    Gcm aes((Aes(key)));
    aes.init(iv, sizeof(iv), associated_data, sizeof(associated_data));
    aes.decrypt(cryptogram, sizeof(cryptogram), data);

    uint8_t expected_data[] = {0x7c, 0x0e, 0x88, 0xc8, 0x88, 0x99, 0xa7, 0x79, 0x22, 0x84, 0x65, 0x07, 0x47, 0x97, 0xcd, 0x4c, 0x2e, 0x14, 0x98, 0xd2, 0x59, 0xb5, 0x43, 0x90, 0xb8, 0x5e, 0x3e, 0xef, 0x1c, 0x02, 0xdf, 0x60, 0xe7, 0x43, 0xf1, 0xb8, 0x40, 0x38, 0x2c, 0x4b, 0xcc, 0xaf, 0x3b, 0xaf, 0xb4, 0xca, 0x84, 0x29, 0xbe, 0xa0, 0x63};

    for(size_t i = 0; i < sizeof(expected_data); i++)
    {
        GTEST_ASSERT_EQ(data[i], expected_data[i]);
    }
}

TEST(gcm, decryption_gcm_3) {
    Key key({0xc7, 0xd9, 0x35, 0x8a, 0xf0, 0xfd, 0x73, 0x7b, 0x11, 0x8d, 0xbf, 0x43, 0x47, 0xfd, 0x25, 0x2a});
    uint8_t iv[] = {0x83, 0xde, 0x9f, 0xa5, 0x22, 0x80, 0x52, 0x2b, 0x55, 0x29, 0x0e, 0xbe, 0x3b, 0x06, 0x72, 0x86, 0xd8, 0x76, 0x90, 0x56, 0x01, 0x79, 0x55, 0x41, 0x53, 0xcb, 0x33, 0x41, 0xa0, 0x4e, 0x15, 0xc5, 0xf3, 0x53, 0x90, 0x60, 0x2f, 0xa0, 0x7e, 0x5b, 0x5f, 0x16, 0xdc, 0x38, 0xcf, 0x08, 0x2b, 0x11, 0xad, 0x6d, 0xd3, 0xfa, 0xb8, 0x55, 0x2d, 0x2b, 0xf8, 0xd9, 0xc8, 0x98, 0x1b, 0xbf, 0xc5, 0xf3, 0xb5, 0x7e, 0x5e, 0x30, 0x66, 0xe3, 0xdf, 0x23, 0xf0, 0x78, 0xfa, 0x25, 0xbc, 0xe6, 0x3d, 0x3d, 0x6f, 0x86, 0xce, 0x9f, 0xbc, 0x2c, 0x67, 0x96, 0x55, 0xb9, 0x58, 0xb0, 0x9a, 0x99, 0x13, 0x92, 0xeb, 0x93, 0xb4, 0x53, 0xba, 0x6e, 0x7b, 0xf8, 0x24, 0x2f, 0x8f, 0x61, 0x32, 0x9e, 0x3a, 0xfe, 0x75, 0xd0, 0xf8, 0x53, 0x6a, 0xa7, 0xe5, 0x07, 0xd7, 0x58, 0x91, 0xe5, 0x40, 0xfb, 0x1d, 0x7e};
    uint8_t cryptogram[] = {0x86, 0xeb, 0xa4, 0x91, 0x15, 0x78, 0xac, 0x72, 0xac, 0x30, 0xc2, 0x5f, 0xe4, 0x24, 0xda, 0x9a, 0xb6, 0x25, 0xf2, 0x9b, 0x5c, 0x00, 0xe3, 0x6d, 0x2c, 0x24, 0xa2, 0x73, 0x3d, 0xc4, 0x01, 0x23, 0xdc, 0x57, 0xa8, 0xc9, 0xf1, 0x7a, 0x24, 0xa2, 0x6c, 0x09, 0xc7, 0x3a, 0xd4, 0xef, 0xbc, 0xba, 0x3b, 0xab, 0x5b, 0x49, 0x23, 0x05, 0x19, 0x03, 0x44, 0x61, 0x8c, 0xab, 0x8b, 0x40, 0xf0, 0x06, 0xa5, 0x71, 0x86};
    uint8_t associated_data[] = {0x5d, 0x2b, 0x9a, 0x4f, 0x99, 0x4f, 0xfa, 0xa0, 0x30, 0x00, 0x14, 0x99, 0x56, 0xc8, 0x93, 0x2e, 0x85, 0xb1, 0xa1, 0x67, 0x29, 0x45, 0x14, 0xe3, 0x88, 0xb7, 0x3b, 0x10, 0x80, 0x8f, 0x50, 0x9e, 0xa7, 0x3c, 0x07, 0x5e, 0xcb, 0xf4, 0x3c, 0xec, 0xfe, 0xc1, 0x3c, 0x20, 0x2a, 0xfe, 0xd6, 0x21, 0x10, 0xda, 0xbf, 0x80, 0x26, 0xd2, 0x37, 0xf4, 0xe7, 0x65, 0x85, 0x3b, 0xc0, 0x78, 0xf3, 0xaf, 0xe0, 0x81, 0xd0, 0xa1, 0xf8, 0xd8, 0xf7, 0x55, 0x6b, 0x8e, 0x42, 0xac, 0xc3, 0xcc, 0xe8, 0x88, 0x26, 0x21, 0x85, 0x04, 0x8d, 0x67, 0xc5, 0x5b, 0x2d, 0xf1};

    uint8_t data[sizeof(cryptogram) - 16];

    Gcm aes((Aes(key)));
    aes.init(iv, sizeof(iv), associated_data, sizeof(associated_data));
    aes.decrypt(cryptogram, sizeof(cryptogram), data);

    uint8_t expected_data[] = {0x42, 0x2f, 0x46, 0x22, 0x3f, 0xdd, 0xff, 0x25, 0xfc, 0x7a, 0x6a, 0x89, 0x7d, 0x20, 0xdc, 0x8a, 0xf6, 0xcc, 0x8a, 0x37, 0x82, 0x8c, 0x90, 0xbd, 0x95, 0xfa, 0x9b, 0x94, 0x3f, 0x46, 0x0e, 0xb0, 0xa2, 0x6f, 0x29, 0xff, 0xc4, 0x83, 0x59, 0x2e, 0xfb, 0x64, 0x83, 0x57, 0x74, 0x16, 0x0a, 0x1b, 0xb5, 0xc0, 0xcd};
    for(size_t i = 0; i < sizeof(expected_data); i++)
    {
        GTEST_ASSERT_EQ(data[i], expected_data[i]);
    }
}