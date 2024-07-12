cmake_minimum_required(VERSION 3.17)

project(
    deutschlandreise
    VERSION 0.1
    LANGUAGES CXX)

add_executable (DeutschlandreisePlaner DeutschlandreisePlanerMain.cpp)

target_link_libraries(DeutschlandreisePlaner PRIVATE 
                          JourneyCalculator
                          JourneyInput
                          DeutschlandreiseData)

add_subdirectory(JourneyCalculator)
add_subdirectory(JourneyInput)
add_subdirectory(Data)
