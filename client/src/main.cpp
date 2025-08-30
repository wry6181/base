#include "networkProxy.h"
#include "pch.h"

int main() {
  proxy::NetworkProxy np("142.250.201.196");
  np.init_proxy(AF_INET, SOCK_STREAM, 0);
  np.connect(AF_INET, 80);

  return 0;
}
