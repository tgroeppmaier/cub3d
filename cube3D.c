#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <MLX42.h>

#define WIDTH 512
#define HEIGHT 512
#define MAP_SIZE 10
#define MOVE_SPEED 5

static mlx_image_t* image;
static int map[MAP_SIZE][MAP_SIZE] = { /* your map data here */ };
static int player_x = 0, player_y = 0; // starting position
static int dir_x = 1, dir_y = 0; // starting direction

void draw_scene(mlx_t* mlx) {
	// For each column of the screen...
	for (int x = 0; x < WIDTH; x++) {
		// Calculate ray position and direction
		double cameraX = 2 * x / (double)WIDTH - 1; // x-coordinate in camera space
		double rayDirX = dir_x + cameraX;
		double rayDirY = dir_y + cameraX;

		// Perform raycasting (simplified)
		// You'll need to implement a more complete version of this
		int mapX = (int)player_x;
		int mapY = (int)player_y;
		double sideDistX, sideDistY;
		// ... perform DDA algorithm here ...

		// Draw the walls
		// You'll need to calculate wallX and lineHeight based on the raycast
		int lineHeight = HEIGHT / /* distance to wall */;
		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		mlx_put_pixel(image, x, drawStart, /* color */);
		mlx_put_pixel(image, x, drawEnd, /* color */);
	}
}

void handle_input(mlx_t* mlx) {
	if (mlx_is_key_down(mlx, 'w')) {
		player_x += dir_x * MOVE_SPEED;
		player_y += dir_y * MOVE_SPEED;
	}
	if (mlx_is_key_down(mlx, 's')) {
		player_x -= dir_x * MOVE_SPEED;
		player_y -= dir_y * MOVE_SPEED;
	}
	if (mlx_is_key_down(mlx, 'a')) {
		// rotate direction vector to the left
	}
	if (mlx_is_key_down(mlx, 'd')) {
		// rotate direction vector to the right
	}
}

int main(void) {
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Raycaster", true);
	image = mlx_new_image(mlx, WIDTH, HEIGHT);

	while (true) {
		handle_input(mlx);
		draw_scene(mlx);
		mlx_loop(mlx);
	}

	mlx_terminate(mlx);
	return 0;
}