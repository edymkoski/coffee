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

InputHandler::~InputHandler() {}

InputHandler* InputHandler::_singleton = nullptr;

InputHandler* InputHandler::GetInstance() {
    //  This is a safer way to create an instance. instance = new InputHandler
    //  is dangerous in case two instance threads wants to access at the same
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

        // State switch
        if (scancode == SDL_SCANCODE_SPACE && event.type == SDL_KEYDOWN) {
            // Emit a keyboard event
            KeyEvent keyEvent;
            keyEvent.key = KeyButton::Action;

            _sig(keyEvent);
        }

        // Mouse motion
        // Will record and emit only the final mouse state
        // if (event.type == SDL_MOUSEMOTION) {
        //     const int x = event.motion.x;
        //     const int y = event.motion.y;
        //     printf("Mouse: %d, %d\n", x, y);
        // }

        // D-pad
        // FIXME: use correct variable casing
        bool dpadChanged = false;
        if (scancode == SDL_SCANCODE_UP) {
            if (event.type == SDL_KEYDOWN) {
                _upPressed = true;
                dpadChanged = true;
            }
            if (event.type == SDL_KEYUP) {
                _upPressed = false;
                dpadChanged = true;
            }
        }

        if (scancode == SDL_SCANCODE_DOWN) {
            if (event.type == SDL_KEYDOWN) {
                _downPressed = true;
                dpadChanged = true;
            }
            if (event.type == SDL_KEYUP) {
                _downPressed = false;
                dpadChanged = true;
            }
        }

        if (scancode == SDL_SCANCODE_LEFT) {
            if (event.type == SDL_KEYDOWN) {
                _leftPressed = true;
                dpadChanged = true;
            }
            if (event.type == SDL_KEYUP) {
                _leftPressed = false;
                dpadChanged = true;
            }
        }

        if (scancode == SDL_SCANCODE_RIGHT) {
            if (event.type == SDL_KEYDOWN) {
                _rightPressed = true;
                dpadChanged = true;
            }
            if (event.type == SDL_KEYUP) {
                _rightPressed = false;
                dpadChanged = true;
            }
        }

        // Only update if the state is not ambiguous (only one key per axis
        // pressed)
        if (dpadChanged) {
            Vec2i8 dir = Vec2i8::Zero();

            if (!(_leftPressed && _rightPressed)) {
                if (_leftPressed) {
                    dir(0) = -1;
                } else if (_rightPressed) {
                    dir(0) = 1;
                } else {
                    dir(0) = 0;
                }
            }
            if (!(_downPressed && _upPressed)) {
                if (_downPressed) {
                    dir(1) = 1;
                } else if (_upPressed) {
                    dir(1) = -1;
                } else {
                    dir(1) = 0;
                }
            }

            // Emit a keyboard event for dpad
            KeyEvent keyEvent;
            keyEvent.key = KeyButton::DPad;
            keyEvent.dir = dir;

            _sig(keyEvent);
        }
    }
}

}  // namespace engine
}  // namespace coffee