/****************************************************************************
 * Coffee
 * Copyright 2023 Eric Dymkoski eric.dymkoski@gmail.com
 * This software is distributed under the MIT license (see ~/License.md)
 ****************************************************************************/

// Animation states for an animation control graph

#include "coffee/AnimationState.h"

namespace coffee {
namespace engine {

AnimationState(const entt::resource<engine::SDLFrames> &frames, uint32_t speed)
    : _frames(frames), _speed(speed) {}

// Mutable
SDL_Texture *AnimationState::getFrame(uint64_t currentTime, float timescale) {
    // FIXME: needs to receive this through the call to the function
    uint64_t idx = timescale * currentTime / (_speed);

    SDL_Texture *tex = _frames->operator[](idx);

    return tex;
}

IdleState::IdleState(const entt::resource<engine::SDLFrames> &frames,
                     uint32_t speed)
    : AnimationState(frames, speed) {}

// Update componenets affected by this system
void IdleState::enter(){};
// FIXME: this signature only works for AnimationStates - how to abstract
// the interface, but only take specific events 3rd party libs are often
// defining the inputs/outputs different for different state machines
std::tuple<Animation, uint64_t> IdleState::execute(
    const AnimationControl &control, uint64_t dt) {
    // Compute the end time
    const uint64_t endTime = dt + control.time;

    // make sure it loops properly
    const uint32_t length = _frames->size() * _speed / timescale;

    endTime %= length;

    SDL_Texture *tex = getFrame(endTime, timescale);

    Animation out;
    out.animationState = this;
    out.texture = tex;

    return {out, endTime};

    // FIXME: update state here, triggering any needed transition
}
void IdleState::exit() {}

}  // namespace engine
}  // namespace coffee
