#include "cub3D.h"

/* first check, if the map part contains any other than the allowed character.
	*/

void check_invalid_char(char *line, t_data *data)
{
	int i;

	i = 0;
	while(line[i])
	{
		if(line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W' )
			data->map->p_count++;
		else if(line[i] != ' ' && line[i] != '0' && line[i] != '1')
			error_exit(data, ERR_INVALID_MAP);
		i++;
	}
	data->map->nbr_lines++;
	if (i > data->map->max_line_length)
		data->map->max_line_length = i;
	if(data->map->p_count > 1)
		print_error_exit(data, "Error\nToo many players");
}

bool check_neighbors(char **map, int x, int y, int width, int height)
{
	int i;
	int nx;
	int ny;
	int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
	int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

	i = 0;
	while (i < 8)
	{
		nx = x + dx[i];
		ny = y + dy[i];
		if (nx >= 0 && nx < height && ny >= 0 && ny < width)
		{
			if (map[nx][ny] == '0' || map[nx][ny] == 'N' || map[nx][ny] == 'S' || map[nx][ny] == 'W' || map[nx][ny] == 'E')
				return false;
		}
		i++;
	}
	return true;
}

void set_player_pos(t_data *data, int i, int j, char c)
{
	data->map->player_direction = c;
	data->map->player_x = j;
	data->map->player_y = i;
}

void check_player(t_data *data)
{
	if(data->map->p_count != 1)
		print_error_exit(data, "Error\nWrong Player Count\n");
}

void validate_map(t_data *data)
{
	int i;
	int j;
	char c; 
	
	i = 0;
	while (i < data->map->nbr_lines + 2)
	{
		j = 0;
		while (j < data->map->max_line_length + 2)
		{
			c = data->map->map_arr[i][j];
			if (c == 'x')
			{
				if (!check_neighbors(data->map->map_arr, i, j, data->map->max_line_length + 2, data->map->nbr_lines + 2))
					print_error_exit(data, "Error\nMap not surrounded by walls\n");
			}
			else if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
				set_player_pos(data, i, j, c);
			j++;
		}
		i++;
	}
	check_player(data);
}
