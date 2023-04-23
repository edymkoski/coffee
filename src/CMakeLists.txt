set(coffee_SRC
    Level.cpp
)

add_library(coffee STATIC ${coffee_SRC})

target_include_directories(coffee PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(coffee
    fmt
    spdlog
    Eigen3::Eigen
)
