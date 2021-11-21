add_library(rendering SHARED
  messages.hpp
  messages.cpp
  polygon.hpp
  polygon.cpp
  rendering_server.hpp
  rendering_server.cpp
  rgba.hpp
  rgba.cpp
)

target_link_libraries(rendering)
