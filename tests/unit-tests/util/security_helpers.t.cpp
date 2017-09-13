//
// Created by Lei Pi on 3/9/17.
//


#include <algorithm>
#include <iostream>

#include <ndn-cxx/util/string-helper.hpp>

#include "easylogging/easylogging++.h"
#include "util/security_helpers.hpp"

INITIALIZE_EASYLOGGINGPP

#define CATCH_CONFIG_MAIN
#include "../../catch.hpp"

namespace ndn {
namespace homesec {
namespace sec {
namespace tests {

uint8_t key[] =
  {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

uint8_t plainText[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a,
                       0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
                       0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

uint8_t iv[] =
  {0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

uint8_t cipherText[] = {0x07, 0x4d, 0x32, 0x68, 0xc3, 0x40, 0x64, 0x43, 0x1e, 0x66, 0x4c, 0x25,
                        0x66, 0x42, 0x0f, 0x59, 0x0a, 0x51, 0x19, 0x07, 0x67, 0x5c, 0x0e, 0xfa,
                        0xa6, 0x8c, 0xbb, 0xaf, 0xfd, 0xea, 0x47, 0xd4, 0xc7, 0x2c, 0x12, 0x34,
                        0x79, 0xde, 0xec, 0xc8, 0x75, 0x33, 0x8f, 0x6b, 0xd6, 0x55, 0xf3, 0xfa};

TEST_CASE("security helpers", "[BlockCipher]")
{
  const int plainTextSize = sizeof(plainText);
  const int keySize = sizeof(key);
  const int cipherTextSize = sizeof(cipherText);

  SECTION("Using fixture key and iv")
  {
    ConstBufferPtr pt = decrypt_aes(cipherText, cipherTextSize, key, keySize, iv);

    int size = pt->size();
    REQUIRE(std::equal(pt->get(), pt->get() + size, plainText));
  }

  SECTION("Using fixture key and random iv")
  {
    // debug
    std::cout << "key to use : ";
    printHex(std::cout, key, sizeof(key));
    std::cout << std::endl;
    // end of debug

    // encrypt
    ConstBufferPtr ct = encrypt_aes(plainText, plainTextSize, key, keySize);
    // debug
    std::cout << "cipher0 : ";
    printHex(std::cout, ct->get(), ct->size());
    std::cout << std::endl;
    std::cout << "- - - - - - - - - - " << std::endl;
    // end of debug

    // decrypt
    ConstBufferPtr pt = decrypt_aes(ct->get(), ct->size(), key, keySize);

    const u_int8_t* ptbuf = pt->get();
    const size_t ptbuf_size = pt->size();

    // print infor for debug
    std::cout << "deciphered: \t";
    printHex(std::cout, ptbuf, ptbuf_size);
    std::cout << std::endl;
    std::cout << "plaintext: \t";
    printHex(std::cout, plainText, plainTextSize);
    std::cout << std::endl;
    // end of print

    REQUIRE(std::equal(ptbuf, ptbuf + (ptbuf_size - 1), plainText));
  }
}

} // namespace tests
} // namespace sec
} // namespace homesec
} // namespace ndn