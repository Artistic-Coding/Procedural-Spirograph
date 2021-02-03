cmake_minimum_required (VERSION 3.5)

project(procedural_spirograph)

# Optional definitions
#set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++fs -std=c++14 -O3")

# The pack for your cinder installation
get_filename_component( CINDER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../libs/Cinder" ABSOLUTE )

include( "${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake" )

ci_make_app(
        APP_NAME    ${PROJECT_NAME}
        CINDER_PATH ${CINDER_PATH}
        SOURCES     ${CMAKE_CURRENT_SOURCE_DIR}/src/Pendulum.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
        INCLUDES    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

#include_directories(include)
#file(GLOB SOURCES "src/*.cpp")

#add_executable(${PROJECT_NAME} ${SOURCES})