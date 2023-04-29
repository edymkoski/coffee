/****************************************************************************
 * Coffee
 * Copyright 2023 Eric Dymkoski eric.dymkoski@gmail.com
 * This software is distributed under the MIT license (see ~/License.md)
 ****************************************************************************/

// Input handler

#include "coffee/InputHandler.h"

#include "SDL2/SDL.h"

namespace coffee {
namespace engine {

InputHandler* InputHandler::_singleton = nullptr;

InputHandler* InputHandler::GetInstance() {
    //  This is a safer way to create an instance. instance = new InputHandler
    //  is dangeruous in case two instance threads wants to access at the same
    //  time
    if (_singleton == nullptr) {
        _singleton = new InputHandler();
    }
    return _singleton;
}

void InputHandler::handleInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            _quit = true;
            return;  // Early return, since a quit has been called
        }

        // Direction
        // Record state of the D-Pad
        const auto scancode = event.key.keysym.scancode;

        if (scancode == SDL_SCANCODE_UP) {
            if (event.type == SDL_KEYDOWN) {
                _up_pressed = true;
            }
            if (event.type == SDL_KEYUP) {
                _up_pressed = false;
            }
        }

        if (scancode == SDL_SCANCODE_DOWN) {
            if (event.type == SDL_KEYDOWN) {
                _down_pressed = true;
            }
            if (event.type == SDL_KEYUP) {
                _down_pressed = false;
            }
        }

        if (scancode == SDL_SCANCODE_LEFT) {
            if (event.type == SDL_KEYDOWN) {
                _left_pressed = true;
            }
            if (event.type == SDL_KEYUP) {
                _left_pressed = false;
            }
        }

        if (scancode == SDL_SCANCODE_RIGHT) {
            if (event.type == SDL_KEYDOWN) {
                _right_pressed = true;
            }
            if (event.type == SDL_KEYUP) {
                _right_pressed = false;
            }
        }

        // Only update if the state is not ambiguous (only one key per axis
        // pressed)
        if (!(_left_pressed && _right_pressed)) {
            if (_left_pressed) {
                _dir(0) = -1;
            } else if (_right_pressed) {
                _dir(0) = 1;
            } else {
                _dir(0) = 0;
            }
        }
        if (!(_down_pressed && _up_pressed)) {
            if (_down_pressed) {
                _dir(1) = 1;
            } else if (_up_pressed) {
                _dir(1) = -1;
            } else {
                _dir(1) = 0;
            }
        }
    }
}

}  // namespace engine
}  // namespace coffee