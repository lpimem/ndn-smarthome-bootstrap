#include "bt_state_1.hpp"
#include "bt_state_2.hpp"
#include "../util/ndn_helpers.hpp"
#include "details/bootstrap_impl.hpp"

#include <sstream>

namespace ndn {
namespace homesec {
namespace protocol {

void
WaitingForGwPubKey::next()
{
  const std::string keyname = BT_NAME_OWNER_PUBKEY + "/for/" + getConfig()->getId();

  Interest interest(keyname);
  interest.setMustBeFresh(true);
  interest.setInterestLifetime(time::milliseconds(1000));

  auto onNack = [&](const Interest& i, const lp::Nack& n) {
    LOG(ERROR) << "NACK: " << i.getName().toUri() << " : " << n.getReason();
    std::ostringstream os;
    os << n.getReason();
    std::string reason = os.str();
    this->getSession()->onFailed(reason);
  };

  auto onData = [this](const Interest& interest, const Data& data) {
    if (!this->isInSession()) {
      LOG(WARNING) << "WaitingForGwPubKey onData not in session.";
      return;
    }
    LOG(INFO) << "received data from " << data.getName().toUri();
    this->onReceivedPubKey(this->getSession(), this->getConfig(), interest, data);
  };

  const int retry = 5;
  expressInterest(FaceHolder::get(), interest, retry, onData, onNack);
}

void
WaitingForGwPubKey::onReceivedPubKey(BtSession* session,
                                     shared_ptr<DeviceConfig> config,
                                     const ndn::Interest& inst,
                                     const ndn::Data& data)
{
  impl::parseGwPubKey(session, data, config);
  shared_ptr<BtState> state =
    std::dynamic_pointer_cast<BtState>(make_shared<PublishingDevicePubKey>(session, config));
  state->setR1(session->getCurrentState()->getR1());
  session->setState(state);
  state->next();
}

} // namespace protocol
} // namespace homesec
} // namespace ndn