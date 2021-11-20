add_library(world SHARED
  obstacle.hpp
  path.hpp
)

# Set the linker language since the linker cannot determine the language automatically for a
# header-only library. If a definition file is added, then this is no longer necessary and should be
# removed.
set_target_properties(world PROPERTIES LINKER_LANGUAGE CXX)
