add_library(hash_lib ../src/sha0.cpp ../include/hash/sha0.h ../src/sha1.cpp ../include/hash/sha1.h)

target_compile_features(hash_lib PRIVATE cxx_std_20)

target_link_libraries(hash_lib PRIVATE hash)
