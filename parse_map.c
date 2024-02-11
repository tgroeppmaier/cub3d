#include "cub3D.h"

/* first check, if the map part contains any other than the allowded character.
	only checks lines, that start with 1 */

void check_invalid_char(char *line, t_data *data)
{
	int i;

	i = 0;
	while(line && ft_isspace(line[i]))
	{
		line[i] = '1';
		i++;
	}
	while(line[i])
	{
		if(line[i] == ' ')
			line[i] = '1';
		if(line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
			error_exit(data, ERR_INVALID_MAP);
		i++;
	}
	data->map->nbr_lines++;
	if (i > data->map->max_line_length)
		data->map->max_line_length = i;

}

/*  Finds the line number where the map content starts */

int find_map_start(t_data *data)
{
	int i;
	Identifier id;

	i = 0;
	while(data->file_by_line[i])
	{
		id = get_identifier(data->file_by_line[i]);
		if(id == ID_MAP)
			break;
		i++;
	}
	return i;
}

/*  Allocates and initializes a map line  */

char *create_map_line(t_data* data, int index, int line_length)
{
	int remaining_len;
	
	char* line = (char *)malloc((line_length + 1) * sizeof(char));
	if (!line)
	{
		return NULL;
	}
	ft_strlcpy(line, data->file_by_line[index], line_length);
	remaining_len = line_length - ft_strlen(line);
	ft_memset(line + ft_strlen(line), '1', remaining_len);
	line[line_length] = '\0';
	return line;
}

/*  Creates the map from the file content */

void create_map(t_data *data)
{
	int i;
	int map_width;
	int map_height;
	int start_line;

	i = 0;
	map_width = data->map->max_line_length;
	map_height = data->map->nbr_lines;
	start_line = find_map_start(data);
	char **map = (char **)malloc((map_height + 1) * sizeof(char *));
	if (!map)
		return; // todo
	while(i < map_height)
	{
		map[i] = create_map_line(data, start_line + i, map_width);
		if (!map[i])
		{
			while (--i >= 0)
				free(map[i]);
			free(map);
			return; // todo
		}
		i++;
	}
	map[map_height] = NULL;
	data->map->map_arr = map;
}
