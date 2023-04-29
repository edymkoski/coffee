/****************************************************************************
 * Coffee
 * Copyright 2023 Eric Dymkoski eric.dymkoski@gmail.com
 * This software is distributed under the MIT license (see ~/License.md)
 ****************************************************************************/

// Sprite movement system

#include "coffee/MovementSystem.h"

namespace coffee {
namespace engine {

void MovementSystem::update(entt::registry &registry, uint64_t dt) {
    // View into components
    auto view = registry.view<Position, const Direction, const Speed>();

    // Update position from movement
    uint32_t dt32 = static_cast<uint32_t>(dt);
    for (auto entity : view) {
        // Turns are performed instantaneously
        // @todo add a target and current direction to allow for inertia in
        // turning
        auto &pos = view.get<Position>(entity);
        auto &dir = view.get<const Direction>(entity);
        auto &speed = view.get<const Speed>(entity);

        // Normalize the direction, so that the speed is fully set by
        // "speed" Update location
        Vec2f velocity = (1.0f / 1000.0f) * speed.value * float(speed.moving) *
                         dir.value.normalized();
        Vec2f update = velocity.array() * float(dt32);
        pos.value += update.template cast<int32_t>();
    }
}

void MovementSystem::render(entt::registry &) const {
    // no op
}

}  // namespace engine
}  // namespace coffee
