/****************************************************************************
 * Coffee
 * Copyright 2023 Eric Dymkoski eric.dymkoski@gmail.com
 * This software is distributed under the MIT license (see ~/License.md)
 ****************************************************************************/

// System interface, for an Entity-Componenet-System

#pragma once

#include "entt/entt.hpp"

namespace coffee {
namespace engine {

// System interface
class ISystem {
   public:
    virtual ~ISystem() {}

    // Update componenets affected by this system
    virtual void update(entt::registry &registry, uint64_t dt) const = 0;

    // Render components affected by this system
    virtual void render(entt::registry &registry) const = 0;
};

}  // namespace engine
}  // namespace coffee
