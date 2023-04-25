/****************************************************************************
 * Coffee
 * Copyright 2023 Eric Dymkoski eric.dymkoski@gmail.com
 * This software is distributed under the MIT license (see ~/License.md)
 ****************************************************************************/

// Initial Level demo

#pragma once

#include "coffee/Assets.h"

namespace coffee {

class Level {
   public:
    Level() = default;

    // initialize object
    void initialize();

    // update the state of the level
    void update();

   private:
    // FIXME: should this really have its own asset manager?  or should it
    // receive assets from the client for better long-term management?
    engine::Sprites _spriteManager;
};

}  // namespace coffee