CMAKE_MINIMUM_REQUIRED(VERSION 3.31)
PROJECT(aura)

ADD_EXECUTABLE(Example examples/example.c
                       src/window/aura_window.c
                       include/glad/glad.c)

TARGET_INCLUDE_DIRECTORIES(Example PRIVATE include)
TARGET_LINK_DIRECTORIES(Example PRIVATE lib)
TARGET_LINK_LIBRARIES(Example PRIVATE glfw3.lib)
