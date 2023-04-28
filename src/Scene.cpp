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
      _animation(renderer),
      _movement() {}

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

    _frames.load("right_walk"_hs, texPath.c_str(), _renderer,
                 SDL_Rect{0, 64, 32, 32}, 4, 4.0);

    // Create a player character
    const auto entity = _registry.create();
    _registry.emplace<engine::Animation>(entity, _frames["right_walk"_hs], 0,
                                         200);
    _registry.emplace<engine::Position>(entity, engine::Vec2i(50, 100));
    _registry.emplace<engine::Direction>(entity, engine::Vec2f(100, 0));
    _registry.emplace<engine::Speed>(entity, 375.0f, 0);

    // Attache the movement system as a listerner on the PlayerInput
    // FIXME: bind the entity ID to this function, so the PlayerInput updates
    // the correct entity
    // FIXME: what is the point of including the emitter?  context data?
    // FIXME: including the emitter makes the event handler aware of the
    // emitter, but the emitter should be abstract?
    // Note: the connection can be used to manage lifetime.  Note, this
    // shouldn't be an issue, since the emitter/listener are systems, not
    // components
    // auto conn =
    // FIXME: can multiple MovementEvents be connected to the same emitter?
    _player.on<engine::MovementEvent>(
        [&](const engine::MovementEvent &event, engine::PlayerInput &) {
            // ...
            // FIXME: push a movement event on the MovementHandler?
            _movement.queueMovement(entity, event);
        });
}

bool Scene::update(uint64_t dt) {
    // FIXME: how to properly handle the quit state?
    // FIXME: should this be handled in a different Scene function, or by the
    // client code?  Right now it is needed here so that different listeners in
    // the scene can be connected to the Input Handler
    // Alternatively, the Input Handler could be owned by the game, stripped of
    // non-generic events, and a handle passed to the scene where it is
    // connected to the Player.  The Player receives general game events, and
    // translates them into Scene events which are emitted for game systems. The
    // Player system processes a much smaller queue - though this does increase
    // the number of systems that events must pass through, which is strange
    // A separate game-level InputManager is probably the right thing, since
    // each scene is going to take different actions based on the input
    const bool quit = _player.handleInput();
    if (quit) {
        return true;
    }

    _movement.update(_registry, dt);
    _animation.update(_registry, dt);

    return false;
}

void Scene::render() {
    _movement.render(_registry);
    _animation.render(_registry);
}

}  // namespace coffee