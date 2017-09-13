#ifndef BOOTSTRAP_IMPL_HPP
#define BOOTSTRAP_IMPL_HPP

#include "../bt_common.hpp"
#include "../bt_state.hpp"

namespace ndn {
namespace homesec {
namespace protocol {

class Bootstrap;

class BtHelper
{
public:
  static void
  defaultOnNackReceived(const Interest& i, const lp::Nack& n)
  {
    LOG(ERROR) << "NACK: " << i.getName().toUri() << " : " << n.getReason();
    // std::exit(1);
    throw "nack " + i.getName().toUri();
  }

  static void
  defaultOnRegisterPrefixFailure(const Name& prefix, const std::string& reason)
  {
    LOG(ERROR) << "Register Prefix: " << prefix.toUri() << " : " << reason;
  }

  static void
  defaultOnTimeout(const Interest& interest)
  {
    LOG(ERROR) << "Timeout: " << interest.toUri();
    // std::exit(1);
    throw "timeout: " + interest.toUri();
  }
};

namespace impl {
shared_ptr<Buffer>
generateDevicePublicKey(DeviceConfig& cfg);

ConstBufferPtr
generateSecret(const std::string& pin);

bool
authenticateInterest(const ndn::Interest& interest, ConstBufferPtr& key);

void
parseGwPubKey(BtSession* session, const ndn::Data& data, shared_ptr<DeviceConfig> config);

void
publishDeviceKey(BtSession* session, shared_ptr<DeviceConfig> cfg, const Name& name);

bool
validateR2(BtSession* session, const ndn::Data& data);

} // namespace impl
} // namespace protocol
} // namespace homesec
} // namespace ndn

#endif /* BOOTSTRAP_IMPL_HPP */
