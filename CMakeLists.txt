cmake_minimum_required(VERSION 4.2)
project(hash-library)
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt
    ON
    CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
add_library(hash-library STATIC crc32.c keccak.cpp md5.cpp sha1.cpp sha256.cpp sha3.cpp)
target_include_directories(hash-library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
enable_testing()
add_executable(hash-library-test tests/hash_test.cpp)
target_link_libraries(hash-library-test PRIVATE hash-library GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(hash-library-test)
