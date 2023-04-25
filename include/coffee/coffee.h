/****************************************************************************
 * Coffee
 * Copyright 2023 Eric Dymkoski eric.dymkoski@gmail.com
 * This software is distributed under the MIT license (see ~/License.md)
 ****************************************************************************/

// Coffee engine top-level functionality

#pragma once

namespace coffee {
namespace engine {

// Initialize the coffee engine - typically called once at the beginning of the game
// Returns a bool to indicate if initialization was successful
bool initialize();

// Finalize the coffee engine - typically called once before program exit
void finalize();

}  // namespace engine
}  // namespace coffee