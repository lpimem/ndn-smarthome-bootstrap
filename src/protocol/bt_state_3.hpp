#ifndef BT_STATE_3_HPP
#define BT_STATE_3_HPP

#include "bt_state.hpp"
#include "details/bootstrap_impl.hpp"

namespace ndn {
namespace homesec {
namespace protocol {
class WaitingForGwAuth : public BtState
{
public:
  WaitingForGwAuth(BtSession* session, shared_ptr<DeviceConfig> cfg)
    : BtState(session, cfg, BtStage::FetchingGwAuth)
  {
  }

  void
  next();

protected:
  static void
  onReceiveR2(BtSession* session, shared_ptr<DeviceConfig> cfg, const Interest&, const Data&);
};

} // namespace protocol
} // namespace homesec
} // namespace ndn
#endif /* BT_STATE_3_HPP */
