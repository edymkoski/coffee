/****************************************************************************
 * Coffee
 * Copyright 2023 Eric Dymkoski eric.dymkoski@gmail.com
 * This software is distributed under the MIT license (see ~/License.md)
 ****************************************************************************/

// Initial game demo

#include <coffee/CoffeeGame.h>
#include <coffee/Level.h>

namespace coffee {
CoffeeGame::CoffeeGame(SDL_Window* window) : _window(window) {}

void CoffeeGame::run() {
    // Get window surface
    SDL_Surface* screenSurface = SDL_GetWindowSurface(_window);

    // Fill the surface white
    SDL_FillRect(screenSurface, nullptr,
                 SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

    // Update the surface
    SDL_UpdateWindowSurface(_window);

    // Create and initialize the game level
    Level level;
    level.initialize();

    // Main game loop
    SDL_Event e;
    bool quit = false;
    while (quit == false) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // update and draw level here
        level.update(dt);

        // TODO: game-level overlay with diagnostics, such as FPS
    }
}

}  // namespace coffee