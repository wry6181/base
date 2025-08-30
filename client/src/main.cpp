#include "network.h"
#include "pch.h"

int main() {
  proxy::network::Socket s{};
  s.open_socket(AF_INET, SOCK_STREAM, 0);
  proxy::network::Address a("142.250.201.196");
  a.connect(AF_INET, 80, s.get_socket());
  a.close(s.get_socket());

  return 0;
}
