/****************************************************************************
 * Coffee
 * Copyright 2023 Eric Dymkoski eric.dymkoski@gmail.com
 * This software is distributed under the MIT license (see ~/License.md)
 ****************************************************************************/

// Collects user inputs, generating game events

#include "coffee/PlayerInput.h"

#include "SDL2/SDL.h"
#include "coffee/MovementSystem.h"

namespace coffee {
namespace engine {

bool PlayerInput::handleInput() {
    // Get the current keyboard state, which will be used to reconcile
    // multiple-key events, such as directions
    int numkeys = 0;
    const uint8_t* keys = SDL_GetKeyboardState(&numkeys);

    SDL_Event event;
    // FIXME this really shouldn't be done within the frame loop?
    // FIXME: the player should only receive sanitized inputs, not raw SDL
    // inputs
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return true;
        }

        // State-based inputs - events coming from changes in states
        const auto scancode = event.key.keysym.scancode;
        // FIXME: should check if it is a SDL_KEYUP or SDL_KEYDOWN, or are those
        // the only events?
        if (scancode == SDL_SCANCODE_UP || scancode == SDL_SCANCODE_DOWN ||
            scancode == SDL_SCANCODE_LEFT || scancode == SDL_SCANCODE_RIGHT) {
            MovementEvent movement;
            // Default to a stopped-state event
            movement.dir.value = Vec2f::Zero();
            movement.moving = 0;

            // Get the new Movement event based on the current state
            if (keys[SDL_SCANCODE_UP] && !keys[SDL_SCANCODE_DOWN]) {
                movement.dir.value(1) = -1;
                movement.moving = 1;
            }
            if (keys[SDL_SCANCODE_DOWN] && !keys[SDL_SCANCODE_UP]) {
                movement.dir.value(1) = 1;
                movement.moving = 1;
            }
            if (keys[SDL_SCANCODE_LEFT] && !keys[SDL_SCANCODE_RIGHT]) {
                movement.dir.value(0) = -1;
                movement.moving = 1;
            }
            if (keys[SDL_SCANCODE_RIGHT] && !keys[SDL_SCANCODE_LEFT]) {
                movement.dir.value(0) = 1;
                movement.moving = 1;
            }
            // For the basic keyboard input, the player cannot look in any
            // direction without first moving.  The final facing direction is
            // retained.
            movement.updateDir = movement.moving;

            // publish the event to all listeners
            // FIXME: how to handle received MovementEvents?
            publish(movement);
        }
    }
    return false;
}

}  // namespace engine
}  // namespace coffee
