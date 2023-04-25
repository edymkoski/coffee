/****************************************************************************
 * Tesseract: Numerics library
 * Copyright 2021 Eric Dymkoski ericbrownd@hotmail.com
 * This software is distributed under the MIT license (see ~/License.md)
 ****************************************************************************/

/// Error throwing macros

#pragma once

#include <exception>
#include <sstream>
#include <stdexcept>

#include "fmt/core.h"

namespace coffee {

#define THROW_EXCEPT(EXCEPTION_TYPE, ...)           \
    throw EXCEPTION_TYPE(fmt::format(__VA_ARGS__) + \
                         fmt::format(": {}:{}", __FILE__, __LINE__))

#define COFFEE_CHECK(EXPRESSION, EXCEPTION_TYPE, ...) \
    if (!(EXPRESSION)) {                              \
        THROW_EXCEPT(EXCEPTION_TYPE, __VA_ARGS__);    \
    }

}  // namespace coffee