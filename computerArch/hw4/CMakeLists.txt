cmake_minimum_required(VERSION 3.0.0)
project(HW4 VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(HW4 core_api.c main.c sim_api.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
