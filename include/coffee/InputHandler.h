/****************************************************************************
 * Coffee
 * Copyright 2023 Eric Dymkoski eric.dymkoski@gmail.com
 * This software is distributed under the MIT license (see ~/License.md)
 ****************************************************************************/

// Input handler

#pragma once

#include "coffee/components.h"

namespace coffee {
namespace engine {

// Input handler
// Designed as a singleton, since the SDL library queue could otherwise be
// emptied by multiple instances, leading to missed events
class InputHandler final {
   public:
    InputHandler(InputHandler& other) = delete;
    void operator=(const InputHandler&) = delete;

    //   This is the static method that controls the access to the singleton
    //   instance. On the first run, it creates a singleton object and places it
    //   into the static field. On subsequent runs, it returns the client
    //   existing object stored in the static field.
    static InputHandler* GetInstance();

    // Read all input
    void handleInput();

    // Flag to signal a quit
    bool quit() const { return _quit; }

    const Vec2i& directionInput() const { return _dir; }

   private:
    InputHandler() = default;

    static InputHandler* _singleton;

    // Data state set based on input
    bool _quit = false;
    Vec2i _dir = Vec2i::Zero();

    bool _up_pressed = false;
    bool _down_pressed = false;
    bool _left_pressed = false;
    bool _right_pressed = false;
};

}  // namespace engine
}  // namespace coffee