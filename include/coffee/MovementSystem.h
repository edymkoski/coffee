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

// System for moving sprites
class MovementSystem : public ISystem {
   public:
    MovementSystem() = default;
    virtual ~MovementSystem() {}

    // Update componenets affected by this system
    void update(entt::registry &registry, uint64_t dt) override;

    // Render components affected by this system
    void render(entt::registry &registry) const override;
};

}  // namespace engine
}  // namespace coffee
