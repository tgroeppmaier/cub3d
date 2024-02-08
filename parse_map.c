#include "cub3D.h"

/* first check, if the map part contains any other than the allowded character.
	only checks lines, that start with 1 */

void check_invalid_char(char *line, t_data *data)
{
	int i;

	i = 0;
	// printf("%s", line);
	while(line && ft_isspace(line[i]))
		i++;
	printf("i = %d\n", i);
	if(data->map->line_start == -1)
		data->map->line_start = i;
	else if (i < data->map->line_start)
		data->map->line_start = i;
	while(line[i])
	{
		if(line[i] != ' ' && line[i] != '0' && line[i] != '1' && line[i] != 'N')
			error_exit(data, ERR_INVALID_MAP);
		i++;
	}
}