/****************************************************************************
 * Coffee
 * Copyright 2023 Eric Dymkoski eric.dymkoski@gmail.com
 * This software is distributed under the MIT license (see ~/License.md)
 ****************************************************************************/

// Sprite movement components and system

#pragma once

#include "coffee/ISystem.h"
#include "coffee/components.h"
#include "entt/entt.hpp"

namespace coffee {
namespace engine {

// Direction component
// Note: velocity is given as an int in order to not have roundoff errors at
// large values
struct Direction {
    Vec2f value = Vec2f::Zero();
};

// Speed component
// [pixels/s]
struct Speed {
    float value = 0.f;  // @todo int16?
    uint32_t moving = 0;
};

// Event for updating movement - implies setting the Speed movement flag
// A direction vector of zero length indicates no update to the direction
// FIXME: flag?
struct MovementEvent {
    Direction dir = {};
    uint8_t updateDir = 0;
    uint8_t moving = 0;
};

// System for moving sprites
// This is an event handler for MovementEvents.  A movement event will provide
// movement for a single frame, but the movement is not persistent without
// another event.
// FIXME: this means that a lot of events will be generated.  Instead, updates
// should be sent explicitly when the state needs to change
class MovementSystem : public ISystem {
   public:
    MovementSystem() = default;
    virtual ~MovementSystem() {}

    // Update componenets affected by this system
    void update(entt::registry &registry, uint64_t dt) override;

    // Render components affected by this system
    void render(entt::registry &registry) const override;

    void queueMovement(entt::entity entity, const engine::MovementEvent &event);

   private:
    // Queue of active movements
    std::vector<std::pair<entt::entity, engine::MovementEvent>> _movementQueue;
};

}  // namespace engine
}  // namespace coffee
