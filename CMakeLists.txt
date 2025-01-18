cmake_minimum_required(VERSION 3.23...3.28)

project(project_boxmuller LANGUAGES C)
include(CTest)

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
    option(BUILD_TESTING_BOXMULLER "Whether to build the libboxmuller tests" ${BUILD_TESTING})
    if (BUILD_TESTING AND BUILD_TESTING_BOXMULLER)
        set(BUILD_TESTING_BOXMULLER, "ON")
    elseif (BUILD_TESTING AND NOT BUILD_TESTING_BOXMULLER)
        message(WARNING, " will use more specific BUILD_TESTING_BOXMULLER=\"${BUILD_TESTING_BOXMULLER}\" over BUILD_TESTING=\"${BUILD_TESTING}\"")
        set(BUILD_TESTING_BOXMULLER, "OFF")
    elseif (NOT BUILD_TESTING AND BUILD_TESTING_BOXMULLER)
        message(WARNING, " will use more specific BUILD_TESTING_BOXMULLER=\"${BUILD_TESTING_BOXMULLER}\" over BUILD_TESTING=\"${BUILD_TESTING}\"")
        set(BUILD_TESTING_BOXMULLER, "ON")
    elseif (NOT BUILD_TESTING AND NOT BUILD_TESTING_BOXMULLER)
        set(BUILD_TESTING_BOXMULLER, "OFF")
    endif()
    option(BUILD_EXAMPLES_BOXMULLER "Whether to build the libboxmuller examples" "ON")
else()
    # I'm not the top-most project, use BUILD_TESTING_BOXMULLER as-is
    option(BUILD_TESTING_BOXMULLER "Whether to build the libboxmuller tests" "OFF")
    option(BUILD_EXAMPLES_BOXMULLER "Whether to build the libboxmuller examples" "OFF")
endif()
if (BUILD_TESTING_BOXMULLER)
    add_subdirectory(${PROJECT_ROOT}/test/boxmuller)
endif()
if (BUILD_EXAMPLES_BOXMULLER)
    add_subdirectory(${PROJECT_ROOT}/src/example)
endif()
