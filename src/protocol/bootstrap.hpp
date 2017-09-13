//
// Created by Lei Pi on 2/23/17.
//

#ifndef HOMESEC_BOOTSTRAP_HPP
#define HOMESEC_BOOTSTRAP_HPP

#include "bt_session.hpp"
#include "bt_state.hpp"
#include "bt_state_1.hpp"

namespace ndn {
namespace homesec {
namespace protocol {
class BtState;

class Bootstrap : public std::enable_shared_from_this<Bootstrap>
{
public:
  Bootstrap(security::Identity identity)
    : m_session(new BtSession(identity))
  {
  }

  void
  startBootstrap(const OnBootstrapSuccess& onSuc, const OnBootstrapFailed& onFailed);

  bool
  isDone()
  {
    return m_session->isDone();
  }

private:
  BtSession* m_session;
};

} // namespace protocol
} // namespace homesec
} // namespace ndn

#endif //HOMESEC_BOOTSTRAP_HPP
