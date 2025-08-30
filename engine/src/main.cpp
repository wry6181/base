
#include "network.h"
#include <arpa/inet.h>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

namespace network {

Socket::Socket() = default;

int Socket::open_socket(int type, int protocol, int layer) {
  socketFD = socket(type, protocol, layer);
  if (socketFD < 0) {
    std::cerr << "Socket creation failed\n";
    return 1;
  }
  return socketFD;
}

int Socket::get_socket() { return socketFD; }

Address::Address(const char *ip) : ip(ip) {}

int Address::connect(int type, int port, int socket) {
  address.sin_family = type;
  address.sin_port = htons(port);
  if (inet_pton(AF_INET, ip, &address.sin_addr.s_addr) <= 0) {
    std::cerr << "Invalid IP address\n";
    return 1;
  }
  int connection_result = ::connect(
      socket, reinterpret_cast<struct sockaddr *>(&address), sizeof(address));
  if (connection_result == 0) {
    std::cout << "connected \n";
  } else {
    perror("connect failed");
  }
  return connection_result;
}

int Address::close(int socket) { return ::close(socket); }

} // namespace network
