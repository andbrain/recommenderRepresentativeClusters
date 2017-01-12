cmake_minimum_required(VERSION 3.5.0)
project(recommender)
include_directories(include)

#Set debug flag
set(CMAKE_BUILD_TYPE Debug)

#Can manually add the sources using the set command as follows:
set(SOURCES recommender.cpp ) 
#list(APPEND SOURCES cpp/parser.cpp cpp/util.cpp)
#list(APPEND SOURCES cpp/graph.cpp)

#datasets
#list(APPEND SOURCES cpp/datasets/ml10m100k.cpp)
#list(APPEND SOURCES cpp/datasets/ml2k.cpp)
#list(APPEND SOURCES cpp/datasets/ml100k.cpp)

#However, the file(GLOB...) allows for wildcard additions:
#file(GLOB_RECURSE SOURCES "cpp/*.cpp")

add_executable(recommender ${SOURCES})

#Set name of executable
set_target_properties(recommender PROPERTIES OUTPUT_NAME rec.out PREFIX "")

target_compile_features(recommender PRIVATE cxx_range_for)
