/****************************************************************************
 * Coffee
 * Copyright 2023 Eric Dymkoski eric.dymkoski@gmail.com
 * This software is distributed under the MIT license (see ~/License.md)
 ****************************************************************************/

// Initial Level demo

#include <coffee/CoffeeGame.h>

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

    // Main game loop
    SDL_Event e;
    bool quit = false;
    while (quit == false) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = true;
        }
    }
}

}  // namespace coffee