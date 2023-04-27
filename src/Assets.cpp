/****************************************************************************
 * Coffee
 * Copyright 2023 Eric Dymkoski eric.dymkoski@gmail.com
 * This software is distributed under the MIT license (see ~/License.md)
 ****************************************************************************/

// Asset managers

#include "coffee/Assets.h"

#include <filesystem>
#include <memory>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "coffee/common_error.h"
#include "entt/entt.hpp"

namespace coffee {
namespace engine {

// Wraps and transfers ownership of a Texture
SDLTextureLoader::result_type SDLTextureLoader::operator()(
    SDL_Texture *value) const {
    // return std::shared_ptr<SDL_Texture,SDL_DestroyTexture>(value,
    // SDL_DestroyTexture);
    return {value, SDL_DestroyTexture};
}

// Load a texture from a filesystem path
SDLTextureLoader::result_type SDLTextureLoader::operator()(
    const std::filesystem::path &filename, SDL_Renderer *renderer) const {
    const auto absPath = std::filesystem::canonical(filename);

    // Load the image to a surface, and convert to a texture for performance
    SDL_Surface *buffer = IMG_Load(absPath.c_str());
    COFFEE_CHECK(buffer, std::runtime_error, "Error loading image: {:}, ({:})",
                 absPath.string(), SDL_GetError());

    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, buffer);
    SDL_FreeSurface(buffer);
    buffer = nullptr;
    COFFEE_CHECK(tex, std::runtime_error, "Error creating texture ({:})",
                 SDL_GetError());
    return this->operator()(tex);
}

// Load a texture from a filesystem path
SDL_Texture *SDLTextureLoader::loadTexture(

    const std::filesystem::path &filename, SDL_Renderer *renderer,
    SDL_Rect clip, float scale) const {
    const auto absPath = std::filesystem::canonical(filename);

    // Load the image to a surface, and convert to a texture for performance
    SDL_Surface *buffer = IMG_Load(absPath.c_str());
    COFFEE_CHECK(buffer, std::runtime_error, "Error loading image: {:}, ({:})",
                 absPath.string(), SDL_GetError());

    SDL_Texture *sheet = SDL_CreateTextureFromSurface(renderer, buffer);
    SDL_FreeSurface(buffer);
    buffer = nullptr;
    COFFEE_CHECK(sheet, std::runtime_error, "Error creating texture ({:})",
                 SDL_GetError());

    // Clip
    auto prevTarget = SDL_GetRenderTarget(renderer);

    // FIXME: alpha

    SDL_Texture *tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                         SDL_TEXTUREACCESS_TARGET,
                                         clip.w * scale, clip.h * scale);
    SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
    // SDL_Rect rect = {i * width / clipPerRow, j * height / clipPerColumn,
    //                  width / clipPerRow, height / clipPerColumn};
    SDL_SetRenderTarget(renderer, tex);

    // FIXME: renderer?
    SDL_RenderCopy(renderer, sheet, &clip, NULL);

    // Reset the previous render target
    SDL_SetRenderTarget(renderer, prevTarget);

    return tex;
}

SDLTextureLoader::result_type SDLTextureLoader::operator()(
    const std::filesystem::path &filename, SDL_Renderer *renderer,
    SDL_Rect clip, float scale) const {
    auto *tex = this->loadTexture(filename, renderer, clip, scale);
    return this->operator()(tex);
}

namespace {
// Frames custom deleter
void SDLFramesDeleter(SDLFrames *frames) {
    for (auto &f : *frames) {
        SDL_DestroyTexture(f);
    }
    delete frames;
}
}  // namespace

SDLFramesLoader::result_type SDLFramesLoader::operator()(
    const std::filesystem::path &filename, SDL_Renderer *renderer,
    SDL_Rect clip, uint32_t nFrames, float scale) const {
    SDLFrames *animation = new SDLFrames;
    animation->resize(nFrames, nullptr);

    // Use the texture loader to load frames from a spritesheet
    SDLTextureLoader textureLoader;
    for (uint32_t i = 0; i < nFrames; ++i) {
        SDL_Rect spriteClip = clip;
        spriteClip.x += clip.w * i;
        auto tex =
            textureLoader.loadTexture(filename, renderer, spriteClip, scale);
        animation->operator[](i) = tex;
    }

    return result_type{animation, SDLFramesDeleter};
}

}  // namespace engine
}  // namespace coffee