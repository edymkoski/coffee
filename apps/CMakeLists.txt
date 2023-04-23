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
