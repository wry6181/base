#pragma once
#include <netinet/in.h>

namespace network {

class Socket {
  int socketFD;

public:
  Socket();
  int open_socket(int type, int protocol, int layer);
  int get_socket();
};

class Address {
  struct sockaddr_in address{};
  const char *ip;

public:
  explicit Address(const char *ip);
  int connect(int type, int port, int socket);
  int close(int socket);
};

} // namespace network
