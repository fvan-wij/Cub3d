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

*Gameplay* (Dark_Secret)
- [x] Add Foreshadowing jumpscare po
- [x] Add jumpscare, tree or shrub
- [ ] Lion roar
- [x] Po dismemberment mechanic
- [x] Gasoline / fuel for chainsaw
- [x] chase soundtrack (danger)
- [x] Jumpscare sounds
- [ ] Add patrolling BEAR
- [x] Add finishing move on Po
- [x] Add exit on Dome entrance
- [ ] Add kick
- [ ] Add near death overlay
- [x] Add end screen
- [ ] Add destructibles
- [ ] Add health indicator
- [ ] Door should be more obvious
- [ ] Add sprite with controls
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
- [ ] Minimap should play buzzing sound
- [x] Add sprites


### Credits
Music and sounddesign produced and composed by Flip van Wijk

Chainsaw Sound:
Sound Effect by <a href="https://pixabay.com/users/u_zpj3vbdres-31862813/?utm_source=link-attribution&utm_medium=referral&utm_campaign=music&utm_content=128369">u_zpj3vbdres</a> from <a href="https://pixabay.com/sound-effects//?utm_source=link-attribution&utm_medium=referral&utm_campaign=music&utm_content=128369">Pixabay</a>

Pickup Sound:
Sound Effect from <a href="https://pixabay.com/?utm_source=link-attribution&utm_medium=referral&utm_campaign=music&utm_content=37089">Pixabay</a>

Sound Effect by <a href="https://pixabay.com/users/soundreality-31074404/?utm_source=link-attribution&utm_medium=referral&utm_campaign=music&utm_content=128320">Jurij</a> from <a href="https://pixabay.com//?utm_source=link-attribution&utm_medium=referral&utm_campaign=music&utm_content=128320">Pixabay</a>

Sound Effect by <a href="https://pixabay.com/users/soundsforyou-4861230/?utm_source=link-attribution&utm_medium=referral&utm_campaign=music&utm_content=129073">Mikhail</a> from <a href="https://pixabay.com//?utm_source=link-attribution&utm_medium=referral&utm_campaign=music&utm_content=129073">Pixabay</a>
