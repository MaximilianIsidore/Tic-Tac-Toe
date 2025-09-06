cmake_minimum_required(VERSION 3.16)
project(Tic-Tac-Toe)

# Set c++ standard
set(CMAKE_CXX_STANDARD 23)

set(SFML_DIR "${CMAKE_SOURCE_DIR}/SFML-3.0.0/lib/cmake/SFML")

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System Audio)

add_executable(Tic-Tac-Toe main.cpp)

set_target_properties(Tic-Tac-Toe PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)

target_sources(${PROJECT_NAME}
        PUBLIC
        FILE_SET CXX_MODULES FILES
        board.ixx
        board_entity.ixx
        game.ixx
        game_state.ixx
        mouse.ixx
        UI.ixx
        sound.ixx
        AI.ixx
)

target_link_libraries(Tic-Tac-Toe PRIVATE SFML::Graphics SFML::Window SFML::System SFML::Audio)