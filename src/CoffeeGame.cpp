/****************************************************************************
 * Coffee
 * Copyright 2023 Eric Dymkoski eric.dymkoski@gmail.com
 * This software is distributed under the MIT license (see ~/License.md)
 ****************************************************************************/

// Initial game demo

#include "coffee/CoffeeGame.h"

#include <cstdint>
#include <filesystem>
#include <string>

#include "SDL2/SDL_ttf.h"
#include "coffee/Scene.h"

namespace coffee {
CoffeeGame::CoffeeGame(SDL_Window* window, SDL_Renderer* renderer)
    : _window(window), _renderer(renderer) {}

namespace {
void renderText(std::string text, SDL_Rect dest, SDL_Renderer* renderer,
                TTF_Font* font, SDL_Color fg = {0, 0, 0}) {
    SDL_Surface* surf = TTF_RenderText_Solid(font, text.c_str(), fg);

    dest.w = surf->w;
    dest.h = surf->h;

    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);

    SDL_RenderCopy(renderer, tex, NULL, &dest);
    SDL_DestroyTexture(tex);
    SDL_FreeSurface(surf);
}
}  // namespace

void CoffeeGame::run() {
    // 60 FPS limiter
    constexpr uint64_t interval = 17;

    // Clear the surface
    SDL_SetRenderDrawColor(_renderer, 120, 120, 120, 255);
    SDL_RenderClear(_renderer);
    SDL_RenderPresent(_renderer);

    // Get executable path
    // FIXME: store helper function elsewhere - preferrably the asset managers
    const auto exePath =
        std::filesystem::canonical("/proc/self/exe").remove_filename();

    // Initialize the game-level font
    // FIXME: should place this in an asset manager
    TTF_Font* font;
    auto fontPath = exePath / "./resources/gnu-free-font/FreeMonoBold.ttf";
    font = TTF_OpenFont(fontPath.c_str(), 24);
    if (!font) {
        printf("Error loading font: %s\n", TTF_GetError());
        return;
    }

    // Create and initialize the game level
    Scene scene(_renderer);
    scene.initialize();

    // Main game loop
    // SDL_Event e;
    bool quit = false;
    uint64_t previousTime = 0;  // Initialize to zero, so that the first frame
                                // will be updated and rendered
    float fpsAvg = 0.0;
    while (quit == false) {
        // Check for exit
        // FIXME: could retain here if it does not empty the queue
        // while (SDL_PollEvent(&e)) {
        //     if (e.type == SDL_QUIT) {
        //         quit = true;
        //     }
        // }

        // Compute dt for a limited frame rate
        const uint64_t currentTime = SDL_GetTicks64();

        auto dt = currentTime - previousTime;
        if (dt >= interval) {
            previousTime = currentTime;

            // todo: check for exit

            // Clear the window for the current frame
            SDL_RenderClear(_renderer);

            quit = scene.update(dt);
            if (quit) {  // exit early without completing further actions
                break;
            }
            scene.render();

            // Game-level overlay with diagnostics, such as FPS
            {
                const float eps = 0.1;
                const float fpsFloat = 1000.0f / dt;
                fpsAvg = (1.0 - eps) * fpsAvg + eps * fpsFloat;
                auto fpsString = std::to_string(fpsAvg);

                SDL_Rect dest = {10, 10, 0, 0};
                renderText(fpsString, dest, _renderer, font, {100, 149, 237});
            }
            // Update the screen
            SDL_RenderPresent(_renderer);

        } else {
            uint64_t remainingTime = interval - dt;
            SDL_Delay(remainingTime);
        }
    }

    // Kill the font for game-level writing
    // FIXME: do this in the asset manager
    TTF_CloseFont(font);
}

}  // namespace coffee