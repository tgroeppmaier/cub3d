#include "cub3D.h"

void	set_path(char *line, t_data *data, Identifier id)
{
	char	**path;

	path = NULL;
	if (id == ID_NO || id == ID_SO || id == ID_WE || id == ID_EA)
	{
		if (id == ID_NO)
			path = &(data->assets->NO_path);
		else if (id == ID_SO)
			path = &(data->assets->SO_path);
		else if (id == ID_WE)
			path = &(data->assets->WE_path);
		else if (id == ID_EA)
			path = &(data->assets->EA_path);
		if (*path == NULL)
			*path = get_config_path(data, line + 3);
		else
			error_exit(data, ERR_IDENT);
	}
}

/* converts char string to unsigned char, moves pointer and checks,
	if the pointer has moved.
	returns value */

unsigned char	get_color_value(t_data *data, char **str)
{
	int		result;
	char	*test;

	test = *str;
	result = 0;
	while (**str >= '0' && **str <= '9')
	{
		result = result * 10 + (**str - '0');
		if (result > 255)
			error_exit(data, ERR_FLOOR_CEILING);
		(*str)++;
	}
	if (*str == test)
		error_exit(data, ERR_FLOOR_CEILING);
	return ((unsigned char)result);
}

/* checks, if the color is already set. if not, it sets the color values */

void	set_color_value(char *line, t_data *data, Identifier id)
{
	t_color	*color;

	if (id == ID_F)
		color = &(data->map->floor);
	else
		color = &(data->map->ceiling);
	if (color->color_ok == true)
		print_error_exit(data, "Error\nColor duplicate");
	color->red = get_color_value(data, &line);
	if (*line != ',')
		error_exit(data, ERR_FLOOR_CEILING);
	line++;
	color->green = get_color_value(data, &line);
	if (*line != ',')
		error_exit(data, ERR_FLOOR_CEILING);
	line++;
	color->blue = get_color_value(data, &line);
	while (ft_isspace(*line))
		line++;
	if (*line != '\0')
		error_exit(data, ERR_FLOOR_CEILING);
	color->color_ok = true;
}

/* when this function is called, *line points to the first character
of the line. After the identifier are 1+n whitespaces */

void	parse_line(char *line, t_data *data, Identifier id)
{
	if (id == ID_NO || id == ID_SO || id == ID_WE || id == ID_EA)
	{
		if (data->map->map_parsing == true)
			print_error_exit(data, "Error\n wrong order\n");
		while (*line && ft_isspace(*line))
			line++;
		set_path(line, data, id);
	}
	else if (id == ID_F || id == ID_C)
	{
		if (data->map->map_parsing == true)
			print_error_exit(data, "Error\n wrong order\n");
		while (*line && ft_isspace(*line)) // skip over whitespace before id
			line++;
		line++;                            // skip over id
		while (*line && ft_isspace(*line)) // skip over whitespace after id
			line++;
		set_color_value(line, data, id);
	}
	else if (id == ID_MAP)
		check_invalid_char(line, data);
	else
		error_exit(data, ERR_IDENT);
}

/* splits the file into lines and saves the ** in data->file
checks, which identifier it is. */

void	parse_file(t_data *data)
{
	int			i;
	Identifier	id;
	char		*line;

	i = -1;
	if (data->file == NULL)
		print_error_exit(data, "Error\nFile not read");
	data->file_by_line = ft_split(data->file, '\n');
	if (data->file_by_line == NULL)
		error_exit(data, ERR_USAGE);
	while (data->file_by_line[++i])
	{
		line = data->file_by_line[i];
		id = get_identifier(line);
		if (id == ID_UNKNOWN)
			error_exit(data, ERR_IDENT);
		if (id == ID_MAP && data->map->map_parsing == false)
		{
			data->map->map_parsing = true;
			data->map->map_start = data->file_by_line + i;
			check_config(data);
		}
		parse_line(line, data, id);
	}
}
