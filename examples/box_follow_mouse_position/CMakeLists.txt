# Create the main executable.
add_executable(main main.cpp)

# Link the necessary libraries to the main executable.
target_link_libraries(main
  rendering
  common
)
