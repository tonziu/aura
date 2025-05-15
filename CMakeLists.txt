CMAKE_MINIMUM_REQUIRED(VERSION 3.31)
PROJECT(aura)

include_directories(vendor)
include_directories(include)
link_directories(lib)

set(AURA_SRC_FILES src/window/aura_window.c
                   src/material/aura_shader.c
                   src/font/aura_font.c
                   vendor/glad/glad.c)

set(AURA_LIBS glfw3.lib freetype.lib)

ADD_EXECUTABLE(Window examples/window.c ${AURA_SRC_FILES})

ADD_EXECUTABLE(Shader examples/shader.c ${AURA_SRC_FILES})

ADD_EXECUTABLE(Text  examples/text.c ${AURA_SRC_FILES})

TARGET_LINK_LIBRARIES(Window PRIVATE ${AURA_LIBS})

TARGET_LINK_LIBRARIES(Shader PRIVATE ${AURA_LIBS})

TARGET_LINK_LIBRARIES(Text PRIVATE ${AURA_LIBS})
