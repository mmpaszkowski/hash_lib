FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)
set(CMAKE_CXX_FLAGS "-Ofast -Wall -Wextra")

FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(testlib
        aes_test.cpp
        gcm_test.cpp
        sha0_test.cpp
        sha1_test.cpp
        sha224_test.cpp
        sha256_test.cpp
        sha384_test.cpp
        sha512_224_test.cpp
        sha512_256_test.cpp
        sha512_test.cpp
        word_test.cpp
        )

target_link_libraries(testlib PRIVATE GTest::GTest hash)

enable_testing()
add_test(testlib testlib)
