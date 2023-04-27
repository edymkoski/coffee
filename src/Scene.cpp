/****************************************************************************
 * Coffee
 * Copyright 2023 Eric Dymkoski eric.dymkoski@gmail.com
 * This software is distributed under the MIT license (see ~/License.md)
 ****************************************************************************/

// Initial Scene demo

#include "coffee/Scene.h"

#include "SDL2/SDL.h"
#include "coffee/components.h"

namespace coffee {

Scene::Scene(SDL_Renderer* renderer)
    : _renderer(renderer),
      _textures(),
      _frames(),
      _registry(),
      _animation(renderer) {}

void Scene::initialize() {
    // Load textures into the cache

    // Get executable path
    // FIXME: store helper function elsewhere - preferrably the asset managers
    const auto exePath =
        std::filesystem::canonical("/proc/self/exe").remove_filename();

    // Initialize the game-level font
    // @todo how to configure different assets?  Should be procedurally loaded
    auto texPath = exePath / "./resources/AnimationSheet_Character.png";

    // Test texture
    // FIXME: should textures also be assigned a layer at this point?
    // FIXME: are textures unloaded automatically on destruction?

    // FIXME: alpha
    // FIXME: able to sub-select a part of a sprite sheet
    // FIXME: use a hashed-string as an id
    _textures.load("character"_hs, texPath.c_str(), _renderer,
                   SDL_Rect{0, 0, 32, 32}, 4.0);

    _frames.load("right_idle"_hs, texPath.c_str(), _renderer,
                 SDL_Rect{0, 0, 32, 32}, 2, 4.0);

    // Create a character
    const auto entity = _registry.create();
    _registry.emplace<engine::Animation>(entity, _frames["right_idle"_hs], 0,
                                         200);
    _registry.emplace<engine::Position>(entity, 500, 100);
}

void Scene::update(uint64_t dt) { _animation.update(_registry, dt); }

void Scene::render() { _animation.render(_registry); }

}  // namespace coffee