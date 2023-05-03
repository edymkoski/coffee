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
    // _keyQueue.push_back(event);

    // Process d-pad commands
    if (event.key == KeyButton::DPad) {
        _dPadUpdate = true;
        const bool pressed = event.dir.x() != 0 || event.dir.y() != 0;
        // Default to no movement
        _lastCmd.moving = 0;

        // Only update the direction if the player is moving
        if (pressed) {
            _lastCmd.moving = 1;
            _lastCmd.inputDir = event.dir.template cast<float>();
        }
    }

    // Change player selection
    if (event.key == KeyButton::Select) {
        ++_selectCount;
    }
}

// Update componenets affected by this system
void PlayerSystem::update(entt::registry &registry, uint64_t /*dt*/) {
    // Initialize check for direction-pad events
    // bool dpadUpdate = false;
    // uint32_t moving = 0;
    // Vec2f inputDir = Vec2f::Zero();

    // TODO: it looks like most of these could be processed on receipt into
    // counters, not needing a queue
    //
    // Use counters for the number of times a
    // switch button has been pressed
    int selectCount = _selectCount;
    // Process queue
    // for (const auto &k : _keyQueue) {
    //     // if (k.key == KeyButton::DPad) {
    //     //     dpadUpdate = true;
    //     //     const bool pressed = k.dir.x() != 0 || k.dir.y() != 0;
    //     //     moving = 0;  // Default to no movement
    //     //                  // Only update the direction if the player is
    //     moving
    //     //     if (pressed) {
    //     //         moving = 1;
    //     //         inputDir = k.dir.template cast<float>();
    //     //     }
    //     // }

    //     if (k.key == KeyButton::Select) {
    //         ++selectCount;
    //     }
    // }
    // _keyQueue.clear();

    // View into components
    auto view = registry.view<PlayerControl, Direction, Speed>();

    int activeIdx = 0;  // Newly selected player idx
    entt::entity activeEntity = entt::null;
    if (selectCount > 0) {
        // select new player entity to control
        int nPlayers = 0;
        int entitiesAfter = 0;
        for ([[maybe_unused]] auto entity : view) {
            // Count players, and clear all control flags
            auto &control = view.get<PlayerControl>(entity);
            if (control.active) {
                activeEntity = entity;
                entitiesAfter = 0;
            }
            control.active = 0;

            // increment count of entities after
            if (activeEntity != entt::null) {
                ++entitiesAfter;
            }

            ++nPlayers;
        }

        // Compute the index of the newly selected entity
        int oldActiveIdx = nPlayers - entitiesAfter;
        selectCount += oldActiveIdx;
        activeIdx = selectCount % nPlayers;

        // if there are no active entities, do nothing
    }

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

        // Select entity, if applicable
        if (activeIdx == 0 && activeEntity != entt::null) {
            control.active = 1;
        }
        --activeIdx;

        // Stop unactive players
        // TODO: control might be handed off to their own AI
        if (!control.active) {
            speed.moving = 0;
        }

        // Updated selections automatically force a d-pad update
        if ((_dPadUpdate || _selectCount > 0) && control.active) {
            speed.moving = _lastCmd.moving;
            if (_lastCmd.moving > 0) {  // only update direction if moving
                dir.value = _lastCmd.inputDir;
            }
        }
    }

    // Clear event counters
    _selectCount = 0;
    _dPadUpdate = false;
}

// Render components affected by this system
void PlayerSystem::render(entt::registry &) const {}

}  // namespace engine
}  // namespace coffee
