CMAKE_MINIMUM_REQUIRED(VERSION 3.9)
set(CMAKE_CXX_STANDARD 14)

PROJECT(muon_propagator_test)

find_package(PROPOSAL REQUIRED)

add_executable(muon_propagator ${PROJECT_SOURCE_DIR}/muon_propagator.cpp)
add_executable(antimuon_propagator ${PROJECT_SOURCE_DIR}/antimuon_propagator.cpp)
add_executable(muon_propagator_example ${PROJECT_SOURCE_DIR}/muon_propagator_simpleexample.cpp)

target_link_libraries(muon_propagator PROPOSAL::PROPOSAL)
target_link_libraries(antimuon_propagator PROPOSAL::PROPOSAL)
target_link_libraries(muon_propagator_example PROPOSAL::PROPOSAL)
