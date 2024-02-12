#include "cub3D.h"

char *create_boundary_line(int line_length)
{
	char* line = (char *)malloc((line_length + 1) * sizeof(char));
	if (!line)
	{
		return NULL;
	}
	ft_memset(line, 'x', line_length);
	line[line_length] = '\0';
	return line;
}

char *create_map_line(t_data* data, int index, int line_length)
{
	int remaining_len;
	int j;
	
	char *line = (char *)malloc((line_length + 1) * sizeof(char));
	if (!line)
	{
		return NULL;
	}
	line[0] = 'x';
	ft_strlcpy(line + 1, data->map->map_start[index], line_length - 1);
	remaining_len = line_length - ft_strlen(line);
	ft_memset(line + ft_strlen(line), 'x', remaining_len);
	line[line_length - 1] = 'x';
	line[line_length] = '\0';

	// Replace all spaces with 'x'
	j = 0;
	while (line[j])
	{
		if (line[j] == ' ')
			line[j] = 'x';
		j++;
	}

	return line;
}

void create_map(t_data *data)
{
	int i;
	int map_width;
	int map_height;

	i = 0;
	map_width = data->map->max_line_length + 2;
	map_height = data->map->nbr_lines + 2;
	char **map = (char **)malloc((map_height + 1) * sizeof(char *));
	if (!map)
		return; // todo
	map[0] = create_boundary_line(map_width);
	while(i < map_height - 2)
	{
		map[i + 1] = create_map_line(data, i, map_width);
		if (!map[i + 1])
		{
			while (--i >= 0)
				free(map[i]);
			free(map);
			return; // todo
		}
		i++;
	}
	map[map_height - 1] = create_boundary_line(map_width);
	map[map_height] = NULL;
	data->map->map_arr = map;

	if(!validate_map(data))
		print_error_exit(data, "Error\nMap not surrounded by walls\n");
}
