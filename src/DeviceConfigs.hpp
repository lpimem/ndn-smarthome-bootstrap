//
// Created by Lei Pi on 2/24/17.
//

#ifndef HOMESEC_DEVICECONFIGS_HPP
#define HOMESEC_DEVICECONFIGS_HPP

#include <string>

namespace ndn {
namespace homesec {
class DeviceConfigs
{
public:
  static DeviceConfigs&
  getInstance();

  const std::string&
  getDeviceId() const;

  const std::string&
  getPin() const;

private:
  DeviceConfigs(std::string deviceId, std::string pin)
    : m_deviceId(deviceId)
    , m_pin(pin)
  {
  }

private:
  std::string m_deviceId;
  std::string m_pin;
};
} // namespace homesec
} // namespace ndn

#endif //HOMESEC_DEVICECONFIGS_HPP
