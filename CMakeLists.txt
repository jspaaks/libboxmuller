cmake_minimum_required(VERSION 3.23...3.28)

project(project_boxmuller LANGUAGES C)
include(CTest)  # defines BUILD_TESTING

set(PROJECT_ROOT ${CMAKE_CURRENT_LIST_DIR})

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set_property(CACHE CMAKE_INSTALL_PREFIX PROPERTY VALUE "${CMAKE_BINARY_DIR}/dist")
endif()

add_subdirectory(${PROJECT_ROOT}/man/boxmuller)
add_subdirectory(${PROJECT_ROOT}/src/boxmuller)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    # I'm the top-most project
    option(BOXMULLER_BUILD_TESTING "Whether to build the libboxmuller tests" ${BUILD_TESTING})
    option(BOXMULLER_BUILD_EXAMPLES "Whether to build the libboxmuller examples" ON)
    if ((BUILD_TESTING AND NOT BOXMULLER_BUILD_TESTING) OR
         NOT BUILD_TESTING AND BOXMULLER_BUILD_TESTING)
        message(WARNING, " will use more specific BOXMULLER_BUILD_TESTING=${BOXMULLER_BUILD_TESTING} over BUILD_TESTING=${BUILD_TESTING}")
    endif()
else()
    # I'm not the top-most project, use BOXMULLER_BUILD_TESTING and BOXMULLER_BUILD_EXAMPLES as-is
    option(BOXMULLER_BUILD_TESTING "Whether to build the libboxmuller tests" OFF)
    option(BOXMULLER_BUILD_EXAMPLES "Whether to build the libboxmuller examples" OFF)
endif()
if (BOXMULLER_BUILD_TESTING)
    add_subdirectory(${PROJECT_ROOT}/test/boxmuller)
endif()
if (BOXMULLER_BUILD_EXAMPLES)
    add_subdirectory(${PROJECT_ROOT}/src/example)
endif()
