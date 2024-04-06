/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkoechli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:29:02 by gkoechli          #+#    #+#             */
/*   Updated: 2021/12/13 10:54:12 by gkoechli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <X11/keysym.h>
# include <X11/Xlib.h>
# include "./mlx/minilibx-linux/mlx.h"
# define MAP_IS_INVALID 15
# define DUPLICATE_PLAYER_OR_EXIT 14
# define NO_PLAYER 13
# define NO_COLLECTIBLE 12
# define NO_EXIT 11
# define NOT_WALLED 10

typedef struct s_pos
{
	int	x;
	int	y;
	int	player_x;
	int	player_y;
	int	height;
	int	width;
}	t_pos;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_string
{
	char	*tmp;
	char	*buff;
	char	*end;
	char	*solong;
}	t_string;

typedef struct s_xpm
{
	void	*image;	
	char	*path;
	int		bpp;
	int		image_w;
	int		line_len;
	int		image_h;
	int		endian;
	char	*addr;
}	t_xpm;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_pos		pos;
	t_string	temp;
	t_xpm		rend;
	t_xpm		walls;
	t_xpm		collec;
	t_xpm		ground;
	t_xpm		player;
	t_xpm		exit;
	char		*map;
	int			index;
	int			success;
	int			check;
	int			**wall;
	int			row_size;
	int			col_size;
	int			color;
	int			player_number;
	int			exit_number;
	int			collectible;
	int			steps;
	int			win_width;
	int			win_height;
	int			cur_img;
}	t_data;

int		map_read(t_data *data);
int		handle_keypress(int keysym, t_data *data);
int		render(t_data *data);
int		check_borders(t_data *data);
int		check_map(t_data *data);
void	check_params(t_data *data);
int		parse(t_data *data);
int		exit_hook(t_data *data);
void	ft_cpyber(const char *str, t_data *data);
int		wall_gen(t_data *data);
int		grid_gen(t_data *data);
int		new_coor(t_data *data);
int		wall_kill(t_data *data);
int		is_map_valid(t_data *data);
int		fill_grid(t_data *data, int elem);
void	kill_error(t_data *data, int error_type);
void	reset_data(t_data *data);
void	str_glue(t_data *data);
void	str_add(t_data *data, char c);
char	*ft_strdup(const char *s1);
void	free_string_struct(t_data *data);
int		get_next_line(int fd, t_data *data);
int		check_line(char *str);
void	ft_substr_tmp(t_data *data, int start, int len);
void	ft_substr_end(t_data *data, int start, int len);
void	ft_strjoin(t_data *data);
char	*ft_strdup(const char *s1);
int		ft_strlen(const char *str);
void	assets_gen(t_data *data);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);

#endif
