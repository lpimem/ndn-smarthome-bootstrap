//
// Created by Lei Pi on 2/24/17.
//

#include "DeviceConfigs.hpp"

namespace ndn {
namespace homesec {

DeviceConfigs&
DeviceConfigs::getInstance()
{
  static DeviceConfigs ins("SampleDeviceID12345", "unsafe");
  return ins;
}

const std::string&
DeviceConfigs::getDeviceId() const
{
  return m_deviceId;
}

const std::string&
DeviceConfigs::getPin() const
{
  return m_pin;
}
} // namespace homesec
} // namespace ndn
