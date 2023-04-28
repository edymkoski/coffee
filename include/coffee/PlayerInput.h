/****************************************************************************
 * Coffee
 * Copyright 2023 Eric Dymkoski eric.dymkoski@gmail.com
 * This software is distributed under the MIT license (see ~/License.md)
 ****************************************************************************/

// Collects user inputs, generating game events

#pragma once

#include "entt/entt.hpp"

namespace coffee {
namespace engine {

// User Input - emmits events to the appropriate listeners
class PlayerInput : public entt::emitter<PlayerInput> {
   public:
    PlayerInput() = default;
    virtual ~PlayerInput() {}

    // Handle all inputs
    // Returns whether a "quit" signal has been received
    bool handleInput();

   private:
};

}  // namespace engine
}  // namespace coffee
