//
// Created by Lei Pi on 2/27/17.
//

#include "keyring.hpp"
namespace ndn {
namespace homesec {

ndn::security::v2::KeyChain*
keyring::get()
{
  static keyring ins;
  return ins.keyChain;
}

} // namespace homesec
} // namespace ndn
