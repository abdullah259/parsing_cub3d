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