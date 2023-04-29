/****************************************************************************
 * Coffee
 * Copyright 2023 Eric Dymkoski eric.dymkoski@gmail.com
 * This software is distributed under the MIT license (see ~/License.md)
 ****************************************************************************/

// Collects user inputs, generating game events

#pragma once

#include "coffee/ISystem.h"
#include "entt/entt.hpp"

namespace coffee {
namespace engine {

// Tag for entities that will be player controllable
struct PlayerControllableTag {};

// User Input - emmits events to the appropriate listeners
class PlayerSystem : ISystem {
   public:
    PlayerSystem() = default;
    virtual ~PlayerSystem() {}

    // Update componenets affected by this system
    void update(entt::registry &registry, uint64_t dt) override;

    // Render components affected by this system
    void render(entt::registry &registry) const override;

   private:
    // Signal emitter
    // FIXME: will need to be able to add/remove listeners
    // Overall question if signals are destined to multiple specific entities,
    // or if they are general, and sent to systems
    // A collision system can send multiple collisions, but it is still 1:1
    // FIXME: question - how can a player switch which entity they control?
    // Connect a new signal, or what?
    //  entt::sigh<void(int, char)> _movementSignal; // doess entt:sigh have any
    //  advantages?
    // entt::dispatcher _dispatcher = {};
};

}  // namespace engine
}  // namespace coffee
