#include "include/cub3D.h"
#include <fcntl.h>

static bool	is_dir(char *path)
{
	int		fd;
	bool	ret;

	ret = false;
	fd = open(path, O_DIRECTORY);
	if (fd >= 0)
	{
		close (fd);
		ret = true;
	}
	return (ret);
}

void	check_argument(int argc, char **argv)
{
	int	len;

	if (argc != 2)
	{
		printf("Error\n");
		printf("usage: ./cub3D mapname.cub\n");
		exit(1);
	}
	len = ft_strlen(argv[1]);
	if (len < 4)
	{
		printf("filename too short\n");
		exit(1);
	}
	if (ft_strncmp(argv[1] + len - 4, ".cub", 4) != 0)
	{
		printf("Error\n");
		printf("wrong filename! use .cub\n");
		exit(1);
	}
	if (is_dir(argv[1]))
		exit(1);
}

/*
	opens file and reads it into data->file.
*/

void	read_file(char *path, t_data *data)
{
	int	fd;
	int	bytes_read;
	char *buffer;
	char *tmp = NULL;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if(!buffer)
		error_exit(data, ERR_MALLOC);
	data->file = ft_strdup("");
	if(!data->file)
	{
		free(buffer);
		error_exit(data, ERR_MALLOC);
	}

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		free(buffer);
		error_exit(data, ERR_FILE_OPEN);
	}
	while((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[bytes_read] = '\0';
		tmp = ft_strjoin(data->file, buffer);
		free(data->file);  // free the old string
		data->file = ft_strdup(tmp);  // assign the new string
		free(tmp);
	}
	if (bytes_read == -1)
	{
		free(buffer);
		close(fd);
		error_exit(data, ERR_FILE_READ);
	}
	close(fd);
	free(buffer);  // free the buffer
}

bool ft_isspace(int c) 
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

// void get_config_data(t_data *data, char *line, Identifier id)
// {
// 	int i = 0;
// 	int len = ft_strlen(line);
	
// 	while(i < len && ft_isspace(line[i]))
// 		i++;
// 	while(i < len && !ft_isspace(line[i]))
// 		i++;
// 	if(i == 0)
// 		error_exit(data, ERR_IDENT);
	
// 	char **path = NULL;
	
// 	if (id == ID_NO)
// 		path = &(data->assets->NO_path);
// 	else if (id == ID_SO)
// 		path = &(data->assets->SO_path);
// 	else if (id == ID_WE)
// 		path = &(data->assets->WE_path);
// 	else if (id == ID_EA)
// 		path = &(data->assets->EA_path);
// 	else
// 		error_exit(data, ERR_IDENT);
	
// 	if(*path == NULL)
// 		*path = ft_strndup(line, i);
// 	else
// 		error_exit(data, ERR_IDENT);
// }

char *get_config_data(t_data *data, char *line)
{
	int i;
	int len = ft_strlen(line);
	
	i = 0;
	while(i < len && ft_isspace(line[i]))
		i++;
	while(i < len && !ft_isspace(line[i]))
		i++;
	if(i == 0)
		error_exit(data, ERR_IDENT);
	
	return(ft_strndup(line, i));
}

Identifier get_identifier(char *str)
{
	if(ft_strncmp(str, "NO ", 3) == 0)
		return ID_NO;
	if(ft_strncmp(str, "SO ", 3) == 0)
		return ID_SO;
	if(ft_strncmp(str, "WE ", 3) == 0)
		return ID_WE;
	if(ft_strncmp(str, "EA ", 3) == 0)
		return ID_EA;
	if(ft_strncmp(str, "F ", 2) == 0)
		return ID_F;
	if(ft_strncmp(str, "C ", 2) == 0)
		return ID_F;
	return ID_UNKNOWN;
}

long custom_strtol(const char *str, char **endptr) 
{
	long result = 0;
	while (*str >= '0' && *str <= '9') {
		result = result * 10 + (*str - '0');
		str++;
	}
	if (endptr) {
		*endptr = (char *)str;
	}
	return result;
}

void parse_line(char *line, t_data *data)
{
	while (*line && ft_isspace(*line))
		line++;
	Identifier id = get_identifier(line);
	char **path = NULL;
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
		else if (id == ID_F)
			path = &(data->assets->EA_path);
		else if (id == ID_EA)
			path = &(data->assets->EA_path);
		if (*path == NULL)
			*path = get_config_data(data, line + 3);
		else
			error_exit(data, ERR_IDENT);
	}
	if(id == ID_F || id == ID_C)
	{
		while (*line && ft_isspace(*line))
			line++;
		if(id == ID_F || id == ID_C)
		{
			unsigned char red, green, blue;
			char *endptr;
			red = (unsigned char)custom_strtol(line, &endptr);
			if (endptr == line || *endptr != ',') {
				error_exit(data, ERR_IDENT);
			}

			line = endptr + 1;
			green = (unsigned char)custom_strtol(line, &endptr);
			if (endptr == line || *endptr != ',') {
				error_exit(data, ERR_IDENT);
			}

			line = endptr + 1;
			blue = (unsigned char)custom_strtol(line, &endptr);
			if (endptr == line || (*endptr != '\0' && *endptr != '\n' && *endptr != '\r')) {
				error_exit(data, ERR_IDENT);
			}

			if (id == ID_F) {
				data->map->floor.red = red;
				data->map->floor.green = green;
				data->map->floor.blue = blue;
			} else { // id == ID_C
				data->map->ceiling.red = red;
				data->map->ceiling.green = green;
				data->map->ceiling.blue = blue;
			}
		}
	// else 
	// 	error_exit(data, ERR_IDENT);
	}
}

void	parse_config(t_data *data)
{
	int i = 0;	
	// int j = 0;

	while(data->file_by_line[i])
	{
		parse_line(data->file_by_line[i], data);
		i++;
	}

}


/* splits the file into lines and saves the ** in data->file */

void parse_file(t_data *data)
{
    // int i = 0;

    if(data->file == NULL)
	{
		printf("file not read\n");
		exit(1);
	}
	data->file_by_line = ft_split(data->file, '\n');
	parse_config(data);
    // while (data->file[i])
    // {
    //     printf("%s\n", data->file[i]);
    //     i++;
    // }
}

