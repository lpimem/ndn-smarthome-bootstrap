//
//  main.cpp
//  homesec2
//
//  Created by Lei Pi on 1/26/17.
//  Copyright © 2017 Lei Pi. All rights reserved.
//

#include "FaceHolder.hpp"
#include "device.hpp"

INITIALIZE_EASYLOGGINGPP

int
main()
{
  LOG(INFO) << "device start ...";
  ndn::homesec::Device gw(ndn::homesec::DeviceConfigs::getInstance().getDeviceId(),
                          ndn::homesec::DeviceConfigs::getInstance().getPin());
  const int maxRetry = 10;
  int ret = 1;
  int retry = 0;
  while (retry++ < maxRetry) {
    try {
      gw.run();
      ndn::homesec::FaceHolder::get()->processEvents();
      break;
    }
    catch (std::string& s) {
      LOG(INFO) << "ignored error: " << s;
      if (retry < maxRetry){
        LOG(INFO) << "restart bootstrapping in 10 seconds ...";
        std::this_thread::sleep_for(std::chrono::milliseconds(10000));
      }
      continue;
    }
  }
  if (ret == 0) {
    ndn::homesec::FaceHolder::get()->processEvents();
  }
  LOG(INFO) << "Exit " << ret;
  return ret;
}
