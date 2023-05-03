/****************************************************************************
 * Coffee
 * Copyright 2023 Eric Dymkoski eric.dymkoski@gmail.com
 * This software is distributed under the MIT license (see ~/License.md)
 ****************************************************************************/

// Collects user inputs, generating game events

#include "coffee/PlayerSystem.h"

#include "SDL2/SDL.h"
#include "coffee/InputHandler.h"
#include "coffee/MovementSystem.h"

namespace coffee {
namespace engine {

void PlayerSystem::keyButtonEvent(KeyEvent event) {
    // Insert in queue
    // Note: need to insert in the queue and cannot easily update directly,
    // because this method does not have access to the registry

    // TODO: dpad events could be processed on receipt, only pushing other
    // events back into the queue
    _keyQueue.push_back(event);
}

// Update componenets affected by this system
void PlayerSystem::update(entt::registry &registry, uint64_t /*dt*/) {
    // Initialize check for direction-pad events
    bool dpadUpdate = false;
    uint32_t moving = 0;
    Vec2f inputDir = Vec2f::Zero();

    for (const auto &k : _keyQueue) {
        if (k.key == KeyButton::DPad) {
            dpadUpdate = true;
            const bool pressed = k.dir.x() != 0 || k.dir.y() != 0;
            moving = 0;  // Default to no movement
                         // Only update the direction if the player is moving
            if (pressed) {
                moving = 1;
                inputDir = k.dir.template cast<float>();
            }
        }
    }
    _keyQueue.clear();

    // View into components
    auto view = registry.view<PlayerControl, Direction, Speed>();

    // Update position from movement
    for (auto entity : view) {
        // Update movement
        // Turns are performed instantaneously, so they are updated by
        // incoming events
        // @todo add a target and current direction to allow for inertia in
        // turning
        auto &control = view.get<PlayerControl>(entity);
        auto &dir = view.get<Direction>(entity);
        auto &speed = view.get<Speed>(entity);
        if (dpadUpdate && control.active) {
            speed.moving = moving;
            if (moving > 0) {  // only update direction if moving
                dir.value = inputDir;
            }
        }
    }
}

// Render components affected by this system
void PlayerSystem::render(entt::registry &) const {}

}  // namespace engine
}  // namespace coffee
