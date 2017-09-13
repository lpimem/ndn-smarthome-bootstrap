//
// Created by Lei Pi on 2/27/17.
//

#ifndef HOMESEC_KEYRING_HPP
#define HOMESEC_KEYRING_HPP

#include <ndn-cxx/security/v2/key-chain.hpp>

namespace ndn {
namespace homesec {


class keyring
{
public:
  static ndn::security::v2::KeyChain*
  get();

private:
  keyring(){};

private:
  ndn::security::v2::KeyChain* keyChain =
    new ndn::security::v2::KeyChain("pib-memory:", "tpm-memory:", true);
};

} // namespace homesec
} // namespace ndn


#endif //HOMESEC_KEYRING_HPP
