#include "arpa/inet.h"
#include "netinet/in.h"
#include "pch.h"
#include "sys/socket.h"
#include "unistd.h"
namespace proxy {
namespace network {
class Socket {
  int socketFD;

public:
  Socket() = default;
  int open_socket(int type, int protocol, int layer) {
    socketFD = socket(type, protocol, layer);
    if (socketFD < 0) {
      std::cerr << "Socket creation failed\n";
      return 1;
    }
    return 0;
  }
  int get_socket() { return socketFD; }
};
class Address {
  struct sockaddr_in address{};
  const char *ip;
  int connection_result;

public:
  Address(const char *ip) : ip(ip) {}

  int connect(int type, int port, int socket) {
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
  int close(int socket) { return ::close(socket); }
};
} // namespace network
class NetworkProxy {
  virtual ~NetworkProxy() {}

public:
  int connect() {}
};
} // namespace proxy
