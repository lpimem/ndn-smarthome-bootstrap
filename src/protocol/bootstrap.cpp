//
// Created by Lei Pi on 2/23/17.
//
#include "bootstrap.hpp"

namespace ndn {
namespace homesec {
namespace protocol {

void
Bootstrap::startBootstrap(const OnBootstrapSuccess& onSuc, const OnBootstrapFailed& onFailed)
{
  LOG(INFO) << "start bootstrapping...";
  // register handlers
  m_session->setOnSuccessHandler(onSuc);
  m_session->setOnFailHandler(onFailed);
  // init configuration
  DeviceConfigs cfgs = DeviceConfigs::getInstance();
  auto config = make_shared<DeviceConfig>(cfgs.getDeviceId(), cfgs.getPin());
  security::Key deviceKey = m_session->getDevId().getDefaultKey();
  const Buffer pubkeyBuf = deviceKey.getPublicKey();
  config->setDevicePubKey(pubkeyBuf);
  // start bt session
  shared_ptr<BtState> initState =
    std::dynamic_pointer_cast<BtState>(make_shared<WaitingForGwPubKey>(m_session, config));
  m_session->setState(initState);
  initState->next();
}

} // namespace protocol
} // namespace homesec
} // namespace ndn
