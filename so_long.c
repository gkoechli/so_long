/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkoechli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:18:47 by gkoechli          #+#    #+#             */
/*   Updated: 2021/12/13 10:45:16 by gkoechli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	exit_hook(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->walls.image);
	mlx_destroy_image(data->mlx_ptr, data->collec.image);
	mlx_destroy_image(data->mlx_ptr, data->player.image);
	mlx_destroy_image(data->mlx_ptr, data->ground.image);
	mlx_destroy_image(data->mlx_ptr, data->exit.image);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	data->win_ptr = NULL;
	free(data->mlx_ptr);
	wall_kill(data);
	free(data->map);
	free(data->walls.path);
	free(data->ground.path);
	free(data->player.path);
	free(data->exit.path);
	free(data->collec.path);
	free(data->collec.addr);
	free(data->player.addr);
	free(data->exit.addr);
	free(data->ground.addr);
	free(data->walls.addr);
	free_string_struct(data);
	exit(EXIT_FAILURE);
	return (0);
}

int	render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);
	if (data->pos.player_x == 0)
		check_map(data);
	if (data->pos.x != 0 && (data->pos.x != data->pos.player_x
			|| data->pos.player_y != data->pos.y))
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->ground.image, data->pos.x * 64, data->pos.y * 64);
	if (data->wall[data->pos.x][data->pos.y] == 3 &&
		data->wall[data->pos.player_x][data->pos.player_y] != 3)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->exit.image, data->pos.x * 64, data->pos.y * 64);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player.image,
		data->pos.player_x * 64, data->pos.player_y * 64);
	new_coor(data);
	data->pos.x = data->pos.player_x;
	data->pos.y = data->pos.player_y;
	if (data->win_ptr == NULL)
		return (1);
	return (0);
}

int	so_long(t_data *data)
{
	map_read(data);
	ft_cpyber(data->temp.solong, data);
	data->win_width = data->row_size * 64;
	data->win_height = data->col_size * 64;
	wall_gen(data);
	grid_gen(data);
	check_borders(data);
	check_params(data);
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (1);
	data->win_ptr = mlx_new_window(data->mlx_ptr,
			data->win_width, data->win_height, "SO LONG");
	if (data->win_ptr == NULL)
	{
		free(data->win_ptr);
		return (1);
	}
	assets_gen(data);
	mlx_loop_hook(data->mlx_ptr, &render, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, data);
	mlx_hook(data->win_ptr, 17, 0, &exit_hook, data);
	mlx_loop(data->mlx_ptr);
	exit_hook(data);
	return (0);
}

int	main(int argc, char **argv)
{
	int		fd;
	int		i;
	t_data	data;

	i = 1;
	if (argc != 2)
		return (printf("Wrong number of arguments\n"));
	ft_bzero(&data, sizeof(data));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (printf("%s\n", strerror(errno)));
	while (i > 0)
	{
		if (data.temp.buff)
			free(data.temp.buff);
		i = get_next_line(fd, &data);
		str_glue(&data);
		str_add(&data, '\n');
	}
	close(fd);
	if (i == -1)
		kill_error(&data, MAP_IS_INVALID);
	if (argc == 2 && data.success == 10)
		so_long(&data);
	return (0);
}
