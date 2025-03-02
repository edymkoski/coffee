/****************************************************************************
 * Coffee
 * Copyright 2023 Eric Dymkoski eric.dymkoski@gmail.com
 * This software is distributed under the MIT license (see ~/License.md)
 ****************************************************************************/

// Initial game demo

#pragma once

#include "SDL2/SDL.h"

namespace coffee {

class CoffeeGame {
   public:
    explicit CoffeeGame(SDL_Window* window, SDL_Renderer* renderer);

    void run();

   private:
    // The window we'll be rendering to
    SDL_Window* _window = nullptr;
    SDL_Renderer* _renderer = nullptr;
};

}  // namespace coffee