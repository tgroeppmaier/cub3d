#include "cub3D.h"

/* first check, if the map part contains any other than the allowded character.
	only checks lines, that start with 1 */

void check_invalid_char(char *line, t_data *data)
{
	int i;

	i = 0;
	while(line[i])
	{
		if(line[i] != ' ' && line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
			error_exit(data, ERR_INVALID_MAP);
		i++;
	}
	data->map->nbr_lines++;
	if (i > data->map->max_line_length)
		data->map->max_line_length = i;

}


bool check_neighbors(char **map, int x, int y, int width, int height)
{
	int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
	int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
	int i;

	for (i = 0; i < 8; i++)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (nx >= 0 && nx < height && ny >= 0 && ny < width)
		{
			if (map[nx][ny] == '0' || map[nx][ny] == 'N' || map[nx][ny] == 'S' || map[nx][ny] == 'W' || map[nx][ny] == 'E')
			{
				return false;
			}
		}
	}

	return true;
}

bool validate_map(t_data *data)
{
	int i, j;

	for (i = 0; i < data->map->nbr_lines + 2; i++)
	{
		for (j = 0; j < data->map->max_line_length + 2; j++)
		{
			if (data->map->map_arr[i][j] == 'x')
			{
				if (!check_neighbors(data->map->map_arr, i, j, data->map->max_line_length + 2, data->map->nbr_lines + 2))
				{
					return false;
				}
			}
		}
	}

	return true;
}