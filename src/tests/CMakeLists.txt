# Define the list of tests in this directory.
set(TESTS )

# Create a test executable for each test in this directory.
foreach (CUR_TEST ${TESTS})
    add_executable(${CUR_TEST} ${CUR_TEST}.cpp)
    target_link_libraries(${CUR_TEST} gtest )
    add_test(${CUR_TEST} ${CUR_TEST})
endforeach (CUR_TEST)
