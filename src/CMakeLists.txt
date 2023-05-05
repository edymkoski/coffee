set(coffee_SRC
    AnimationState.cpp
    AnimationSystem.cpp
    Assets.cpp
    MovementSystem.cpp
    TargetSystem.cpp
    Scene.cpp
    coffee.cpp
    CoffeeGame.cpp
    PlayerSystem.cpp
    NpcSystem.cpp
    InputHandler.cpp
)

add_library(coffee STATIC ${coffee_SRC})

target_include_directories(coffee PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(coffee
    fmt
    spdlog
    SDL2
    SDL2_ttf
    SDL2_image
    EnTT::EnTT
    Eigen3::Eigen
)
