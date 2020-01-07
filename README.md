# attackalantus

## Installation
Within the team11 directory:
```
mkdir build; cd build;
CMAKE ../ -DCMAKE_BUILD_TYPE=Release
make
./attackAtlantus
```

## Controls
- WASD Keys to move
- Spacebar to attack
- Mouse for ability direction and mouse left click for ability activation
## Story
Deep in the ocean, something horrible has emerged: the forces of Atlantis are waging war upon humanity. Once a lowly beach bum, you are forced to fight through hordes of sea monsters in order to defend your home. The game will have around 5 - 10 stages (levels). In order for the player to clear all stages, the player needs to defeat all minions and boss(es) to pick up the key to unlock the next stage. 
## Core game design elements
## Rendering
The background for the game will be rendered as a stationary top-down 2D plane. We plan to vary the background image when we create different stages. There will be five main types of entities that need to be rendered: 
The player
An enemy
An item/skill
Obstacles
Projectiles
## Assets (geometry, sprites, audio, etc.)
We plan to use sprites for most of our graphical assets. We plan to have simple animations for abilities. For audio, we would like simple, pleasant, battle music, sounds for dealing/taking damage, death sounds, and ability pickup sounds.
## 2D geometry manipulation (transformation, collisions, etc.)
We will have translations for each entity listed in the rendering section. There will be many collision checks, as we need to check for touching enemies, projectiles, and items. Additionally, we would like to implement various space transformations as items.
## Gameplay logic/AI
The core gameplay will be surviving as enemies periodically spawn from specified locations and attempt to attack the player. There will be various items/power-ups spawning in random locations, forcing the player to make strategic decisions regarding whether they should risk trying to go pick up the item, and when they should use the item once it’s picked up. The enemies will have a basic AI, following the player and trying to kill them. Different types of enemies may have different AIs; some will shoot projectiles while others may have erratic movement. After surviving a certain period of time, the player will need to defeat a boss in order to complete the stage.
## Physics
We will have basic projectile physics. We are also likely to rely on physics for certain abilities, for example, a weapon that moves in curves or an ability pushing/pulling enemies in certain directions.


## Reference:
    Sound: Willlewis, Abyssmal, ethanchase7744 and jalastram from freesound.org and gg from https://www.myinstants.com/instant/gg/
           NeoSpica, 89o, Michel88, Christopherderp, rhodesmas, LittleRobotSoundFactory, sheyvan, Robinhood76, UsuarioLeal
    Boomerang: https://opengameart.org/content/boomerang-bullet
    Meteor: https://imgbin.com/png/kz89Xz1Z/computer-icons-meteoroid-png
## License
[MIT](https://choosealicense.com/licenses/mit/)
