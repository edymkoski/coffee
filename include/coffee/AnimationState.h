/****************************************************************************
 * Coffee
 * Copyright 2023 Eric Dymkoski eric.dymkoski@gmail.com
 * This software is distributed under the MIT license (see ~/License.md)
 ****************************************************************************/

// State interface, for a finite state machine

#pragma once

#include <memory>
#include <tuple>

#include "SDL2/SDL.h"
#include "coffee/Assets.h"
#include "entt/entt.hpp"

namespace coffee {
namespace engine {

// FIXME: this is all part of the animation system??

class AnimationState;
using AnimationStatePtr = std::shared_ptr<AnimationState>;

struct Animation {
    AnimationStatePtr animationState;
    SDL_Texture *texture;
};

struct AnimationControl {
    // progressed time, ms
    uint64_t time = 0;
    float timescale = 1.0;
};

// Animation State - plays a sprite animation, and has configurable transitions
// Note: bespoke lib could be replaced with a more full function c++ library
class AnimationState {
   public:
    AnimationState(const entt::resource<engine::SDLFrames> &frames,
                   uint32_t speed);
    virtual ~AnimationState() {}

    // Update componenets affected by this system
    virtual void enter() = 0;
    // FIXME: this signature only works for AnimationStates - how to abstract
    // the interface, but only take specific events 3rd party libs are often
    // defining the inputs/outputs different for different state machines
    virtual std::tuple<Animation, uint64_t> execute(
        const AnimationControl &control, uint64_t dt) = 0;
    virtual void exit() = 0;

   protected:
    SDL_Texture *getFrame(uint64_t currentTime, float timescale);

   private:
    // pointer to frames
    // FIXME: mutable?
    const entt::resource<engine::SDLFrames> _frames;
    const uint32_t _speed;
};

class IdleState : public AnimationState {
   public:
    IdleState(const entt::resource<engine::SDLFrames> &frames, uint32_t speed);
    virtual ~IdleState() {}

    // Update componenets affected by this system
    void enter() override;
    // FIXME: this signature only works for AnimationStates - how to abstract
    // the interface, but only take specific events 3rd party libs are often
    // defining the inputs/outputs different for different state machines
    std::tuple<Animation, uint64_t> execute(const AnimationControl &control,
                                            uint64_t dt) override;

    void exit() override;
};

}  // namespace engine
}  // namespace coffee
