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
		if(!data->file)
			error_exit(data, ERR_MALLOC);
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
		return ID_C;
	if(ft_strncmp(str, "1", 1) == 0)
		return ID_MAP;
	return ID_UNKNOWN;
}

char *get_config_path(t_data *data, char *line)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(line);
	while(i < len && ft_isspace(line[i]))
		i++;
	int start = i;
	while(i < len && !ft_isspace(line[i]))
		i++;
	if(i == start)
		error_exit(data, ERR_IDENT);
	return(ft_strndup(line + start, i - start));
}

void set_path(char *line, t_data *data, Identifier id)
{
	char **path;

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
		else if (id == ID_F)
			path = &(data->assets->EA_path);
		else if (id == ID_EA)
			path = &(data->assets->EA_path);
		if (*path == NULL)
			*path = get_config_path(data, line + 3);
		else
			error_exit(data, ERR_IDENT);
	}
}

/* converts char string to unsigned char, moves pointer and checks, if the pointer has moved.
	returns value */

unsigned char get_color_value(t_data *data, char **str) 
{
	int result;
	char *test;

	test = *str;
	result = 0;
	while (**str >= '0' && **str <= '9') 
	{
		result = result * 10 + (**str - '0');
		if(result > 255)
			error_exit(data, ERR_FLOOR_CEILING);
		(*str)++;
	}
	if(*str == test)
		error_exit(data, ERR_FLOOR_CEILING);
	return((unsigned char)result);
}

/* checks, if the color is already set. if not, it sets the color values */

void set_color_value(char *line, t_data *data, Identifier id)
{
	t_color *color;

	if (id == ID_F) 
		color = &(data->map->floor);
	else
		color = &(data->map->ceiling);
	if(color->color_ok == true)
		print_error_exit(data, "color duplicate");
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
of the identifier. After the identifier are 1+n whitespaces */

void parse_line(char *line, t_data *data, Identifier id)
{
	if (id == ID_NO || id == ID_SO || id == ID_WE || id == ID_EA) 
		set_path(line, data, id);
	else if(id == ID_F || id == ID_C)
	{
		// while (*line && ft_isspace(*line)) // skip over whitespace before id
		// 	line++;
		line++;
		while (*line && ft_isspace(*line)) // skip over whitespace after id
			line++;
		set_color_value(line, data, id);
	}
	else if(id == ID_MAP)
	{
		check_invalid_char(line, data);
	}
	else 
		error_exit(data, ERR_IDENT);
}


/* skips whitespace before the identifier by moving the pointer, 
then checks, which identifier it is. if it is unknown, it could be the map.
 */

void	parse_config(t_data *data)
{
	int i = 0;	
	Identifier id;
	char *line;
	
	while(data->file_by_line[i])
	{
		line = data->file_by_line[i];
		while (*line && ft_isspace(*line))
			line++;	
		id = get_identifier(line);
		if(id == ID_UNKNOWN)
			error_exit(data, ERR_IDENT);
		parse_line(line, data, id);
		i++;
	}

}

/* splits the file into lines and saves the ** in data->file */

void parse_file(t_data *data)
{
    if(data->file == NULL)
	{
		printf("file not read\n");
		exit(1);
	}
	data->file_by_line = ft_split(data->file, '\n');
	if (data->file_by_line == NULL)
		error_exit(data, ERR_USAGE);
	parse_config(data);
    // while (data->file[i])
    // {
    //     printf("%s\n", data->file[i]);
    //     i++;
    // }
}

