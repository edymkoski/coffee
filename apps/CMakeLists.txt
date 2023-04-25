cmake_minimum_required(VERSION 3.20)
project(coffee-game LANGUAGES CXX)

add_executable(coffee-game main.cpp)

# CLI11
# find_package( Cli11 REQUIRED )
target_link_libraries(coffee-game
    # Cli11
    SDL2
    coffee
)


add_custom_target(copy-assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/resources ${CMAKE_CURRENT_BINARY_DIR}/resources
)
add_dependencies(coffee-game copy-assets)
