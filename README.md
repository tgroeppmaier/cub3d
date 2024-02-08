# cub3d
A 3D graphical project that uses raycasting

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
- [ ] split with ft_split into lines
- [ ] check if all indentifiers are there and no duplicates
- [ ] check if paths are valid
- [ ] save path
- [ ] check if arguments for floor and ceiling is valid 
- [ ] save values

#### Parse Map
- [ ] after all identifiers succesful, start reading map
- [ ] check for invalid characters
##### get map dimensions
- [ ] skip whitespace in the beginning
- [ ] find lenght of longest line



### Status
worked on getting initial whitespace of the map part, but need different approach
due to the whitespace already been skipped when the check_invalid_char function is 
called. Need to check if there is whitespace skipped again unnecessarily
