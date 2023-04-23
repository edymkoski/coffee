/****************************************************************************
 * Coffee
 * Copyright 2023 Eric Dymkoski eric.dymkoski@gmail.com
 * This software is distributed under the MIT license (see ~/License.md)
 ****************************************************************************/

// Entity tests

#include <gtest/gtest.h>

#include <entt/entt.hpp>
// #include <entt.hpp>

namespace coffee {

namespace {
struct Position {
    float x;
    float y;
};

struct Velocity {
    float dx;
    float dy;
};

}  // namespace

// Stub test
TEST(EntityTest, BasicRegistry) {
    entt::registry registry;

    const auto entity = registry.create();
    registry.emplace<Position>(entity, 1.0f, 2.0f);
    registry.emplace<Velocity>(entity, 0.1f, 0.3f);

    // Get a view to these characteristics
    auto view = registry.view<const Position, Velocity>();

    // use a callback to access the entity
    view.each([](const auto &pos, auto &vel) {
        ASSERT_EQ(1.0f, pos.x);
        ASSERT_EQ(2.0f, pos.y);
        ASSERT_EQ(0.1f, vel.dx);
        ASSERT_EQ(0.3f, vel.dy);
    });
}
}  // namespace coffee