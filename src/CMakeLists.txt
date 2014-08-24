project(libcarp_project)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g3 -std=c99 -Wall -Werror -Wno-unused-variable -Wno-format-security")
file(GLOB carp_src "*.c" "lib/*.c")
list(REMOVE_ITEM carp_src ${CMAKE_CURRENT_SOURCE_DIR}/carp.c) # very likely that carp.c will be moved to somewhere else.
add_library(carp STATIC ${carp_src})
add_executable(carp_cmd carp.c)
target_link_libraries(carp_cmd carp)

# Install bin and lib
install(TARGETS carp carp_cmd
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

# Install header files.
file(GLOB headers ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
install(FILES ${headers} DESTINATION include)
