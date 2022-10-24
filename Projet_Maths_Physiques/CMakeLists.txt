# CMakeList.txt : projet CMake pour test, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)
project ("Projet_Maths_Physique")
include(GNUInstallDirs)

add_subdirectory(Dependencies/lib-vc2022)
file(GLOB SOURCES src/*.cpp)
# Ajoutez une source à l'exécutable de ce projet.
add_executable(Projet_Maths_Physique Game/main.cpp ${SOURCES}  "includes/test.h" "includes/Vertice.h")

include_directories(Dependencies/include includes)
link_directories(Dependencies/lib-vc2022)

target_link_libraries(Projet_Maths_Physique ${Projet_Maths_Physique_SOURCE_DIR}/DEPENDENCIES/lib-vc2022/glfw3.lib)
target_link_libraries(Projet_Maths_Physique GLAD)
set_target_properties(GLFW PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(GLAD PROPERTIES LINKER_LANGUAGE CXX)

find_package(OpenGL REQUIRED)
target_link_libraries(Projet_Maths_Physique OpenGL::GL)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Projet_Maths_Physique PROPERTY CXX_STANDARD 20)
endif()


# Install gtest

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#Tests

enable_testing()


file(GLOB testsFiles "Tests/Tests*.cpp")

include(GoogleTest)

foreach(file ${testsFiles})

	string(REGEX MATCH "[A-Za-z0-9]+\.cpp" fileName ${file})
  
	add_executable(
		${fileName}
		${file} ${SOURCES}
	)

	target_link_libraries(
	  ${fileName}
	  GTest::gtest_main
	)

	include_directories(Tests/ glm)

	target_link_libraries(${fileName} ${Projet_Maths_Physique_SOURCE_DIR}/DEPENDENCIES/lib-vc2022/glfw3.lib)
	target_link_libraries(${fileName} GLAD)
	set_target_properties(GLFW PROPERTIES LINKER_LANGUAGE CXX)
	set_target_properties(GLAD PROPERTIES LINKER_LANGUAGE CXX)

	set_property(TARGET ${fileName} PROPERTY CXX_STANDARD 20)

	gtest_discover_tests(${fileName})

endforeach()

