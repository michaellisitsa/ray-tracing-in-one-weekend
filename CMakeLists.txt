cmake_minimum_required(VERSION 3.5.1)
project(RayTracing VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(main src/main.cpp)

# Use the Catch Library?
add_executable(main_test src/tests/main_test.cpp test/tests-main.cpp)
add_executable(vec3_test src/tests/vec3_test.cpp test/tests-main.cpp)

add_custom_target(test_main ALL DEPENDS ${CMAKE_BINARY_DIR}/main_test COMMAND ${CMAKE_BINARY_DIR}/main_test)
add_custom_target(test_vec3 ALL DEPENDS ${CMAKE_BINARY_DIR}/vec3_test COMMAND ${CMAKE_BINARY_DIR}/vec3_test)