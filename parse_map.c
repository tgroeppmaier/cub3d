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