/****************************************************************************
 * Coffee
 * Copyright 2023 Eric Dymkoski eric.dymkoski@gmail.com
 * This software is distributed under the MIT license (see ~/License.md)
 ****************************************************************************/

// Animation system

#include "coffee/Animation.h"

#include "SDL2/SDL.h"
#include "coffee/components.h"

namespace coffee {
namespace engine {

AnimationSystem::AnimationSystem(SDL_Renderer *renderer)
    : _renderer(renderer) {}

void AnimationSystem::update(entt::registry &registry, uint64_t dt) const {
    auto view = registry.view<Animation>();

    uint32_t dt32 = static_cast<uint32_t>(dt);
    for (auto entity : view) {
        auto &anim = view.get<Animation>(entity);
        // make sure it loops properly
        const uint32_t length = anim.frames->size() * anim.speed;
        anim.time += dt32;
        anim.time = anim.time % length;
    }
}

void AnimationSystem::render(entt::registry &registry) const {
    auto view = registry.view<const Animation, const Position>();

    // FIXME: implement camera system

    // FIXME: what order to render in?
    for (auto entity : view) {
        auto &anim = view.get<const Animation>(entity);
        auto &pos = view.get<const Position>(entity);

        auto idx = anim.time / anim.speed;

        SDL_Texture *tex = anim.frames->operator[](idx);

        int w;
        int h;
        SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);

        // @todo: center of texture, or upper-left?
        SDL_Rect dest = {pos.value.x(), pos.value.y(), w, h};

        SDL_RenderCopy(_renderer, tex, nullptr, &dest);
    }
}

}  // namespace engine
}  // namespace coffee
