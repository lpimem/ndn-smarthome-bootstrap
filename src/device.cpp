
#include "device.hpp"

namespace ndn {
namespace homesec {

ndn::Name
getDeviceName(std::string& deviceId)
{
  return ndn::Name(HOME_PREFIX + "/dev/" + deviceId);
}

void
Device::run()
{
  // bootstrapping
  auto bt = make_shared<protocol::Bootstrap>(m_identity);
  auto onSuccess = [this](shared_ptr<protocol::DeviceConfig> cfg) { this->onBootstrapSuccess(cfg); };
  auto onFail = [=](std::string message) {
    this->onBootstrapFailed(message);
    LOG(INFO) << "Will retry in a few seconds";
    std::chrono::milliseconds zzz(2000);
    std::this_thread::sleep_for(zzz);
    this->run();
  };
  bt->startBootstrap(onSuccess, onFail);
}

/**
 * Default interest dispatcher. 
 */
void
Device::onInterest(const InterestFilter& filter, const Interest& interest)
{
  Name name(interest.getName());
  LOG(DEBUG) << "Received interest: " << name.toUri();
}

void
Device::onRegisterFailed(const Name& prefix, const std::string& reason)
{
  LOG(ERROR) << "Failed register prefix: \t\"" << prefix << "\"." << std::endl
             << "Reason: \t" << reason << std::endl;
  FaceHolder::get()->shutdown();
}

void
Device::sendData(Name& dataName, std::string content)
{
  shared_ptr<Data> data = make_shared<Data>();
  data->setName(dataName);
  data->setFreshnessPeriod(time::seconds(INTEREST_FRESH_SECONDS));
  data->setContent(reinterpret_cast<const uint8_t*>(content.c_str()), content.length());
  keyring::get()->sign(*data);
  FaceHolder::get()->put(*data);
}

void
Device::onDataInterest(const InterestFilter& filter, const Interest& interest)
{
  Name name = interest.getName();
  LOG(INFO) << "Received interest: " << name.toUri();
}

void
Device::declareService(Name& prefix, ServiceHandler handler)
{
}

/**
 * Create default identity if not one exists.
 */
security::Identity
Device::generateIdentity()
{
  Name deviceName = getDeviceName(m_devId);
  security::Identity identity = keyring::get()->createIdentity(deviceName);
  LOG(INFO) << "generated identity for device [" << m_devId << "]" << deviceName.toUri();
  return identity;
}

void
Device::stopService(Name& name)
{
}

void
Device::onBootstrapSuccess(shared_ptr<protocol::DeviceConfig> cfg) const
{
  LOG(INFO) << "Bootstrap Success " << std::endl
            << "\t Owner Pubkey:\t" << toHex(cfg->getGwPubKey()) << std::endl;
}

void
Device::onBootstrapFailed(std::string message) const
{
  LOG(ERROR) << "Bootstrap Failed : " << message;
}
} // namespace homesec
} // namespace ndn