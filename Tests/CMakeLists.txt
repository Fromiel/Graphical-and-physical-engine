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


file(GLOB testsFiles "./Tests*.cpp")

include(GoogleTest)

foreach(file ${testsFiles})

	string(REGEX MATCH "[A-Za-z0-9]+\.cpp" fileName ${file})

	add_executable( ${fileName} ${file} )

	target_link_libraries(${fileName} PRIVATE Engine GTest::gtest_main)

	include_directories(. glm)

	#target_link_libraries(${fileName} ${CMAKE_CURRENT_SOURCE_DIR}/DEPENDENCIES/lib-vc2022/glfw3.lib)
	#target_link_libraries(${fileName} GLAD)
	#set_target_properties(GLFW PROPERTIES LINKER_LANGUAGE CXX)
	#set_target_properties(GLAD PROPERTIES LINKER_LANGUAGE CXX)

	set_property(TARGET ${fileName} PROPERTY CXX_STANDARD 20)

	gtest_discover_tests(${fileName})

endforeach()