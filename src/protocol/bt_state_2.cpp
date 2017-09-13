#include "bt_state_2.hpp"
#include "bt_state_3.hpp"
#include "details/bootstrap_impl.hpp"

namespace ndn {
namespace homesec {
namespace protocol {

void
unregisterPrefix(shared_ptr<Face> face, RegisteredPrefixId* pid)
{
  LOG(INFO) << "BT Stage 2: unregistering prefix " << pid;
  face->unsetInterestFilter(pid);
}

void
PublishingDevicePubKey::next()
{
  LOG(INFO) << "BT stage 2(PublishingDevicePubKey) starts...";
  shared_ptr<Face> face = FaceHolder::get();
  std::string name = BT_DEVICE_PREFIX + "/" + getConfig()->getId() + "/pubkey";
  LOG(INFO) << "set interest filter: " << name;
  const RegisteredPrefixId* prefixId =
    face->setInterestFilter(name,
                            bind(&PublishingDevicePubKey::onInterest, this, _1, _2),
                            RegisterPrefixSuccessCallback(),
                            BtHelper::defaultOnRegisterPrefixFailure);
  m_registered_prefix_id = const_cast<RegisteredPrefixId*>(prefixId);
}

void
PublishingDevicePubKey::onInterest(const InterestFilter& prefix, const Interest& interest)
{
  LOG(INFO) << "PublishingDevicePubKey callback";
  if (!this->isInSession()) {
    LOG(WARNING) << "PublishingDevicePubKey onInterest not in session.";
    return;
  }
  if (this->isProcessing()) {
    LOG(INFO) << "alreading processing, interest dropped";
    return;
  }
  this->flagProcessing();
  // unregisterPrefix(FaceHolder::get(), m_registered_prefix_id);
  this->onRequestDeviceKey(this->getSession(), this->getConfig(), prefix, interest);
  this->flagProcessed();
}

void
PublishingDevicePubKey::onRequestDeviceKey(BtSession* session,
                                           shared_ptr<DeviceConfig> cfg,
                                           const InterestFilter& prefix,
                                           const Interest& interest)
{
  impl::publishDeviceKey(session, cfg, prefix.getPrefix());
  // make sure data is sent.
  FaceHolder::get()->processEvents(time::milliseconds(1000));
  shared_ptr<BtState> state =
    std::dynamic_pointer_cast<BtState>(make_shared<WaitingForGwAuth>(session, cfg));
  state->setR2(session->getCurrentState()->getR2());
  session->setState(state);
  state->next();
}

} // namespace protocol
} // namespace homesec
} // namespace ndn