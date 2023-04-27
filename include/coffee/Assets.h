/****************************************************************************
 * Coffee
 * Copyright 2023 Eric Dymkoski eric.dymkoski@gmail.com
 * This software is distributed under the MIT license (see ~/License.md)
 ****************************************************************************/

// Asset managers

#pragma once

#include <filesystem>
#include <memory>

#include "SDL2/SDL.h"
#include "entt/entt.hpp"

namespace coffee {
namespace engine {


// Texture Loader
struct SDLTextureLoader final {
    // FIXME: should the result_type have the deleter in the signature?  is
    // there a cast happening?
    using result_type = std::shared_ptr<SDL_Texture>;

    // Wraps and transfers ownership of a Texture
    result_type operator()(SDL_Texture *value) const;

    // Load a texture from a filesystem path
    result_type operator()(const std::filesystem::path &filename,
                           SDL_Renderer *renderer) const;

    // Load a texture from a filesystem path
    result_type operator()(const std::filesystem::path &filename,
                           SDL_Renderer *renderer, SDL_Rect clip,
                           float scale = 1.0) const;

    SDL_Texture *loadTexture(const std::filesystem::path &filename,
                             SDL_Renderer *renderer, SDL_Rect clip,
                             float scale = 1.0) const;
};

// Texture Cache
using SDLTextureCache = entt::resource_cache<SDL_Texture, SDLTextureLoader>;

// Animation resource
using SDLFrames = std::vector<SDL_Texture *>;

// Animation Loader
struct SDLFramesLoader final {
    using result_type = std::shared_ptr<SDLFrames>;

    // Load an animation from a filesystem path
    result_type operator()(const std::filesystem::path &filename,
                           SDL_Renderer *renderer, SDL_Rect clip,
                           uint32_t nFrames, float scale = 1.0) const;
};

// Animation Cache
using SDLFramesCache = entt::resource_cache<SDLFrames, SDLFramesLoader>;

}  // namespace engine
}  // namespace coffee