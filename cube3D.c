// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>
// #include <MLX42.h>

// #define WIDTH 512
// #define HEIGHT 512
// #define MAP_SIZE 10
// #define MOVE_SPEED 5

// static mlx_image_t* image;
// static int map[MAP_SIZE][MAP_SIZE] = { /* your map data here */ };
// static int player_x = 0, player_y = 0; // starting position
// static int dir_x = 1, dir_y = 0; // starting direction

// void draw_scene(mlx_t* mlx) {
// 	// For each column of the screen...
// 	for (int x = 0; x < WIDTH; x++) {
// 		// Calculate ray position and direction
// 		double cameraX = 2 * x / (double)WIDTH - 1; // x-coordinate in camera space
// 		double rayDirX = dir_x + cameraX;
// 		double rayDirY = dir_y + cameraX;

// 		// Perform raycasting (simplified)
// 		// You'll need to implement a more complete version of this
// 		int mapX = (int)player_x;
// 		int mapY = (int)player_y;
// 		double sideDistX, sideDistY;
// 		// ... perform DDA algorithm here ...

// 		// Draw the walls
// 		// You'll need to calculate wallX and lineHeight based on the raycast
// 		int lineHeight = HEIGHT / /* distance to wall */;
// 		int drawStart = -lineHeight / 2 + HEIGHT / 2;
// 		int drawEnd = lineHeight / 2 + HEIGHT / 2;
// 		mlx_put_pixel(image, x, drawStart, /* color */);
// 		mlx_put_pixel(image, x, drawEnd, /* color */);
// 	}
// }

// void handle_input(mlx_t* mlx) {
// 	if (mlx_is_key_down(mlx, 'w')) {
// 		player_x += dir_x * MOVE_SPEED;
// 		player_y += dir_y * MOVE_SPEED;
// 	}
// 	if (mlx_is_key_down(mlx, 's')) {
// 		player_x -= dir_x * MOVE_SPEED;
// 		player_y -= dir_y * MOVE_SPEED;
// 	}
// 	if (mlx_is_key_down(mlx, 'a')) {
// 		// rotate direction vector to the left
// 	}
// 	if (mlx_is_key_down(mlx, 'd')) {
// 		// rotate direction vector to the right
// 	}
// }

// int main(void) 
// {
// 	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Raycaster", true);
// 	image = mlx_new_image(mlx, WIDTH, HEIGHT);

// 	while (true) {
// 		handle_input(mlx);
// 		draw_scene(mlx);
// 		mlx_loop(mlx);
// 	}

// 	mlx_terminate(mlx);
// 	return 0;
// }

// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <MLX42.h>

#define WIDTH 512
#define HEIGHT 512

static mlx_image_t* image;

// -----------------------------------------------------------------------------

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void* param)
{
	(void)param;
	for (uint32_t i = 0; i < image->width; ++i)
	{
		for (uint32_t y = 0; y < image->height; ++y)
		{
			uint32_t color = ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);
			mlx_put_pixel(image, i, y, color);
		}
	}
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
}

// -----------------------------------------------------------------------------

int32_t main(void)
{
	mlx_t* mlx;

	// Gotta error check this stuff
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(mlx, 128, 128)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	
	mlx_loop_hook(mlx, ft_randomize, mlx);
	mlx_loop_hook(mlx, ft_hook, mlx);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
