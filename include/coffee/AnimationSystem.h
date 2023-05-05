/****************************************************************************
 * Coffee
 * Copyright 2023 Eric Dymkoski eric.dymkoski@gmail.com
 * This software is distributed under the MIT license (see ~/License.md)
 ****************************************************************************/

// Animation components and system

#pragma once

#include "coffee/Assets.h"
#include "coffee/ISystem.h"
#include "entt/entt.hpp"

namespace coffee {
namespace engine {

// Animation component
// FIXME: this naming around animations is pretty convoluted
struct Sprite {
    Animation animation;
    AnimationControl control;
};

// System for running animations for sprites
// FIXME: add complex capability that allows for more complex compositing of
// multiple clips
class AnimationSystem : public ISystem {
   public:
    explicit AnimationSystem(SDL_Renderer *renderer);
    virtual ~AnimationSystem() {}

    // Update componenets affected by this system
    void update(entt::registry &registry, uint64_t dt) override;

    // Render components affected by this system
    void render(entt::registry &registry) const override;

   private:
    SDL_Renderer *_renderer = nullptr;
};

}  // namespace engine
}  // namespace coffee
