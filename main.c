#include "cub3D.h"


void initialization(t_data* data, t_asset* assets, t_map* map)
{
	ft_memset(data, 0, sizeof(*data));
	ft_memset(assets, 0, sizeof(*assets));
	ft_memset(map, 0, sizeof(*map));
	data->map = map;
	data->assets = assets;
	// map->ceiling.color_ok = false;
	// map->floor.color_ok = false;
	// data->map->map_parsing = false;
	// data->map->nbr_lines = 0;
	// data->map->nbr_lines = 0;
}

void create_map(t_data *data)
{
	int i;
	int x;
	int y;
	char **map;

	i = 0;
	x = data->map->max_line_length;
	y = data->map->nbr_lines;
	map = (char **)malloc((y + 1) * sizeof(char *));
	while(i < y)
	{
		map[i] = (char *)malloc((x + 1) * sizeof(char));
		ft_strlcpy(map[i], data->file_by_line[i], x);
		// map[i][x] = '\0';
		i++;
	}
	map[y] = NULL;
	i = 0;
    char **map_ptr = map;
    while(*map_ptr)
    {
        printf("%s\n", *map_ptr);
        map_ptr++;
    }
	free_array(map);
}

int main(int argc, char **argv)
{
	t_data	data;
	t_asset	assets;
	t_map	map;

	initialization(&data, &assets, &map);
	check_argument(argc, argv);
	read_file(argv[1], &data);
	// printf("%s\n", data.buffer);
	parse_file(&data);
	check_config(&data);
	create_map(&data);
	// print_data(&data);
	free_file(&data);
	free_assets(&data);
	return(0);
}