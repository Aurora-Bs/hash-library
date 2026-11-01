// //////////////////////////////////////////////////////////
// crc32.h
// Copyright (c) 2014,2015 Stephan Brumme. All rights reserved.
// see http://create.stephan-brumme.com/disclaimer.html
//

#ifndef CRC32_H
#define CRC32_H
// #include "hash.h"
#include <string.h>
// check if C23 features can be used.
#ifdef __STDC_VERSION__
#if (__STDC_VERSION__ >= 202311L)
#define NODISCARD [[nodiscard]]
#else
#define NODISCARD
#endif
#else
#define NODISCARD
#endif
// define fixed size integer types
#ifdef _MSC_VER
// Windows
typedef unsigned __int8 uint8_t;
typedef unsigned __int32 uint32_t;
#else
// GCC
#include <stdint.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif
/// compute CRC32 hash, based on Intel's Slicing-by-8 algorithm
/** Usage:
    CRC32 crc32;
    std::string myHash  = crc32("Hello World");     // std::string
    std::string myHash2 = crc32("How are you", 11); // arbitrary data, 11 bytes

    // or in a streaming fashion:

    CRC32 crc32;
    while (more data available)
      crc32.add(pointer to fresh data, number of new bytes);
    std::string myHash3 = crc32.getHash();

    Note:
    You can find code for the faster Slicing-by-16 algorithm on my website, too:
    http://create.stephan-brumme.com/crc32/
    Its unrolled version is about twice as fast but its look-up table doubled in
   size as well.
  */
enum CRC32_ENUM {
  HashBytes = 4,
};

typedef struct CRC32 {
  uint32_t _hash;
} CRC32;
// compute the CRC32 of a memory block
NODISCARD char *CRC32_compute_block(CRC32 *crc32, const void *data,
                                    size_t numBytes);

// compute CRC32 of a null-terminated string, excluding final zero.
NODISCARD char *CRC32_compute_string(CRC32 *crc32, const char *text);

/// add arbitrary number of bytes
void CRC32_add(CRC32 *crc32, const void *data, size_t numBytes);

/// Return the latest hash as 8 hex characters
NODISCARD char *CRC32_get_hash_as_hex(CRC32 *crc32);

/// return the latest hash as bytes
void CRC32_get_hash_as_bytes(CRC32 *crc32, unsigned char buffer[HashBytes]);

/// restart
void CRC32_reset(CRC32 *crc32);

#ifdef __cplusplus
}
#endif
#endif
