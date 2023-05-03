/****************************************************************************
 * Coffee
 * Copyright 2023 Eric Dymkoski eric.dymkoski@gmail.com
 * This software is distributed under the MIT license (see ~/License.md)
 ****************************************************************************/

// Collects user inputs, generating game events

#include "coffee/NpcSystem.h"

#include "SDL2/SDL.h"
#include "coffee/InputHandler.h"
#include "coffee/MovementSystem.h"

namespace coffee {
namespace engine {

// Update componenets affected by this system
void NpcSystem::update(entt::registry &registry, uint64_t /*dt*/) {
    // FIXME: much of this code is going to be similar for the AI and the Player
    // systems, will need to figure out how to consolidate?

    // View into components
    auto view = registry.view<NpcAI, const Position, Direction, Speed>();

    // Update position from movement
    for (auto entity : view) {
        // Update movement
        // Turns are performed instantaneously, so they are updated by incoming
        // events
        // @todo add a target and current direction to allow for inertia in
        // turning
        auto &pos = view.get<const Position>(entity);
        auto &dir = view.get<Direction>(entity);
        auto &speed = view.get<Speed>(entity);
        auto &ai = view.get<NpcAI>(entity);

        // NPC behavior is going to be to walk towards the player, if close
        // enough
        const auto &targetPos = registry.get<const Position>(ai.target);
        const Vec2i vec = targetPos.value - pos.value;
        const Vec2f vecf = vec.template cast<float>();
        // Compute square of the distance
        const float dist = vecf.x() * vecf.x() + vecf.y() * vecf.y();

        speed.moving = 0;
        if (dist < ai.senseDistance * ai.senseDistance) {
            speed.moving = 1;
            dir.value = vecf;
        }
    }
}

// Render components affected by this system
void NpcSystem::render(entt::registry &) const {}

}  // namespace engine
}  // namespace coffee
