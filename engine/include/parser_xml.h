#pragma once

#include "pch.h"

namespace parser {

class openscenario_xml {
  struct M {
    std::map<std::string, std::string> FileHeader;
    std::map<std::string, std::string> ParameterDeclarations;

  } m;
  explicit openscenario_xml(M m) : m(std::move(m)) {};

public:
  ~openscenario_xml() = default;
  static openscenario_xml create(const std::string &path_to_xml) {
    std::cout << "parser\n";

    std::map<std::string, std::string> temp{{"test", "alma"}};
    std::map<std::string, std::string> temp2{{"test", "alma"}};

    return openscenario_xml(M{.FileHeader = std::move(temp),
                              .ParameterDeclarations = std::move(temp2)});
  }
};
} // namespace parser
