#ifndef BT_COMMON
#define BT_COMMON

#include <string>

#include <ndn-cxx/face.hpp>
#include <ndn-cxx/util/string-helper.hpp>

#include "../DeviceConfigs.hpp"
#include "../FaceHolder.hpp"
#include "../constants.h"
#include "../easylogging/easylogging++.h"
#include "../keyring.hpp"
#include "../util/security_helpers.hpp"
#include "../util/string_helpers.hpp"

#include "device_config.hpp"

class BootstrapError : std::runtime_error
{
public:
  BootstrapError(const std::string& msg)
    : runtime_error(msg)
  {
  }
};

#endif /* BT_COMMON */