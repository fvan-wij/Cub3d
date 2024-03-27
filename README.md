# Cub3d (Raycaster in C)
![](https://github.com/fvan-wij/Cub3d_Telestein3D/blob/main/telestein.gif)

## Project description
The aim of this project is to build a dynamic maze which can be explored in first-person similar to the game Wolfenstein 3D.

Further goals of this project:
- Building a robust application with proper error handling, no memory leaks and a decent performance;
- Building a ray-casting engine from scratch using mathematics;
- Use of basic algorithms;

### Resources

Ray-casting tutorial
https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/

### To dos

*Parsing*

- [x] consider skipping non-valid lines while reading the .cub file, check for duplicate elements and decide on appropriate behaviour;
- [ ] check if the colors are in a valid format
- [ ] write a function where I pass an array of characters and check if they are present in a string;
- [x] write a floodfill algorithm to validate the map, decide on a method to check which index has already been checked;
- [x] initialize mlx_textures in the parsing phase;
- [ ] free and terminate the application in a clean way while parsing textures and colors
- [x] avoid passing the main struct to every function and seperate variables instead;
- [x] create seperate vector header?

*Raycaster*

- [x] consider writing the raycaster in a dynamic structure so that it can be used for multiple purposes
- [x] draw a 2d representation of the map
- [x] cast vertical and horizontal ray and determine distance between player and wall
- [x] implement circle-wall collision detection
- [ ] fix bug where circle-wall collision doesn't work for 45 degree angle at corner and refactor collision
- [x] fix overlapping sprites

*Gameplay*
- [ ] Add jumpscares, when entering shack
- [ ] Add Foreshadowing jumpscare po
- [ ] Add jumpscare, tree or shrub
- [ ] Lion roar
- [ ] Po dismemberment mechanic
- [ ] Gasoline / fuel for chainsaw
- [ ] chase soundtrack (danger)
- [ ] Jumpscare sounds
- [ ] Add patrolling BEAR
- [ ] Add Po miniboss
- [ ] Item pickups / Items ( Fuel, Chainsaw)
- [ ] Death mechanic
- [ ] Health stuff
- [ ] Hit stuff
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
- [ ] Add continuous animation for saw + sound.
- [x] Implement textures
- [x] Slither some dither in
- [ ] Minimap should play buzzing sound
- [ ] Add sprites
