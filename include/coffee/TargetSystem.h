/****************************************************************************
 * Coffee
 * Copyright 2023 Eric Dymkoski eric.dymkoski@gmail.com
 * This software is distributed under the MIT license (see ~/License.md)
 ****************************************************************************/

// Targeting system for AI

#pragma once

#include "coffee/ISystem.h"
#include "entt/entt.hpp"

namespace coffee {
namespace engine {

// System for moving sprites
class TargetSystem : public ISystem {
   public:
    TargetSystem() = default;
    virtual ~TargetSystem() {}

    // Update componenets affected by this system
    void update(entt::registry &registry, uint64_t dt) override;

    // Render components affected by this system
    void render(entt::registry &) const override {}
};

}  // namespace engine
}  // namespace coffee
