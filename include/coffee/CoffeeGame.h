/****************************************************************************
 * Coffee
 * Copyright 2023 Eric Dymkoski eric.dymkoski@gmail.com
 * This software is distributed under the MIT license (see ~/License.md)
 ****************************************************************************/

// Initial Level demo

#pragma once

#include <SDL2/SDL.h>

namespace coffee {

class CoffeeGame {
   public:
    explicit CoffeeGame(SDL_Window* window);

    void run();

   private:
    // The window we'll be rendering to
    SDL_Window* _window = nullptr;
};

}  // namespace coffee