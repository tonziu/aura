CMAKE_MINIMUM_REQUIRED(VERSION 3.31)
PROJECT(aura)

include_directories(vendor)
include_directories(include)
link_directories(lib)

set(AURA_SRC_FILES src/core/context.c
                   src/core/mesh.c
                   src/core/material.c
                   src/utils/utils.c
                   src/graphics/renderable.c
                   src/graphics/renderer.c
                   vendor/glad/glad.c)

set(AURA_LIBS glfw3.lib)

add_executable(Window examples/window.c ${AURA_SRC_FILES})
add_executable(Rectangle examples/rectangle.c ${AURA_SRC_FILES})

target_link_libraries(Window PRIVATE ${AURA_LIBS})
target_link_libraries(Rectangle PRIVATE ${AURA_LIBS})

