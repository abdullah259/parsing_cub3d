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
