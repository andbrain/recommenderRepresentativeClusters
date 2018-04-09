cmake_minimum_required(VERSION 3.5.0)
project(recommender)
include_directories(include)

#Set debug flag
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

#Can manually add the sources using the set command as follows:
set(SOURCES recommender.cpp ) 
list(APPEND SOURCES cpp/graph.cpp)
list(APPEND SOURCES cpp/parser.cpp)
list(APPEND SOURCES cpp/util.cpp)
list(APPEND SOURCES cpp/representative.cpp)
list(APPEND SOURCES cpp/syncer.cpp)
list(APPEND SOURCES cpp/estimator.cpp)

add_executable(recommender ${SOURCES})

#Set name of executable
set_target_properties(recommender PROPERTIES OUTPUT_NAME rec.out PREFIX "")

target_compile_features(recommender PRIVATE cxx_range_for)
