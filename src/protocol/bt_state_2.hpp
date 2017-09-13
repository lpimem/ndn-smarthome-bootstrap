#ifndef BT_STATE_2_HPP
#define BT_STATE_2_HPP

#include "bt_state.hpp"

namespace ndn {
namespace homesec {
namespace protocol {
class PublishingDevicePubKey : public BtState
{
public:
  PublishingDevicePubKey(BtSession* session, shared_ptr<DeviceConfig> cfg)
    : BtState(session, cfg, BtStage::PublishingSelfPubkey)
    , m_registered_prefix_id(nullptr)
  {
  }

  // ~PublishingDevicePubKey();

  void
  next();

protected:
  static void
  onRequestDeviceKey(BtSession* session,
                     shared_ptr<DeviceConfig> cfg,
                     const InterestFilter& prefix,
                     const Interest& interest);

private:
  void
  onInterest(const InterestFilter& filter, const Interest& interest);

private:
  RegisteredPrefixId* m_registered_prefix_id;
};

} // namespace protocol
} // namespace homesec
} // namespace ndn
#endif /* BT_STATE_2_HPP */
