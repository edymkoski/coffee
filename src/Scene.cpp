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

Scene::Scene(SDL_Renderer *renderer)
    : _renderer(renderer),
      _textures(),
      _frames(),
      _registry(),
      _player(),
      _npc(),
      _animation(renderer),
      _movement(),
      _target() {}

void Scene::initialize(engine::InputHandler &input) {
    // Form signal/event connections between systems
    input.sig().connect(&_player, &engine::PlayerSystem::keyButtonEvent,
                        std::placeholders::_1);

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

    _frames.load("right_walk"_hs, texPath.c_str(), _renderer,
                 SDL_Rect{0, 64, 32, 32}, 4, 4.0);

    // FIXME: generators for different entities

    // Create a player character
    for (uint8_t i = 0; i < 2; ++i) {
        const auto entity = _registry.create();
        _registry.emplace<engine::Animation>(entity, _frames["right_walk"_hs],
                                             0, 200);
        _registry.emplace<engine::Position>(entity,
                                            engine::Vec2i(50 + 100 * i, 100));
        _registry.emplace<engine::Direction>(entity, engine::Vec2f(100, 0));
        _registry.emplace<engine::Speed>(entity, 350.0f, 0);

        _registry.emplace<engine::PlayerControl>(entity, i);
    }
    // Create a NPC
    {
        const auto entity = _registry.create();
        _registry.emplace<engine::Animation>(entity, _frames["right_idle"_hs],
                                             0, 200);
        _registry.emplace<engine::Position>(entity, engine::Vec2i(400, 400));
        _registry.emplace<engine::Direction>(entity, engine::Vec2f(100, 0));
        _registry.emplace<engine::Speed>(entity, 150.0f, 0);

        // FIXME: procedural targeting
        _registry.emplace<engine::NpcAI>(entity, entt::null, 350);
    }
}

void Scene::update(uint64_t dt) {
    // Handle player and any AI first, since this deals with input
    _target.update(_registry, dt);
    _player.update(_registry, dt);
    _npc.update(_registry, dt);

    _movement.update(_registry, dt);
    _animation.update(_registry, dt);
}

void Scene::render() {
    _target.render(_registry);
    _player.render(_registry);
    _npc.render(_registry);

    _movement.render(_registry);
    _animation.render(_registry);
}

}  // namespace coffee