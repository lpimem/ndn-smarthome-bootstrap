#ifndef BT_STATE_1_HPP
#define BT_STATE_1_HPP

#include "bt_session.hpp"
#include "bt_state.hpp"

namespace ndn {
namespace homesec {
namespace protocol {

class WaitingForGwPubKey : public BtState
{
public:
  WaitingForGwPubKey(BtSession* session, shared_ptr<DeviceConfig> cfg)
    : BtState(session, cfg, BtStage::FetchingGwPubkey)
  {
  }

  void
  next();

protected:
  static void
  onReceivedPubKey(BtSession* session, shared_ptr<DeviceConfig> config, const Interest&, const Data&);
};
} // namespace protocol
} // namespace homesec
} // namespace ndn
#endif /* BT_STATE_1_HPP */
