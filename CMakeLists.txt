CMAKE_MINIMUM_REQUIRED(VERSION 3.9)
set(CMAKE_CXX_STANDARD 14)

PROJECT(muon_propagator_test)

find_package(PROPOSAL REQUIRED)

add_executable(muon_propagator ${PROJECT_SOURCE_DIR}/muon_propagator.cpp)
target_link_libraries(muon_propagator PROPOSAL::PROPOSAL)
