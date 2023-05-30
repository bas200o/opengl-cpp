# Projects Settings
cmake_minimum_required (VERSION 3.1)
project (opengl-bas)
include(CTest)


FILE(GLOB Sources 
    "src/*.cpp" 
    "src/*.hpp"
    "src/*.h"
    "test/*.cpp"
    )

# The main executable
add_executable(opengl-bas ${Sources})

set_property(TARGET opengl-bas PROPERTY CXX_STANDARD 17)
target_compile_options(opengl-bas PRIVATE -Wall)

add_definitions(-DGLEW_STATIC)
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
add_subdirectory(lib/glew EXCLUDE_FROM_ALL)
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)

enable_testing()

target_link_libraries(opengl-bas
  PRIVATE glfw
  PRIVATE libglew_static
  PRIVATE glm
)

add_test(NAME test1 COMMAND opengl-bas test)