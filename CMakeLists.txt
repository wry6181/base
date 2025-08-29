cmake_minimum_required(VERSION 3.15)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
  Root
  VERSION 1.0
  DESCRIPTION "root"
  LANGUAGES CXX
)

# Global settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable folders in IDEs
set_property(GLOBAL PROPERTY USE_FOLDERS ON)


add_subdirectory(server)
