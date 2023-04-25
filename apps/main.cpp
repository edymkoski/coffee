/****************************************************************************
 * Coffee
 * Copyright 2023 Eric Dymkoski eric.dymkoski@gmail.com
 * This software is distributed under the MIT license (see ~/License.md)
 ****************************************************************************/

#include <cstdio>

#include "SDL2/SDL.h"
#include "coffee/CoffeeGame.h"
#include "coffee/coffee.h"

// Screen dimension constants
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 840;

using namespace coffee;

int main(int argc, char* args[]) {
    // The window we'll be rendering to
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;  // Should renderer be owned by the game?

    // Initialize SDL
    if (engine::initialize()) {
        // Create window
        window = SDL_CreateWindow("Coffee", SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (window == nullptr) {
            printf("Window could not be created! SDL_Error: %s\n",
                   SDL_GetError());
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        if (renderer == nullptr) {
            printf("Renderer could not be created! SDL_Error: %s\n",
                   SDL_GetError());
        }

        CoffeeGame game(window, renderer);
        game.run();
    }

    // Destroy windows
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    return 0;
}
