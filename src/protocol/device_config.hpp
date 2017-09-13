#ifndef DEVICE_CONFIG_HPP
#define DEVICE_CONFIG_HPP

#include <string>

#include <ndn-cxx/face.hpp>
#include <ndn-cxx/util/string-helper.hpp>

#include "../easylogging/easylogging++.h"

namespace ndn {
namespace homesec {
namespace protocol {

/**
 * Dynamic configurations of a device, filled during bootstrapping 
 * process.
 */
class DeviceConfig
{
public:
  DeviceConfig(std::string devId, std::string pin)
    : m_id(devId)
    , m_pin(pin)
  {
  }

  /**
   * TODO: this is actully the owner's key
   */
  Buffer
  getGwPubKey() const;

  /**
   * TODO: this is actully the owner's key
   */
  void
  setGwPubKey(Buffer gwPubKey);

  Buffer
  getDevicePubKey() const;

  void
  setDevicePubKey(Buffer devicePubKey);

  const std::string
  getId() const;

  const std::string
  getPin() const;

private:
  std::string m_id;
  std::string m_pin;
  Buffer m_gwPubKey;
  Buffer m_devicePubKey;
};

} // namespace protocol
} // namespace homesec
} // namespace ndn

#endif /* DEVICE_CONFIG_HPP */
