/****************************************************************************
 * Coffee
 * Copyright 2023 Eric Dymkoski eric.dymkoski@gmail.com
 * This software is distributed under the MIT license (see ~/License.md)
 ****************************************************************************/

// Collects user inputs, generating game events

#pragma once

#include "coffee/ISystem.h"
#include "coffee/InputHandler.h"
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

    // Listener for handling KeyEvents
    void keyButtonEvent(KeyEvent event);

   private:
    std::vector<KeyEvent>
        _keyQueue;  // FIXME: inheritance - handler for different events
};

}  // namespace engine
}  // namespace coffee
