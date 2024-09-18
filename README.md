# Telestein3D/Cub3d (Raycaster in C)
Telestein3D or Cub3d (based of 42's project 'Cub3d') is a demo of a horror game that can be explored in first-person similar to the game Wolfenstein 3D.
Additionally, this project has been turned into a fully fledged demo, including combat, audio and more.
Further goals of this project:
- Building a ray-casting engine from scratch using mathematics;
- Use of basic algorithms;
- Custom sprites and sound-effects and music;
- A basic game-loop;

## About Telestein3D
The Teletubbies have taken your children and your life turns into a literal nightmare. You're on a mission to take revange and discover some truly dark secrets...

## Installation
1 Download/clone this repository
2 Open up a terminal, CD into the root directory of Telestein3D and use the 'make' command
3 Let it build...
4 Run the game by booting the binary: './Telestein3D'
5 No additional arguments are required

## Controls
_Player movement:_
Walk: W,A,S,D
Turn around: LEFT-ARROW / RIGHT-ARROW
Sprint: SHIFT

_Combat/Inventory:_
Attack: SPACE
Map: M
Fists: 1
Chainsaw: 2

### Resources
Ray-casting tutorial
https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/

### Features

*Parsing*
- [x] consider skipping non-valid lines while reading the .cub file, check for duplicate elements and decide on appropriate behaviour;
- [x] check if the colors are in a valid format
- [x] write a function where I pass an array of characters and check if they are present in a string;
- [x] write a floodfill algorithm to validate the map, decide on a method to check which index has already been checked;
- [x] initialize mlx_textures in the parsing phase;
- [x] free and terminate the application in a clean way while parsing textures and colors
- [x] avoid passing the main struct to every function and seperate variables instead;
- [x] create seperate vector header?

*Raycaster*

- [x] consider writing the raycaster in a dynamic structure so that it can be used for multiple purposes
- [x] draw a 2d representation of the map
- [x] cast vertical and horizontal ray and determine distance between player and wall
- [x] implement circle-wall collision detection
- [ ] fix bug where circle-wall collision doesn't work for 45 degree angle at corner and refactor collision
- [x] fix overlapping sprites

*Gameplay* (Dark_Secret)
- [x] Add Foreshadowing jumpscare po
- [x] Add jumpscare, tree or shrub
- [x] Po dismemberment mechanic
- [x] Gasoline / fuel for chainsaw
- [x] chase soundtrack (danger)
- [x] Jumpscare sounds
- [x] Add finishing move on Po
- [x] Add exit on Dome entrance
- [x] Add end screen
- [x] Add health indicator
- [x] Add Po miniboss
- [x] Item pickups / Items ( Fuel, Chainsaw)
- [x] Death mechanic
- [x] Health stuff
- [x] Hit stuff
- [x] Add destructible walls

*Features*
- [x] Improve immersion by adding headbobbing on the Y-axis
- [x] Improve immersion by adding headbobbing to the hands on the X and Y-axis
- [x] Pressing M opens the map
- [x] Add dust particles
- [x] Add Po player-centered minimap
- [x] Add ambient soundtrack
- [x] Add menu soundtrack
- [x] Add event triggered sound
- [x] Add saw and smashing animations
- [x] Add continuous animation for saw + sound.
- [x] Implement textures
- [x] Slither some dither in
- [x] Add sprites

### Credits
Music, sounddesign and art by Flip van Wijk
Technical lead: Duco Ritsema

### Other sounds I did not create
Chainsaw Sound:
Sound Effect by <a href="https://pixabay.com/users/u_zpj3vbdres-31862813/?utm_source=link-attribution&utm_medium=referral&utm_campaign=music&utm_content=128369">u_zpj3vbdres</a> from <a href="https://pixabay.com/sound-effects//?utm_source=link-attribution&utm_medium=referral&utm_campaign=music&utm_content=128369">Pixabay</a>

Pickup Sound:
Sound Effect from <a href="https://pixabay.com/?utm_source=link-attribution&utm_medium=referral&utm_campaign=music&utm_content=37089">Pixabay</a>

Sound Effect by <a href="https://pixabay.com/users/soundreality-31074404/?utm_source=link-attribution&utm_medium=referral&utm_campaign=music&utm_content=128320">Jurij</a> from <a href="https://pixabay.com//?utm_source=link-attribution&utm_medium=referral&utm_campaign=music&utm_content=128320">Pixabay</a>

Sound Effect by <a href="https://pixabay.com/users/soundsforyou-4861230/?utm_source=link-attribution&utm_medium=referral&utm_campaign=music&utm_content=129073">Mikhail</a> from <a href="https://pixabay.com//?utm_source=link-attribution&utm_medium=referral&utm_campaign=music&utm_content=129073">Pixabay</a>
