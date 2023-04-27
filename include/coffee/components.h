/****************************************************************************
 * Coffee
 * Copyright 2023 Eric Dymkoski eric.dymkoski@gmail.com
 * This software is distributed under the MIT license (see ~/License.md)
 ****************************************************************************/

// Animation components and system

#pragma once

#include <cstdint>

#include "Eigen/Core"

namespace coffee {
namespace engine {

using Vec2f = Eigen::Vector<float, 2>;
using Vec2u = Eigen::Vector<uint32_t, 2>;
using Vec2i = Eigen::Vector<int32_t, 2>;

// Position component
// Note: position is given as an int in order to not have roundoff errors at
// large values
using Position = Vec2i;

// Velocity component
// Note: velocity is given as an int in order to not have roundoff errors at
// large values
using Position = Vec2i;

}  // namespace engine
}  // namespace coffee
