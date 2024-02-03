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
}

/*
	this function opens the config file and reads it into buffer. 
	it reads up to buffer size - 1.
*/

void	read_file(char *path, t_data *data)
{
	int	fd;
	int	bytes_read;

	if (is_dir(path))
		error_exit(ERR_FILE_IS_DIR);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		error_exit(ERR_FILE_OPEN);
	bytes_read = read(fd, data->buffer, BUFFER_SIZE - 1);
	close(fd);
	if (bytes_read == -1)
		error_exit(ERR_FILE_READ);
	if (bytes_read == BUFFER_SIZE - 1)
		error_exit(ERR_FILE_SIZE);
	data->buffer[bytes_read] = '\0';
}

bool ft_isspace(int c) 
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

// char *get_information(char *str)
// {
// 	int i = 0;
	
// 	while(*str && ft_isspace(*str))
// 		str++;
// 	while(str[i] && !ft_isspace(str[i]))
// 		i++;
	// return()

// }

char *get_config_data(char *line)
{
	int i;
	int len = ft_strlen(line);
	
	i = 0;
	while(i < len && ft_isspace(line[i]))
		i++;
	while(i < len && !ft_isspace(line[i]))
		i++;
	if(i == 0)
		error_exit(ERR_IDENT);
	return(ft_strndup(line, i));
}

Identifier get_identifier(char *str)
{
	printf("%s\n", str);
	
	if(ft_strncmp(str, "NO ", 3) == 0)
		return ID_NO;
	if(ft_strncmp(str, "SO ", 3) == 0)
		return ID_SO;
	if(ft_strncmp(str, "WE ", 3) == 0)
		return ID_WE;
	if(ft_strncmp(str, "EA ", 3) == 0)
		return ID_EA;
	return ID_UNKNOWN;
}

void parse_line(char *line, t_data *data)
{
	while(*line && ft_isspace(*line))
		line++;
	if(get_identifier(line) == ID_NO)
	{
		if(data->assets->NO_path == NULL)
			data->assets->NO_path = get_config_data(line + 3);
		else
		{
			printf("test\n");
			error_exit(ERR_IDENT);
		}
	}
	if(get_identifier(line) == ID_SO)
	{
		if(data->assets->SO_path == NULL)
			data->assets->SO_path = get_config_data(line + 3);
		else
		{
			printf("test\n");
			error_exit(ERR_IDENT);

		}
	}
}

void	parse_config(t_data *data)
{
	int i = 0;	
	// int j = 0;

	while(data->file[i])
	{
		parse_line(data->file[i], data);
		i++;
	}

}


/* splits the file into lines and saves the ** in data->file */

void parse_file(t_data *data)
{
    // int i = 0;

    data->file = ft_split(data->buffer, '\n');
	parse_config(data);
    // while (data->file[i])
    // {
    //     printf("%s\n", data->file[i]);
    //     i++;
    // }
}

