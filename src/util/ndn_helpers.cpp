#include "ndn_helpers.hpp"

#include "../easylogging/easylogging++.h"

#include <chrono>
#include <thread>

namespace ndn {
namespace homesec {

void
onTimeout(shared_ptr<Face> f,
          std::shared_ptr<int> retryCount,
          DataCallback onData,
          NackCallback onNack,
          const Interest& interest)
{
  if ((*retryCount)-- > 0) {
    const int delay = 500;
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    TimeoutCallback retry = std::bind(&onTimeout, f, retryCount, onData, onNack, _1);
    f->expressInterest(interest, onData, onNack, retry);
  }
  else {
    lp::Nack n;
    onNack(interest, n);
  }
}

void
expressInterest(shared_ptr<Face> f,
                Interest interest,
                const int retry,
                DataCallback onData,
                NackCallback onNack)
{
  shared_ptr<int> retryCount = make_shared<int>(retry);
  TimeoutCallback onTimeoutRetry = std::bind(&onTimeout, f, retryCount, onData, onNack, _1);
  LOG(INFO) << "Express: " << interest.toUri();
  f->expressInterest(interest, onData, onNack, onTimeoutRetry);
}

} // namespace homesec
} // namespace ndn