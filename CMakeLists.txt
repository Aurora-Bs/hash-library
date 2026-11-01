cmake_minimum_required(VERSION 4.2)
project(hash-library)
set(CMAKE_C_STANDARD 23)
add_library(CRC32 INTERFACE crc32.c)
enable_testing()
file(GLOB other *.c)
message("OTHER FILES: ${other}")
add_executable(
  hash-library
  tests/tests.cpp
  crc32.c
  keccak.cpp
  md5.cpp
  sha1.cpp
  sha256.cpp
  sha3.cpp)
target_link_libraries(hash-library PRIVATE CRC32)
