/****************************************************************************
 * Coffee
 * Copyright 2023 Eric Dymkoski eric.dymkoski@gmail.com
 * This software is distributed under the MIT license (see ~/License.md)
 ****************************************************************************/

// Sprite movement system

#include "coffee/MovementSystem.h"

namespace coffee {
namespace engine {

void MovementSystem::queueMovement(entt::entity entity,
                                   const engine::MovementEvent &event) {
    // This seems heavyweight to send movements between systems with this layer
    // of indirection, especially if there are a lot of entities to update
    // FIXME: better to do synchronously and apply directly to the components?
    // This would involve creating a view on every event?
    _movementQueue.push_back(std::make_pair(entity, event));
}

void MovementSystem::update(entt::registry &registry, uint64_t dt) {
    // View into components
    auto view = registry.view<Position, Direction, Speed>();

    // Handle received MovementEvents
    for (auto &[entity, event] : _movementQueue) {
        auto &dir = view.get<Direction>(entity);
        auto &speed = view.get<Speed>(entity);

        speed.moving = event.moving;

        // Only conditionally update the direction
        if (event.updateDir) {
            dir.value = event.dir.value;  // Assign the direction
        }
        // speed.moving = 1;  // Assign movement
    }
    _movementQueue.clear();  // Clear the queue, all events handled

    // Update position from movement
    uint32_t dt32 = static_cast<uint32_t>(dt);
    for (auto entity : view) {
        // Turns are performed instantaneously, so they are updated by incoming
        // events
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

        // FIXME: should be only update on a change
        // FIXME: clearing the moving flag by default means that this flag is
        // not available to any other System
        // speed.moving = 0;  // Assign movement
    }
}

void MovementSystem::render(entt::registry &) const {
    // no op
}

}  // namespace engine
}  // namespace coffee
