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
`bash
cmake -DBUILD_TESTS=ON -B build && cmake --build build --parallel
ctest --output-on-failure --test-dir build
`
- compile with `gcc cube3D.c libmlx42.a -Iinclude -ldl -lglfw -pthread -lm`