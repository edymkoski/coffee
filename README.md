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
- Multiple player controllable entities, and the ability to switch between them
- Player can shoot/collide with targets
- Simple AI entities that can pursue the player characters
- Basic particle effect, with player manipulated interactions (ex: attractor)
This should exercise the basic functionality of the ECS and events architectures.  After this, will implement cameras, menus buttons, effects, etc.

