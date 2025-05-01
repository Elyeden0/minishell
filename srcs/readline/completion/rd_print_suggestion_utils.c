/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_print_suggestion_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 00:28:41 by Evan              #+#    #+#             */
/*   Updated: 2025/05/02 00:46:45 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_terminal_width(void)
{
	struct winsize	ws;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
		return (80);
	return (ws.ws_col);
}

int	count_items(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

size_t	get_max_len(char **array)
{
	size_t	max;
	size_t	len;
	int		i;

	if (!array)
		return (0);
	max = 0;
	i = 0;
	while (array[i])
	{
		if (array[i])
		{
			len = ft_strlen(array[i]);
			if (len > max)
				max = len;
		}
		i++;
	}
	return (max);
}

void	ft_putnbr_fd(int n, int fd)
{
	char			buf[12];
	int				i;
	unsigned int	un;

	i = 11;
	buf[11] = '\0';
	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		un = (unsigned int)(-n);
	}
	else
		un = (unsigned int)n;
	while (un > 0 && i > 0)
	{
		buf[--i] = '0' + (un % 10);
		un /= 10;
	}
	write(fd, &buf[i], 11 - i);
}

void	init_sug_data(t_sug_data *d, char **arr, const char *prompt,
		const char *buf)
{
	d->arr = arr;
	d->prompt = prompt;
	d->buf = buf;
	d->count = count_items(arr);
	d->max_len = get_max_len(arr);
	d->width = get_terminal_width();
	d->cols = d->width / (d->max_len + 2);
	d->rows = (d->count + d->cols - 1) / d->cols;
	d->lines_printed = 0;
}
