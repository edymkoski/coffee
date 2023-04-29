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

// Update componenets affected by this system
void PlayerSystem::update(entt::registry &registry, uint64_t /*dt*/) {
    // FIXME: much of this code is going to be similar for the AI and the Player
    // systems, will need to figure out how to consolidate?

    // For the basic keyboard input, the player cannot look in any
    // direction without first moving.  The final facing direction is
    // retained.

    // input state
    InputHandler *g_input = InputHandler::GetInstance();
    const Vec2i directionInput = g_input->directionInput();

    // If there are no directional inputs, there is no movement, and no need to
    // update the direction
    const bool pressed = directionInput.x() != 0 || directionInput.y() != 0;

    // View into components
    auto view = registry.view<PlayerControllableTag, Direction, Speed>();

    // Update position from movement
    for (auto entity : view) {
        // Update movement
        // Turns are performed instantaneously, so they are updated by incoming
        // events
        // @todo add a target and current direction to allow for inertia in
        // turning
        auto &dir = view.get<Direction>(entity);
        auto &speed = view.get<Speed>(entity);

        speed.moving = 0;
        if (pressed) {
            speed.moving = 1;
            dir.value = directionInput.template cast<float>();
        }
    }
}

// Render components affected by this system
void PlayerSystem::render(entt::registry &) const {}

}  // namespace engine
}  // namespace coffee
