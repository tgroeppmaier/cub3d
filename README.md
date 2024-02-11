<h1>cub3D</h1>

A 3D graphical project that uses raycasting

- [useful links](#useful-links)
- [steps to use the library](#steps-to-use-the-library)
- [To Do](#to-do)
	- [Checking Arguments](#checking-arguments)
	- [Parsing](#parsing)
		- [Parse configuration](#parse-configuration)
		- [Parse Map](#parse-map)
		- [Map check](#map-check)
			- [get map dimensions](#get-map-dimensions)
	- [Status](#status)
	- [progress](#progress)

## useful links

- Raycasting https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/
- Raycasting https://lodev.org/cgtutor/raycasting.html
- Movement https://gamecodeschool.com/essentials/calculating-heading-in-2d-games-using-trigonometric-functions-part-1/

## steps to use the library

- Install glfw https://www.glfw.org/download.html using package manager or compiling from source
- install cmake
- clone https://github.com/codam-coding-college/MLX42.git
- build ```code
cmake -B build && cmake --build build --parallel --config (Debug|Release|RelWithDebInfo|MinSizeRel) --target install```
- run tests

```bash
cmake -DBUILD_TESTS=ON -B build && cmake --build build --parallel
ctest --output-on-failure --test-dir build
```

- compile with `gcc cube3D.c libmlx42.a -Iinclude -ldl -lglfw -pthread -lm`

## To Do

### Checking Arguments

- [x] check no of Arguments == 2
- [x] check for .cub ending
- [x] check if its directory
- [x] read file into buffer

### Parsing

#### Parse configuration

- [x] split with ft_split into lines
- [x] check if all indentifiers are there and no duplicates
- [ ] check if paths are valid
- [x] save path
- [x] check if arguments for floor and ceiling is valid 
- [x] save values

#### Parse Map

- Map part start with 1 in the beginning.
- when 1 is encountered id = MAP
- check if all configs are set and check map part for invalid characters

- [ ] after all identifiers succesful, start reading map
- [ ] check for invalid characters

#### Map check

- The map must be composed of only 6 possible characters: 0 for an empty space, 1 for a wall, and N,S,E or W for the player`s start position and spawning orientation.
- The map must be closed/surrounded by walls, if not the program must return an error.
- Map cannot contain empty lines
- Map must come after all Identifiers
- Spaces are a valid part of the map and up to us to handle. We treat spaces as walls.


##### get map dimensions

- [ ] skip whitespace in the beginning
- [ ] find lenght of longest line

### Status

worked on getting initial whitespace of the map part, but need different approach
due to the whitespace already been skipped when the check_invalid_char function is called. Need to check if there is whitespace skipped again unnecessarily

10.02.

- create_map function needs to start reading from the map part of the file

11.02.

- finish create map and map check

### progress
