# Note that headers are optional, and do not affect add_library, but they will
# not show up in IDEs unless they are listed in add_library.

# Optionally glob, but only for CMake 3.12 or later: file(GLOB HEADER_LIST
# CONFIGURE_DEPENDS "${ModernCMakeExample_SOURCE_DIR}/include/modern/*.hpp")
set(HEADER_LIST ../include/tool/chunk.h ../include/tool/word.h ../include/hash/hash.h ../include/hash/sha0_hash.h ../include/hash/sha1_hash.h ../include/hash/sha224_hash.h ../include/hash/sha384_hash.h ../include/hash/sha512_hash.h ../include/hash/sha512_224_hash.h ../include/hash/sha512_256_hash.h ../include/hash/hash_algorithm.h ../include/hash/sha0.h ../include/hash/sha1.h ../include/hash/sha224.h ../include/hash/sha256.h ../include/hash/sha384.h ../include/hash/sha512.h ../include/hash/sha512_224.h ../include/hash/sha512_256.h ../include/tool/binary.h)

# Make an automatic library - will be static or dynamic based on user setting
add_library(hash sha0_hash.cpp sha1_hash.cpp sha224_hash.cpp sha256_hash.cpp sha384_hash.cpp sha512_hash.cpp sha512_224_hash.cpp sha512_256_hash.cpp sha0.cpp sha1.cpp sha224.cpp sha256.cpp sha384.cpp sha512.cpp sha512_224.cpp sha512_256.cpp ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(hash PUBLIC ../include)

# This depends on (header only) boost
target_link_libraries(hash PRIVATE Boost::boost)

# All users of this library will need at least C++11
target_compile_features(hash PUBLIC cxx_std_20)

# IDEs should put the headers in a nice place
source_group(
        TREE "${PROJECT_SOURCE_DIR}/include"
        PREFIX "Header Files"
        FILES ${HEADER_LIST})
