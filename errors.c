#include "cub3D.h"

void	free_assets(t_data *data)
{
	free(data->assets->NO_path);
	free(data->assets->SO_path);
	free(data->assets->WE_path);
	free(data->assets->EA_path);
}

void	free_file(t_data *data)
{
	int	i;

	i = -1;
	free(data->file);
	data->file = NULL;
	while (data->file_by_line[++i])
	{
		free(data->file_by_line[i]);
		data->file_by_line[i] = NULL;
	}
	free(data->file_by_line);
	data->file_by_line = NULL;
}

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = -1;
	while (array[++i])
	{
		free(array[i]);
		array[i] = NULL;
	}
	free(array);
	array = NULL;
}

void	print_error_exit(t_data *data, char *message)
{
	printf("%s\n", message);
	free_file(data);
	free_assets(data);
	free_array(data->map.map_arr);
	exit(1);
}

void	error_exit(t_data *data, ErrorCode code)
{
	if (code == ERR_FILE_NOT_CUB)
		printf("file is not .cub\n");
	else if (code == ERR_FILE_READ)
		printf("error reading file\n");
	else if (code == ERR_FILE_IS_DIR)
		printf("is directory\n");
	else if (code == ERR_FILE_OPEN)
		printf("error opening file\n");
	else if (code == ERR_FILE_SIZE)
		printf("file too big\n");
	else if (code == ERR_IDENT)
		printf("Identifier error\n");
	else if (code == ERR_FLOOR_CEILING)
		printf("Floor / Ceiling error\n");
	else if (code == ERR_INVALID_MAP)
		printf("Invalid Map\n");
	free_file(data);
	free_assets(data);
	exit(1);
}
