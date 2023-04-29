/****************************************************************************
 * Coffee
 * Copyright 2023 Eric Dymkoski eric.dymkoski@gmail.com
 * This software is distributed under the MIT license (see ~/License.md)
 ****************************************************************************/

// Collects user inputs, generating game events

#pragma once

#include <numeric>

#include "coffee/ISystem.h"
#include "entt/entt.hpp"

namespace coffee {
namespace engine {

// Tag for entities that will be player controllable
struct NpcAI {
    entt::entity target = entt::null;
    float senseDistance = 1000.0;
};

// User Input - emmits events to the appropriate listeners
class NpcSystem : ISystem {
   public:
    NpcSystem() = default;
    virtual ~NpcSystem() {}

    // Update componenets affected by this system
    void update(entt::registry &registry, uint64_t dt) override;

    // Render components affected by this system
    void render(entt::registry &registry) const override;
};

}  // namespace engine
}  // namespace coffee
