/****************************************************************************
 * Coffee
 * Copyright 2023 Eric Dymkoski eric.dymkoski@gmail.com
 * This software is distributed under the MIT license (see ~/License.md)
 ****************************************************************************/

// Initial Scene demo

#pragma once

#include "coffee/Animation.h"
#include "coffee/Assets.h"
#include "coffee/Movement.h"
#include "entt/entt.hpp"

namespace coffee {

// Hashable string for asset cache access
using entt::operator""_hs;

class Scene {
   public:
    explicit Scene(SDL_Renderer* renderer);

    // initialize object
    void initialize();

    // update the state of the level
    void update(uint64_t dt);

    // render the scene
    void render();

   private:
    SDL_Renderer* _renderer = nullptr;

    // FIXME: should this really have its own asset manager?  or should it
    // receive assets from the client for better long-term management?
    engine::SDLTextureCache _textures;
    engine::SDLFramesCache _frames;

    entt::registry _registry;

    // @todo list of ISystems?
    engine::AnimationSystem _animation;
    engine::MovementSystem _movement;
};

}  // namespace coffee