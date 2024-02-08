#include "include/cub3D.h"

// void print_color(t_color color) 
// {
// 	printf("Red: %u, Green: %u, Blue: %u\n", color.red, color.green, color.blue);
// 	printf("Red OK: %d, Green OK: %d, Blue OK: %d\n", color.red_ok, color.green_ok, color.blue_ok);
// }

void print_color(t_color color) 
{
	printf("Red: %u, Green: %u, Blue: %u\n", color.red, color.green, color.blue);
	printf("R_OK: %s, G_OK: %s, B_OK: %s\n", color.red_ok ? "true" : "false", color.green_ok ? "true" : "false", color.blue_ok ? "true" : "false");
}

void print_map(t_map *map) 
{
	printf("Floor color: ");
	print_color(map->floor);
	printf("Ceiling color: ");
	print_color(map->ceiling);
	// Add code here to print the map data if needed
}

void print_asset(t_asset *asset) 
{
	printf("NO path: %s\n", asset->NO_path);
	printf("SO path: %s\n", asset->SO_path);
	printf("WE path: %s\n", asset->WE_path);
	printf("EA path: %s\n", asset->EA_path);
}

void print_data(t_data *data)
{
	// printf("File: %s\n", data->file);
	// Add code here to print the file_by_line if needed
	print_asset(data->assets);
	print_map(data->map);
}