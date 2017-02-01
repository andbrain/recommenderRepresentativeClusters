cmake_minimum_required(VERSION 3.5.0)
project(clustering)
include_directories(include)

#Set debug flag
set(CMAKE_BUILD_TYPE Debug)

#Can manually add the sources using the set command as follows:
set(SOURCES clustering.cpp ) 
list(APPEND SOURCES cpp/parser.cpp cpp/util.cpp)
list(APPEND SOURCES cpp/graph.cpp)
list(APPEND SOURCES cpp/hash.cpp)
list(APPEND SOURCES cpp/ap.cpp)
list(APPEND SOURCES cpp/dataset_base.cpp)
list(APPEND SOURCES cpp/similarity_base.cpp)

#datasets
#list(APPEND SOURCES cpp/datasets/ml10m100k.cpp)
list(APPEND SOURCES cpp/datasets/ml2k.cpp)
list(APPEND SOURCES cpp/datasets/ml100k.cpp)

#similarities
list(APPEND SOURCES cpp/similarities/average.cpp)
list(APPEND SOURCES cpp/similarities/cosine.cpp)
list(APPEND SOURCES cpp/similarities/correlation.cpp)
list(APPEND SOURCES cpp/similarities/euclidean.cpp)
list(APPEND SOURCES cpp/similarities/loglikelihood.cpp)

#However, the file(GLOB...) allows for wildcard additions:
#file(GLOB_RECURSE SOURCES "cpp/*.cpp")

add_executable(clustering ${SOURCES})

#Set name of executable
set_target_properties(clustering PROPERTIES OUTPUT_NAME ap.out PREFIX "")

target_compile_features(clustering PRIVATE cxx_range_for)
