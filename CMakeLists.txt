CMAKE_MINIMUM_REQUIRED(VERSION 3.31)
PROJECT(aura)

include_directories(vendor)
include_directories(include)
link_directories(lib)

set(AURA_SRC_FILES src/core/context.c
                   vendor/glad/glad.c)

set(AURA_LIBS glfw3.lib)

add_executable(Window examples/window.c ${AURA_SRC_FILES})

target_link_libraries(Window PRIVATE ${AURA_LIBS})

