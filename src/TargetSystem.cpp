/****************************************************************************
 * Coffee
 * Copyright 2023 Eric Dymkoski eric.dymkoski@gmail.com
 * This software is distributed under the MIT license (see ~/License.md)
 ****************************************************************************/

// Targeting system for AI

#include "coffee/TargetSystem.h"

#include "coffee/NpcSystem.h"
#include "coffee/PlayerSystem.h"

namespace coffee {
namespace engine {

void TargetSystem::update(entt::registry &registry, uint64_t dt) {
    // TODO: implement a delay so that this system is not called every frame
    // TODO: make this delay part of the ISystem

    // Get a view to all of the entities that the Npcs might target
    auto playerView = registry.view<PlayerControl, const Position>();

    auto op = [&](auto &ai, auto &pos) {
        // Naive brute forcing to target the nearest Player controllable entity

        entt::entity closest = entt::null;

        float closestDist =
            ai.senseDistance * ai.senseDistance;  // limited sense distance

        for (auto entity : playerView) {
            const auto &playerPos = playerView.get<const Position>(entity);

            const Vec2i vec = playerPos.value - pos.value;
            const Vec2f vecf = vec.template cast<float>();
            // Compute square of the distance
            const float dist = vecf.x() * vecf.x() + vecf.y() * vecf.y();

            if (dist < closestDist) {
                closestDist = dist;
                closest = entity;
            }
        }

        ai.target = closest;
    };

    registry.view<NpcAI, const Position>().each(op);
}

}  // namespace engine
}  // namespace coffee
