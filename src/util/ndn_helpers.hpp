#ifndef NDN_HELPERS_HPP
#define NDN_HELPERS_HPP

#include <ndn-cxx/face.hpp>

namespace ndn {
namespace homesec {

extern void
expressInterest(shared_ptr<Face> f,
                Interest interest,
                const int retry,
                DataCallback onData,
                NackCallback onNack);
}
} // namespace ndn


#endif /* NDN_HELPERS_HPP */
