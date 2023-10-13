cmake_minimum_required(VERSION 3.5)
project(orderbook-sim)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})
include_directories(include)

file(GLOB SOURCE_FILES
    src/*.cpp 
)

include(CTest)
enable_testing()

add_executable(orderbook-sim main.cpp ${SOURCE_FILES})
target_link_libraries(orderbook-sim ${CURL_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
