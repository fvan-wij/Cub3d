# Cub3d (Raycaster in C)

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
- [ ] create seperate vector header?

*Raycaster*

- [ ] consider writing the raycaster in a dynamic structure so that it can be used for multiple purposes
- [x] draw a 2d representation of the map
- [x] cast vertical and horizontal ray and determine distance between player and wall
- [x] implement circle-wall collision detection
- [ ] fix bug where circle-wall collision doesn't work for 45 degree angle at corner
