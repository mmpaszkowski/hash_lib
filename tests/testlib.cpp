//
// Created by noname on 23.12.2020.
//

#include <gtest/gtest.h>
#include <iostream>
#include "word.h"
#include "sha0.h"
#include "sha1.h"
#include "sha224.h"
#include "sha256.h"
#include "sha384.h"
#include "sha512.h"
#include "sha512_224.h"
#include "sha512_256.h"

GTEST_API_ int main(int argc, char **argv)
{
    std::cout << "Running main() from " << __FILE__ << "\n";
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}