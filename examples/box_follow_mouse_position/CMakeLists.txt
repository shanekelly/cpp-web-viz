# Create the box_follow_mouse_position executable.
add_executable(box_follow_mouse_position box_follow_mouse_position.cpp)

# Link the necessary libraries to the box_follow_mouse_position executable.
target_link_libraries(box_follow_mouse_position
  rendering
  common
)
