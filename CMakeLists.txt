cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall ${CMAKE_CXX_FLAGS} -g")
add_executable(assignment5-3 Visitor.cpp Object.cpp driverUgrad.cpp Universe.cpp AggregateStrategy.cpp)