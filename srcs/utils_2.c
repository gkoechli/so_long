/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkoechli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:21:10 by gkoechli          #+#    #+#             */
/*   Updated: 2021/12/11 11:58:34 by gkoechli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	str_add(t_data *data, char c)
{
	int		i;
	char	*s;

	s = NULL;
	i = 0;
	s = malloc(sizeof(char) * ft_strlen(data->temp.solong) + 2);
	if (s == NULL)
		return ;
	while (data->temp.solong[i])
	{
		s[i] = data->temp.solong[i];
		i++;
	}
	s[i] = c;
	s[i + 1] = '\0';
	free(data->temp.solong);
	data->temp.solong = ft_strdup(s);
	free(s);
}

int	map_read(t_data *data)
{
	int	i;

	i = 0;
	while (data->temp.solong[i])
	{
		if (data->temp.solong[i] != '1' && data->temp.solong[i] != '0'
			&& data->temp.solong[i] != 'P' && data->temp.solong[i] != 'E'
			&& data->temp.solong[i] != 'C' && data->temp.solong[i] != '\n')
			kill_error(data, MAP_IS_INVALID);
		i++;
	}
	if (i < 19)
		kill_error(data, MAP_IS_INVALID);
	return (0);
}

void	free_string_struct(t_data *data)
{
	if (data->temp.tmp != NULL)
		free(data->temp.tmp);
	if (data->temp.buff != NULL)
		free(data->temp.buff);
	if (data->temp.end != NULL)
		free(data->temp.end);
	if (data->temp.solong != NULL)
		free(data->temp.solong);
}

int	wall_gen(t_data *data)
{
	int	i;

	i = 0;
	data->wall = (int **)malloc(sizeof(int *) * data->row_size);
	while (i < data->row_size)
	{
		data->wall[i] = malloc(sizeof(int *) * data->row_size);
		i++;
	}
	return (0);
}

int	wall_kill(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->row_size)
	{
		free(data->wall[i]);
		i++;
	}
	free(data->wall);
	return (0);
}
