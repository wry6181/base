add_executable(client
  src/main.cpp
)

target_link_libraries(client PRIVATE
  engine
)

install(TARGETS client DESTINATION bin)
