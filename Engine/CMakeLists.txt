project ("Engine")

file(GLOB_RECURSE SOURCES src/*.cpp)

# Créer une bibliothèque pour "Engine"
add_library(Engine STATIC ${SOURCES})

# Ajouter des options de compilation spécifiques pour "Engine" si nécessaire
target_compile_options(Engine PUBLIC -Wall)

target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)
target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/include)

include(GNUInstallDirs)

add_subdirectory(Dependencies/lib-vc2022)

include_directories(Dependencies/include includes)
link_directories(Dependencies/lib-vc2022)

target_link_libraries(Engine ${CMAKE_CURRENT_SOURCE_DIR}/DEPENDENCIES/lib-vc2022/glfw3.lib)
target_link_libraries(Engine GLAD)
set_target_properties(GLFW PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(GLAD PROPERTIES LINKER_LANGUAGE CXX)

find_package(OpenGL REQUIRED)
target_link_libraries(Engine OpenGL::GL)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Engine PROPERTY CXX_STANDARD 20)
endif()

