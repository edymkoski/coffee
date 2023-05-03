/****************************************************************************
 * Coffee
 * Copyright 2023 Eric Dymkoski eric.dymkoski@gmail.com
 * This software is distributed under the MIT license (see ~/License.md)
 ****************************************************************************/

// Input handler

#pragma once

#include <cstdint>

#include "coffee/Signal.h"
#include "coffee/components.h"

namespace coffee {
namespace engine {

enum class KeyButton : uint8_t { None, Action, Select, DPad };

struct KeyEvent {
    KeyButton key = KeyButton::None;

    // TODO make this able to change states
    Vec2i8 dir = Vec2i8::Zero();
};

// Input handler
// Designed as a singleton, since the SDL library queue could otherwise be
// emptied by multiple instances, leading to missed events
class InputHandler final {
   public:
    InputHandler(InputHandler& other) = delete;
    void operator=(const InputHandler&) = delete;

    // FIXME: destructor on a singleton
    ~InputHandler();

    //   This is the static method that controls the access to the singleton
    //   instance. On the first run, it creates a singleton object and places it
    //   into the static field. On subsequent runs, it returns the client
    //   existing object stored in the static field.
    static InputHandler* GetInstance();

    // Read all input
    void handleInput();

    // Flag to signal a quit
    bool quit() const { return _quit; }

    // Access to the signal, in order to register slots
    Signal<void(KeyEvent)>& sig() { return _sig; }

   private:
    InputHandler() = default;

    static InputHandler* _singleton;

    // Data state set based on input
    bool _quit = false;

    // Tracking current state of the d-pad, so that a change of one key can be
    // used to form a full event
    bool _upPressed = false;
    bool _downPressed = false;
    bool _leftPressed = false;
    bool _rightPressed = false;

    Signal<void(KeyEvent)> _sig;
};

}  // namespace engine
}  // namespace coffee