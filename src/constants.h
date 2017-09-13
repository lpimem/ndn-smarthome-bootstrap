//
// Created by Lei Pi on 1/23/17.
//

#ifndef HOMESEC_CONSTANTS_H
#define HOMESEC_CONSTANTS_H

#include <string>

namespace ndn {
namespace homesec {
const std::string HOME_PREFIX            = "/local-home";
const std::string BT_PREFIX              = HOME_PREFIX + "/bootstrap";
const std::string BT_DEVICE_PREFIX       = BT_PREFIX + "/device";
const std::string BT_OWNER_PREFIX        = BT_PREFIX + "/owner"; 
const std::string BT_NAME_OWNER_PUBKEY   = BT_OWNER_PREFIX + "/pubkey";
const std::string GATEWAY_PREFIX         = HOME_PREFIX + "/gateway";
const std::string OWNER_PREFIX           = HOME_PREFIX + "/owner";
const std::string LOCATION_PREFIX        = HOME_PREFIX + "/location/";
const int         INTEREST_FRESH_SECONDS = 10;
const int         DEFAULT_RETRY_TIMES    = 5;
const int         DEFAULT_RETRY_INTERVAL = 1000;
const long        MAX_WAITING            = 60000; //ms

} // namespace ndn
} // namespace homesec


#endif //HOMESEC_CONSTANTS_H