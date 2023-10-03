//
// Created by noname on 28.12.2020.
//

#include <gtest/gtest.h>
#include <crypto/tool/Word.h>

TEST(word_comparison, equation)
{
    tool::Word<4> w1 = {static_cast<std::byte>(0x04), static_cast<std::byte>(0x03), static_cast<std::byte>(0x02),
                        static_cast<std::byte>(0x01)};

    tool::Word<4> w2 = {static_cast<std::byte>(0x04), static_cast<std::byte>(0x03), static_cast<std::byte>(0x02),
                        static_cast<std::byte>(0x01)};

    GTEST_ASSERT_EQ(w1, w2);
}

TEST(word_comparison, differention)
{
    tool::Word<4> w1 = {static_cast<std::byte>(0x04), static_cast<std::byte>(0x03), static_cast<std::byte>(0x02),
                        static_cast<std::byte>(0x01)};

    tool::Word<4> w2 = {static_cast<std::byte>(0x04), static_cast<std::byte>(0x03), static_cast<std::byte>(0x02),
                        static_cast<std::byte>(0x02)};

    GTEST_ASSERT_NE(w1, w2);
}

TEST(word_mathematical_operation, addition)
{
    tool::Word<4> w1 = {static_cast<std::byte>(0x04), static_cast<std::byte>(0x03), static_cast<std::byte>(0x02),
                        static_cast<std::byte>(0x01)};

    tool::Word<4> w2 = {static_cast<std::byte>(0x04), static_cast<std::byte>(0x03), static_cast<std::byte>(0x02),
                        static_cast<std::byte>(0xff)};

    tool::Word<4> result = {static_cast<std::byte>(0x08), static_cast<std::byte>(0x06),
                            static_cast<std::byte>(0x05),
                            static_cast<std::byte>(0x00)};

    tool::Word<4> a1 = {static_cast<std::byte>(0xb7), static_cast<std::byte>(0x36), static_cast<std::byte>(0x79),
                        static_cast<std::byte>(0xa2)};

    tool::Word<4> a2 = {static_cast<std::byte>(0x01), static_cast<std::byte>(0x3e), static_cast<std::byte>(0x86),
                        static_cast<std::byte>(0x3c)};

    tool::Word<4> a3 = {static_cast<std::byte>(0xaf), static_cast<std::byte>(0xf4), static_cast<std::byte>(0xff),
                        static_cast<std::byte>(0xc1)};

    tool::Word<4> a4 = {static_cast<std::byte>(0x88), static_cast<std::byte>(0x3c), static_cast<std::byte>(0x4f),
                        static_cast<std::byte>(0xbb)};

    tool::Word<4> r1 = {static_cast<std::byte>(0xf0), static_cast<std::byte>(0xa6), static_cast<std::byte>(0x4f),
                        static_cast<std::byte>(0x5a)};

    tool::Word<4> r2 = {static_cast<std::byte>(0xb8), static_cast<std::byte>(0x74), static_cast<std::byte>(0xff),
                        static_cast<std::byte>(0xde)};

    tool::Word<4> r3 = {static_cast<std::byte>(0x68), static_cast<std::byte>(0x69), static_cast<std::byte>(0xff),
                        static_cast<std::byte>(0x9f)};


    GTEST_ASSERT_EQ(r2 + a3, r3);
    GTEST_ASSERT_EQ(w1 + w2, result);
    GTEST_ASSERT_EQ(a1 + a2, r2);
    GTEST_ASSERT_EQ(a1 + a2 + a3 + a4, r1);

}

TEST(word_mathematical_operation, left_rotation)
{
    tool::Word<4> w1 = {static_cast<std::byte>(0b10101010), static_cast<std::byte>(0b11111111),
                        static_cast<std::byte>(0b10101010), static_cast<std::byte>(0b11111111)};

    tool::Word<4> result1 = {static_cast<std::byte>(0b01010101), static_cast<std::byte>(0b11111111),
                             static_cast<std::byte>(0b01010101), static_cast<std::byte>(0b11111111)};

    tool::Word<4> result2 = {static_cast<std::byte>(0b10101011), static_cast<std::byte>(0b11111110),
                             static_cast<std::byte>(0b10101011), static_cast<std::byte>(0b11111110)};

    GTEST_ASSERT_EQ(w1.left_rotate(1), result1);
    GTEST_ASSERT_EQ(w1.left_rotate(2), result2);
    GTEST_ASSERT_EQ(w1.left_rotate(32), w1);
}

TEST(word_mathematical_operation, right_rotation)
{
    tool::Word<4> w1 = {static_cast<std::byte>(0b10101010), static_cast<std::byte>(0b11111111),
                        static_cast<std::byte>(0b10101010), static_cast<std::byte>(0b11111111)};

    tool::Word<4> result1 = {static_cast<std::byte>(0b11010101), static_cast<std::byte>(0b01111111),
                             static_cast<std::byte>(0b11010101), static_cast<std::byte>(0b01111111)};

    tool::Word<4> result2 = {static_cast<std::byte>(0b11101010), static_cast<std::byte>(0b10111111),
                             static_cast<std::byte>(0b11101010), static_cast<std::byte>(0b10111111)};

    GTEST_ASSERT_EQ(w1.right_rotate(1), result1);
    GTEST_ASSERT_EQ(w1.right_rotate(2), result2);
    GTEST_ASSERT_EQ(w1.right_rotate(32), w1);
}

TEST(word_mathematical_operation, left_shift)
{
    tool::Word<4> w1 = {static_cast<std::byte>(0b10101010), static_cast<std::byte>(0b11111111),
                        static_cast<std::byte>(0b10101010), static_cast<std::byte>(0b11111111)};

    tool::Word<4> result1 = {static_cast<std::byte>(0b01010101), static_cast<std::byte>(0b11111111),
                             static_cast<std::byte>(0b01010101), static_cast<std::byte>(0b11111110)};

    tool::Word<4> result2 = {static_cast<std::byte>(0b10101011), static_cast<std::byte>(0b11111110),
                             static_cast<std::byte>(0b10101011), static_cast<std::byte>(0b11111100)};

    tool::Word<4> result3 = {static_cast<std::byte>(0b00000000), static_cast<std::byte>(0b00000000),
                             static_cast<std::byte>(0b00000000), static_cast<std::byte>(0b00000000)};

    GTEST_ASSERT_EQ(w1.left_shift(1), result1);
    GTEST_ASSERT_EQ(w1.left_shift(2), result2);
    GTEST_ASSERT_EQ(w1.left_shift(32), result3);
}

TEST(word_mathematical_operation, right_shift)
{
    tool::Word<4> w1 = {static_cast<std::byte>(0b10101010), static_cast<std::byte>(0b11111111),
                        static_cast<std::byte>(0b10101010), static_cast<std::byte>(0b11111111)};

    tool::Word<4> result1 = {static_cast<std::byte>(0b01010101), static_cast<std::byte>(0b01111111),
                             static_cast<std::byte>(0b11010101), static_cast<std::byte>(0b01111111)};

    tool::Word<4> result2 = {static_cast<std::byte>(0b00101010), static_cast<std::byte>(0b10111111),
                             static_cast<std::byte>(0b11101010), static_cast<std::byte>(0b10111111)};

    tool::Word<4> result3 = {static_cast<std::byte>(0b00000000), static_cast<std::byte>(0b00000000),
                             static_cast<std::byte>(0b00000000), static_cast<std::byte>(0b00000000)};


    GTEST_ASSERT_EQ(w1.right_shift(1), result1);
    GTEST_ASSERT_EQ(w1.right_shift(2), result2);
    GTEST_ASSERT_EQ(w1.right_shift(32), result3);
}

//TEST(word_mathematical_operation, addition_long)
//{
//    for(size_t i = 0; i <= 65536; i++)
//        for(size_t j = 0; j <= 65536; j++)
//            GTEST_ASSERT_EQ(tool::Word<4>({static_cast<std::byte>((i & 0xff000000) >> 24), static_cast<std::byte>((i & 0xff0000) >> 16), static_cast<std::byte>((i & 0xff00) >> 8), static_cast<std::byte>((i & 0xff) >> 0)}) + tool::Word<4>({static_cast<std::byte>((j & 0xff000000) >> 24), static_cast<std::byte>((j & 0xff0000) >> 16), static_cast<std::byte>((j & 0xff00) >> 8), static_cast<std::byte>((j & 0xff) >> 0)}), tool::Word<4>({static_cast<std::byte>(((i+j) & 0xff000000) >> 24), static_cast<std::byte>(((i+j) & 0xff0000) >> 16), static_cast<std::byte>(((i+j) & 0xff00) >> 8), static_cast<std::byte>(((i+j) & 0xff) >> 0)}));
//}
//
//TEST(word_mathematical_operation, left_rotation_long)
//{
//    auto left_rotate = [](size_t n, unsigned int d) { return (n << d)|(n >> (32 - d)); };
//    for(size_t i = 0; i <= 4294967296; i++)
//        for(size_t j = 0; j <= 32; j++)
//        {
//            GTEST_ASSERT_EQ(tool::Word<4>({static_cast<std::byte>((i & 0xff000000) >> 24), static_cast<std::byte>((i & 0xff0000) >> 16), static_cast<std::byte>((i & 0xff00) >> 8), static_cast<std::byte>((i & 0xff) >> 0)}).left_rotate(j), tool::Word<4>({static_cast<std::byte>((left_rotate(i, j) & 0xff000000) >> 24), static_cast<std::byte>((left_rotate(i, j) & 0xff0000) >> 16), static_cast<std::byte>((left_rotate(i, j) & 0xff00) >> 8), static_cast<std::byte>((left_rotate(i, j) & 0xff) >> 0)}));
//        }
//}
//
//TEST(word_mathematical_operation, right_rotation_long)
//{
//    auto right_rotate = [](size_t n, unsigned int d) { return (n >> d)|(n << (32 - d)); };
//    for(size_t i = 0; i <= 4294967296; i++)
//        for(size_t j = 0; j <= 32; j++)
//        {
//            GTEST_ASSERT_EQ(tool::Word<4>({static_cast<std::byte>((i & 0xff000000) >> 24), static_cast<std::byte>((i & 0xff0000) >> 16), static_cast<std::byte>((i & 0xff00) >> 8), static_cast<std::byte>((i & 0xff) >> 0)}).right_rotate(j), tool::Word<4>({static_cast<std::byte>((right_rotate(i, j) & 0xff000000) >> 24), static_cast<std::byte>((right_rotate(i, j) & 0xff0000) >> 16), static_cast<std::byte>((right_rotate(i, j) & 0xff00) >> 8), static_cast<std::byte>((right_rotate(i, j) & 0xff) >> 0)}));
//        }
//}
//
//TEST(word_mathematical_operation, left_shift_long)
//{
//    auto left_shift = [](size_t n, unsigned int d) { return n << d; };
//    for(size_t i = 0; i <= 4294967296; i++)
//        for(size_t j = 0; j <= 32; j++)
//        {
//            GTEST_ASSERT_EQ(tool::Word<4>({static_cast<std::byte>((i & 0xff000000) >> 24), static_cast<std::byte>((i & 0xff0000) >> 16), static_cast<std::byte>((i & 0xff00) >> 8), static_cast<std::byte>((i & 0xff) >> 0)}).left_rotate(j), tool::Word<4>({static_cast<std::byte>((left_shift(i, j) & 0xff000000) >> 24), static_cast<std::byte>((left_shift(i, j) & 0xff0000) >> 16), static_cast<std::byte>((left_shift(i, j) & 0xff00) >> 8), static_cast<std::byte>((left_shift(i, j) & 0xff) >> 0)}));
//        }
//}
//
//TEST(word_mathematical_operation, right_shift_long)
//{
//    auto right_shift = [](size_t n, unsigned int d) { return n >> d; };
//    for(size_t i = 0; i <= 4294967296; i++)
//        for(size_t j = 0; j <= 32; j++)
//        {
//            GTEST_ASSERT_EQ(tool::Word<4>({static_cast<std::byte>((i & 0xff000000) >> 24), static_cast<std::byte>((i & 0xff0000) >> 16), static_cast<std::byte>((i & 0xff00) >> 8), static_cast<std::byte>((i & 0xff) >> 0)}).left_rotate(j), tool::Word<4>({static_cast<std::byte>((right_shift(i, j) & 0xff000000) >> 24), static_cast<std::byte>((right_shift(i, j) & 0xff0000) >> 16), static_cast<std::byte>((right_shift(i, j) & 0xff00) >> 8), static_cast<std::byte>((right_shift(i, j) & 0xff) >> 0)}));
//        }
//}
