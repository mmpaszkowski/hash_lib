FetchContent_Declare(
        gtest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.10.0)

FetchContent_MakeAvailable(gtest)


# Tests need to be added as executables first
add_executable(testlib testlib.cpp word.h sha0.h sha1.h)

# I'm using C++17 in the test
target_compile_features(testlib PRIVATE cxx_std_20)

# Should be linked to the main library, as well as the Catch2 testing library
target_link_libraries(testlib PRIVATE hash gtest)

# This depends on (header only) boost
target_link_libraries(hash PRIVATE Boost::boost)

# If you register a test, then ctest and make test will run it. You can also run
# examples and check the output, as well.
add_test(NAME testlibtest COMMAND testlib) # Command can be a target
