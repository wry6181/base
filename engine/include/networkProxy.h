#pragma once
#include "network.h"
#include <iostream>

namespace proxy {

class NetworkProxy {
  network::Address addr;
  network::Socket soc{};
  int init = 0;

public:
  explicit NetworkProxy(const char *ip) : addr(ip) {}
  virtual ~NetworkProxy() { addr.close(init); }

  int init_proxy(int type, int protocol, int layer) {
    init = soc.open_socket(type, protocol, layer);
    std::cout << init << " : socket\n";
    return init;
  }

  int connect(int type, int port) { return addr.connect(type, port, init); }
};

} // namespace proxy
