CMAKE_MINIMUM_REQUIRED(VERSION 3.31)
PROJECT(aura)

ADD_EXECUTABLE(Window examples/window.c
                       src/window/aura_window.c
                       include/glad/glad.c)

ADD_EXECUTABLE(Shader  examples/shader.c
                       src/window/aura_window.c
                       src/renderer/aura_shader.c
                       include/glad/glad.c)

TARGET_INCLUDE_DIRECTORIES(Window PRIVATE include)
TARGET_LINK_DIRECTORIES(Window PRIVATE lib)
TARGET_LINK_LIBRARIES(Window PRIVATE glfw3.lib)

TARGET_INCLUDE_DIRECTORIES(Shader PRIVATE include)
TARGET_LINK_DIRECTORIES(Shader PRIVATE lib)
TARGET_LINK_LIBRARIES(Shader PRIVATE glfw3.lib)
