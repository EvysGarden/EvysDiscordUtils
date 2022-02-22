cmake_minimum_required(VERSION 3.20)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")

project(EvysDiscordUtils VERSION 0.0.1)

set(DCMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_COLOR_MAKEFILE on)

find_package(fmt CONFIG REQUIRED)
find_package(cpr CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(argh CONFIG REQUIRED)

add_executable(messageToJson
    ${CMAKE_CURRENT_SOURCE_DIR}/src/messageToJson.cpp
)

target_link_libraries(messageToJson PRIVATE fmt::fmt)
target_link_libraries(messageToJson PRIVATE cpr::cpr)
target_link_libraries(messageToJson PRIVATE nlohmann_json nlohmann_json::nlohmann_json)
target_link_libraries(messageToJson PRIVATE argh)