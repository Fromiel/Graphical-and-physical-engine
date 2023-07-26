
include_directories(../include)
add_library(GLFW STATIC glfw3.lib)
file(GLOB SRC_FILES *.c)
add_library(GLAD STATIC ${SRC_FILES})