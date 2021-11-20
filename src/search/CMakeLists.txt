add_library(search SHARED
  searcher.hpp
)

target_link_libraries(search
  common
  world
)

# Set the linker language since the linker cannot determine the language automatically for a
# header-only library. If a definition file is added, then this is no longer necessary and should be
# removed.
set_target_properties(search PROPERTIES LINKER_LANGUAGE CXX)
