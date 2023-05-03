/****************************************************************************
 * Coffee
 * Copyright 2023 Eric Dymkoski eric.dymkoski@gmail.com
 * This software is distributed under the MIT license (see ~/License.md)
 ****************************************************************************/

// Initial Scene demo

#pragma once

#include "coffee/AnimationSystem.h"
#include "coffee/Assets.h"
#include "coffee/InputHandler.h"
#include "coffee/MovementSystem.h"
#include "coffee/NpcSystem.h"
#include "coffee/PlayerSystem.h"
#include "entt/entt.hpp"

namespace coffee {

// Hashable string for asset cache access
using entt::operator""_hs;

class Scene {
   public:
    explicit Scene(SDL_Renderer* renderer);

    // initialize object
    void initialize(engine::InputHandler& input);

    // update the state of the scene
    void update(uint64_t dt);

    // render the scene
    void render();

   private:
    SDL_Renderer* _renderer = nullptr;

    // @todo: should this really have its own asset manager?  or should it
    // receive assets from the client for better long-term management?
    engine::SDLTextureCache _textures;
    engine::SDLFramesCache _frames;

    entt::registry _registry;

    // @todo list of ISystems?  How to preserve a sensible order?
    engine::PlayerSystem _player;
    engine::NpcSystem _npc;
    engine::AnimationSystem _animation;
    engine::MovementSystem _movement;
};

}  // namespace coffee