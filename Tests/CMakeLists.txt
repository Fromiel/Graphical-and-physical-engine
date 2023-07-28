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

	set_property(TARGET ${fileName} PROPERTY CXX_STANDARD 20)

	gtest_discover_tests(${fileName})

endforeach()