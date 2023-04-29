# 

**Coffee**

2D strategy game

Original idea is faster-paced, less tedious take on XCOM-type titles.  The intent is to simplify the controls and game flow, and maintain high-stakes/sense of loss.  Accomplished by 
- Limited form of permadeth
- Pausable real-time (all game-scapes)
- Smaller squads, greater variety of weapons
- Simplified tactics
- Strategy, without becoming a management sim
- Fewer fine-grained options available to the player.  Variety comes from large-scale decisions and potentially branching story tree.

Easy to pick up, over a cup of coffee.

Basic Engine

A basic demo for building out the engine architecture includes:
- Multiple player controllable entities, and the ability to switch between them w/overlay
- Player can shoot/collide with targets
- [DONE] Simple AI entities that can pursue the player characters
- Basic particle and emitter effect, with player manipulated interactions (ex: attractor or grass)
This should exercise the basic functionality of the ECS and events architectures.  After this, will implement cameras, menus buttons, effects, etc.

Longer Term Features
- animations management and compositing (random blinking during idle, directions, action sequences)
- timers
- mouse control
- pathfinding
- better enemy AI
- map importing
- modifiable terrain
- pauseable-real-time
- pause menu
- 3d rendering layers
- vfx
- particle system and emitters
- representative (placeholder, free) art
- sound (placeholder, free)
- combat system
- stats (weapons, types, player, ai)
- fog of war
- overlay effects
- post-game loot and stats

Longest Term Features
- Overworld game
- combine both games into a single whole

