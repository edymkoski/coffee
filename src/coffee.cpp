/****************************************************************************
 * Coffee
 * Copyright 2023 Eric Dymkoski eric.dymkoski@gmail.com
 * This software is distributed under the MIT license (see ~/License.md)
 ****************************************************************************/

// Coffee engine top-level functionality

#include "coffee/coffee.h"

#include <cstdio>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"

namespace coffee {
namespace engine {

bool initialize() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Initialize image subsystem
    if (IMG_Init(IMG_INIT_JPG) < 0) {
        printf("Error initializing SDL_image: %s\n", IMG_GetError());
        return false;
    }

    // Initialize fonts
    if (TTF_Init() < 0) {
        printf("Error initializing SDL_ttf: %s\n", TTF_GetError());

        return false;
    }

    return true;
}

void finalize() {
    // Finalize the font lib
    TTF_Quit();

    // Finalize the SDL IMG subsystem
    IMG_Quit();

    // Quit SDL subsystems
    SDL_Quit();
}

}  // namespace engine
}  // namespace coffee