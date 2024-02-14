#include "cub3D.h"

void	check_config(t_data *data)
{
	if (!data->assets->NO_path || !data->assets->SO_path
		|| !data->assets->WE_path || !data->assets->EA_path)
		print_error_exit(data, "Error\nasset path error");
	if (!data->map->ceiling.color_ok || !data->map->floor.color_ok)
		print_error_exit(data, "Error\ncolor error");
}

Identifier	get_identifier(char *str)
{
	while (*str && ft_isspace(*str))
		str++;
	if (ft_strncmp(str, "NO ", 3) == 0)
		return (ID_NO);
	if (ft_strncmp(str, "SO ", 3) == 0)
		return (ID_SO);
	if (ft_strncmp(str, "WE ", 3) == 0)
		return (ID_WE);
	if (ft_strncmp(str, "EA ", 3) == 0)
		return (ID_EA);
	if (ft_strncmp(str, "F ", 2) == 0)
		return (ID_F);
	if (ft_strncmp(str, "C ", 2) == 0)
		return (ID_C);
	if (ft_strncmp(str, "1", 1) == 0)
		return (ID_MAP);
	return (ID_UNKNOWN);
}

char	*get_config_path(t_data *data, char *line)
{
	int	i;
	int	len;
	int	start;

	i = 0;
	len = ft_strlen(line);
	while (i < len && ft_isspace(line[i]))
		i++;
	start = i;
	while (i < len && !ft_isspace(line[i]))
		i++;
	if (i == start)
		error_exit(data, ERR_IDENT);
	return (ft_strndup(line + start, i - start));
}
