# Create the disk_arrow_key_movement executable.
add_executable(disk_arrow_key_movement disk_arrow_key_movement.cpp)

# Link the necessary libraries to the disk_arrow_key_movement executable.
target_link_libraries(disk_arrow_key_movement
  rendering
  common
)
