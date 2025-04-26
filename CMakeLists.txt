cmake_minimum_required(VERSION 3.28)
project(Leonardo_transazioni_finanziarie)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(test)

set(SOURCE_FILES
        Transaction.h
        Transaction.cpp
        Account.h
        Account.cpp
)

add_executable(${CMAKE_PROJECT_NAME} main.cpp)
add_library(${CMAKE_PROJECT_NAME}_lib ${SOURCE_FILES})
target_link_libraries(${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_NAME}_lib)