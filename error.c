void	free_2d(char ***str)
{
	int	i;

	if (!(*str))
		return ;
	i = 0;
	while ((*str)[i])
		free((*str)[i++]);
	free(*str);
	*str = NULL;
}

void	print_error(t_data *data, char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putchar_fd('\n', 2);
	free_all(data);
	exit(EXIT_FAILURE);
}

void	read_map(t_data *data, char **line, char **map_input)
{
	while (1)
	{
		*line = get_next_line(data->config_fd);
		if (!*line)
			print_error(data, "Wrong Config File");
		if (*line[0] == '\n')
		{
			free(*line);
			continue ;
		}
		else
		{
			*map_input = *line;
			break ;
		}
		free(*line);
	}
}

void	parse_map_contents(t_data *data)
{
	char	*line;
	char	*map_input;

	read_map(data, &line, &map_input);
	while (1)
	{
		line = get_next_line(data->config_fd);
		if (!line)
			break ;
		if (line[0] == '\n')
		{
			free(line);
			if (check_if_no_more_map(data))
			{
				free(map_input);
				print_error(data, "Wrong Config File");
			}
			break ;
		}
		map_input = ft_strjoin(map_input, line);
		free(line);
	}
	data->map = ft_split(map_input, '\n');
	free(map_input);
	calc_map_width_height(data);
}


int	color_atoi(const char *str)
{
	int	i;
	int	num;
	int	sign;

	num = 0;
	i = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] \
	== '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-')
		sign = -1;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	free ((char *)str);
	if (i > 5 || num > 255 || sign < 0)
		return (-1);
	return ((int)(num * sign));
}

int	ft_strlen_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	free_all(t_data *data)
{
	obj_status(data, 0, 0, 1);
	if (!data)
		return ;
	if (data->player.rays)
	{
		clear_ray_obj(data, 0);
		free(data->player.rays);
	}
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->map)
		free_2d(&(data->map));
	free_imgs(data);
	free_text(data);
	if (data->mlx)
		free(data->mlx);
	free(data);
}


int	close_window(t_data *data)
{
	free_all(data);
	exit(EXIT_SUCCESS);
}

void	free_text(t_data *data)
{
	if (data->no_path)
		free(data->no_path);
	if (data->so_path)
		free(data->so_path);
	if (data->we_path)
		free(data->we_path);
	if (data->ea_path)
		free(data->ea_path);
}

void	free_imgs(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 32)
		if (data->img[i].img)
			mlx_destroy_image(data->mlx, data->img[i].img);
}


int	obj_status(t_data *data, int x, int y, int to_do)
{
	static int	**obj_map;
	int			i;

	if (!obj_map)
	{
		i = 0;
		obj_map = ft_calloc(data->map_height, sizeof(int *));
		while (i < data->map_height)
			obj_map[i++] = ft_calloc(data->map_width, sizeof(int));
	}
	if (to_do == 1)
	{
		i = -1;
		while (++i < data->map_height)
			if (obj_map[i])
				free(obj_map[i]);
		if (obj_map)
			free(obj_map);
		return (0);
	}
	if (to_do > 2)
		obj_map[y][x] = to_do;
	return (obj_map[y][x]);
}