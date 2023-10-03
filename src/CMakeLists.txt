set(HEADER_LIST
        ../include/crypto/cipher/Aes.h
        ../include/crypto/cipher/Gcm.h
        ../include/crypto/cipher/Cipher.h
        ../include/crypto/cipher/GHash.h
        ../include/crypto/cipher/OperationMode.h
        ../include/crypto/hash/Hash.h
        ../include/crypto/hash/HashingAlgorithm.h
        ../include/crypto/hash/Sha0.h
        ../include/crypto/hash/Sha0Algorithm.h
        ../include/crypto/hash/Sha1.h
        ../include/crypto/hash/Sha1Algorithm.h
        ../include/crypto/hash/Sha224.h
        ../include/crypto/hash/Sha224Algorithm.h
        ../include/crypto/hash/Sha256Algorithm.h
        ../include/crypto/hash/Sha384.h
        ../include/crypto/hash/Sha384Algorithm.h
        ../include/crypto/hash/Sha512.h
        ../include/crypto/hash/Sha512Algorithm.h
        ../include/crypto/hash/Sha512_224.h
        ../include/crypto/hash/Sha512_224Algorithm.h
        ../include/crypto/hash/Sha512_256.h
        ../include/crypto/hash/Sha512_256Algorithm.h
        ../include/crypto/tool/Binary.h
        ../include/crypto/tool/Block.h
        ../include/crypto/tool/Chunk.h
        ../include/crypto/tool/Word.h
        )


# Make an automatic library - will be static or dynamic based on user setting
add_library(hash
        Aes.cpp
        Gcm.cpp
        GHash.cpp
        Key.cpp
        Mode.cpp
        Sha0.cpp
        Sha0Algorithm.cpp
        Sha1.cpp
        Sha1Algorithm.cpp
        Sha224.cpp
        Sha224Algorithm.cpp
        Sha256.cpp
        Sha256Algorithm.cpp
        Sha384.cpp
        Sha384Algorithm.cpp
        Sha512.cpp
        Sha512Algorithm.cpp
        Sha512_224.cpp
        Sha512_224Algorithm.cpp
        Sha512_256.cpp
        Sha512_256Algorithm.cpp
        ${HEADER_LIST}
        )

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
