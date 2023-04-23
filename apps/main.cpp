/****************************************************************************
 * Coffee
 * Copyright 2023 Eric Dymkoski eric.dymkoski@gmail.com
 * This software is distributed under the MIT license (see ~/License.md)
 ****************************************************************************/

#include <SDL2/SDL.h>
#include <coffee/CoffeeGame.h>

#include <cstdio>

// Screen dimension constants
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 840;

using namespace coffee;

int main(int argc, char* args[]) {
    // The window we'll be rendering to
    SDL_Window* window = nullptr;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    } else {
        // Create window
        window = SDL_CreateWindow("Coffee", SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == nullptr) {
            printf("Window could not be created! SDL_Error: %s\n",
                   SDL_GetError());
        } else {
            CoffeeGame game(window);

            game.run();
        }
    }

    // Destroy window
    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    SDL_Quit();

    return 0;
}
