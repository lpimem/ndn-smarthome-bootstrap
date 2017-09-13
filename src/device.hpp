
#ifndef HOMESEC_DEVICE_HPP
#define HOMESEC_DEVICE_HPP

#include <chrono>
#include <map>
#include <string>
#include <thread>

#include <ndn-cxx/common.hpp>
#include <ndn-cxx/face.hpp>
#include <ndn-cxx/security/key-chain.hpp>
#include <ndn-cxx/security/pib/identity.hpp>
#include <ndn-cxx/util/scheduler.hpp>
#include <ndn-cxx/util/time.hpp>

#include "constants.h"
#include "keyring.hpp"
#include "protocol/bootstrap.hpp"

namespace ndn {
namespace homesec {

using ServiceHandler = void (*)(Interest& interest, Face& face);

class Device : noncopyable
{
public:
  Device(std::string deviceId, std::string pin)
    : m_devId(deviceId)
    , m_pin(pin)
    , m_identity(generateIdentity())
  {
  }

  void
  run();

protected:
  void
  declareService(Name& prefix, ServiceHandler handler);

  void
  stopService(Name& name);

  void
  onBootstrapSuccess(shared_ptr<protocol::DeviceConfig> cfg) const;

  void
  onBootstrapFailed(std::string message) const;

private:
  security::Identity
  generateIdentity();

  void
  onInterest(const InterestFilter& filter, const Interest& interest);

  void
  onRegisterFailed(const Name& prefix, const std::string& reason);

  void
  sendData(Name& dataName, std::string content);

  void
  onDataInterest(const InterestFilter& filter, const Interest& interest);


private:
  std::string m_devId;
  std::string m_pin;
  std::string m_prefix;
  security::Identity m_identity;
};
} // namespace homesec
} // namespace ndn

#endif // HOMESEC_DEVICE_H
