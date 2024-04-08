/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkoechli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 11:27:59 by gkoechli          #+#    #+#             */
/*   Updated: 2021/12/10 13:58:02 by gkoechli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	int		j;
	char	*s2;

	j = 0;
	while (s1[j])
		j++;
	i = 0;
	s2 = malloc(sizeof(char) * (j + 1));
	if (s2 == NULL)
		return (0);
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

void	ft_strjoin(t_data *data)
{
	int		i;
	int		j;
	char	*str;

	i = -1;
	j = 0;
	if (data->temp.tmp == NULL && data->temp.buff)
		data->temp.tmp = ft_strdup(data->temp.buff);
	else
	{
		str = malloc(sizeof(char) * (ft_strlen(data->temp.tmp)
					+ ft_strlen(data->temp.buff)) + 1);
		if (str == NULL)
			return ;
		while (data->temp.tmp[++i])
			str[i] = data->temp.tmp[i];
		while (data->temp.buff[j])
			str[i++] = data->temp.buff[j++];
		str[i] = '\0';
		free(data->temp.tmp);
		data->temp.tmp = ft_strdup(str);
		free(str);
	}
}

void	ft_substr_end(t_data *data, int start, int len)
{
	int	i;

	i = 0;
	if (data->temp.tmp == NULL)
		return ;
	if (ft_strlen(data->temp.tmp) < start)
	{
		data->temp.end = ft_calloc(1, sizeof(char));
		return ;
	}
	if (data->temp.end)
		free(data->temp.end);
	data->temp.end = malloc(sizeof(char) * len + 1);
	if (data->temp.end == NULL)
		return ;
	while (len-- > 0)
	{
		data->temp.end[i] = data->temp.tmp[i + start];
		i++;
	}
	data->temp.end[i] = '\0';
}

void	ft_substr_tmp(t_data *data, int start, int len)
{
	int		i;
	char	*s;

	i = 0;
	if (data->temp.tmp == NULL)
		return ;
	if (ft_strlen(data->temp.tmp) < start)
	{
		if (data->temp.tmp)
			free(data->temp.tmp);
		data->temp.tmp = ft_calloc(1, sizeof(char));
		return ;
	}
	s = malloc(sizeof(char) * len + 1);
	if (s == NULL)
		return ;
	while (len-- > 0)
	{
		s[i] = data->temp.tmp[i + start];
		i++;
	}
	free(data->temp.tmp);
	s[i] = '\0';
	data->temp.tmp = ft_strdup(s);
	free(s);
}

int	get_next_line(int fd, t_data *data)
{
	int	ret;

	ret = 1;
	data->temp.buff = malloc(sizeof(char) * 50 + 1);
	while (check_line(data->temp.tmp) == 0 && ret != 0)
	{
		ret = read(fd, data->temp.buff, 50);
		if (ret == -1)
			return (-1);
		data->temp.buff[ret] = '\0';
		ft_strjoin(data);
	}
	if (ret != 0)
	{
		ft_substr_end(data, 0, check_line(data->temp.tmp) - 1);
		ft_substr_tmp(data, check_line(data->temp.tmp),
			(int)ft_strlen(data->temp.tmp) - check_line(data->temp.tmp));
		return (1);
	}
	free(data->temp.end);
	data->temp.end = ft_strdup(data->temp.tmp);
	free(data->temp.tmp);
	data->temp.tmp = NULL;
	data->success = 10;
	return (0);
}
