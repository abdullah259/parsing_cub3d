

typedef struct s_data
{
	void			*mlx;
	void			*win;
	// struct s_image	img[32];
	// struct s_player	player;
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
	int				c_color;
	int				f_color;
	int				map_width;
	int				map_height;
	int				config_fd;
	double			start_angle;
	int				index;
	int				wrong_door;
	int				c_color_count;
	int				f_color_count;
	char			**map;
}				t_data;