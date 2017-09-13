
#include <chrono>
#include <sstream>
#include <thread>

#include "bt_state_3.hpp"
#include "../util/ndn_helpers.hpp"

namespace ndn {
namespace homesec {
namespace protocol {

void
WaitingForGwAuth::next()
{
  const int interestLifeTimeMs = 5000;
  LOG(INFO) << "BT stage 3 (WaitingForGwAuth) starts... ";
  std::string n = BT_OWNER_PREFIX + "/auth/for/" + this->getConfig()->getId();

  Interest inst(n);
  inst.setMustBeFresh(true);
  inst.setInterestLifetime(time::milliseconds(interestLifeTimeMs));

  DataCallback onData = [this](const Interest& interest, const Data& data) {
    if (!this->isInSession()) {
      LOG(WARNING) << "WaitingForGwAuth onData not in session.";
      return;
    }

    LOG(INFO) << "R2: data: [" << data.getName().toUri() << "]\r\n\tcontent: "
              << toHex(data.getContent().value(), data.getContent().value_size(), true);
    this->onReceiveR2(this->getSession(), this->getConfig(), interest, data);
  };

  NackCallback onNack = [this](const Interest& i, const lp::Nack& n) {
    LOG(ERROR) << "NACK: " << i.getName().toUri() << " : " << n.getReason();
    std::ostringstream os;
    os << n.getReason();
    std::string reason = os.str();
    this->getSession()->onFailed(reason);
  };

  const int retry = 5;
  expressInterest(FaceHolder::get(), inst, retry, onData, onNack);
}

void
WaitingForGwAuth::onReceiveR2(BtSession* session,
                              shared_ptr<DeviceConfig> cfg,
                              const Interest& interest,
                              const Data& data)
{
  LOG(INFO) << "received data for " << interest.toUri();
  if (impl::validateR2(session, data)) {
    session->onSuc(cfg);
    session->setDone(true);
    LOG(INFO) << "bootstrap done. ";
  }
  else {
    session->onFailed("R2 dismatch");
  }
}

} // namespace protocol
} // namespace homesec
} // namespace ndn