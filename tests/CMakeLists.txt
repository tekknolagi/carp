enable_testing()
find_package(Check REQUIRED)
include_directories(${CHECK_INCLUDE_DIRS})
set(LIBS ${LIBS} ${CHECK_LIBRARIES} pthread carp)
include_directories(. ../src)  # For header inclusion
add_executable(test_instr test_instr.c)
target_link_libraries(test_instr ${LIBS})
add_test(test_instr ${CMAKE_CURRENT_BINARY_DIR}/test_instr)