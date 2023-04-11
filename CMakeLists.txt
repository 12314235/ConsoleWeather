cmake_minimum_required(VERSION 3.24)
project(labwork10)

set(CMAKE_CXX_STANDARD 20)

add_executable(labwork10 main.cpp visualisation/visualisation.cpp visualisation/visualisation.h wether/Weather_Information.cpp wether/Weather_Information.h)

add_subdirectory(visualisation)


if (WIN32)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

include(FetchContent)

FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 742fb6f1a5ed40efe8f3a994e0559c6aff52f2d7)

FetchContent_Declare(nlohmann_json GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG 6af826d0bdb55e4b69e3ad817576745335f243ca)

FetchContent_Declare(ftxui GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
        GIT_TAG 898b8d672ef2cea386048b79276db26867997bae)

FetchContent_MakeAvailable(cpr)
FetchContent_MakeAvailable(nlohmann_json)
FetchContent_MakeAvailable(ftxui)

target_link_libraries(${PROJECT_NAME} PRIVATE cpr::cpr)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME} PRIVATE ftxui::dom ftxui::component ftxui::screen)


