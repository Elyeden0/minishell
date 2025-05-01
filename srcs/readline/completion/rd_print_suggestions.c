/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_print_suggestions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 00:46:16 by Evan              #+#    #+#             */
/*   Updated: 2025/05/02 00:47:45 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_display_all(t_sug_data *d)
{
	write(2, "\nDisplay all ", 13);
	ft_putnbr_fd(d->count, 2);
	write(2, " possibilities? (y or n) ", 24);
	while (1)
	{
		if (read(STDIN_FILENO, &d->c, 1) <= 0)
			break ;
		if (d->c == 'y' || d->c == 'Y')
			return (1);
		if (d->c == 'n' || d->c == 'N')
		{
			write(1, "\n", 1);
			write(1, d->prompt, ft_strlen(d->prompt));
			write(1, d->buf, ft_strlen(d->buf));
			return (0);
		}
	}
	return (1);
}

static void	print_suggestion_row(t_sug_data *d, int row)
{
	int	col;
	int	idx;

	col = 0;
	while (col < d->cols)
	{
		idx = col * d->rows + row;
		if (idx < d->count)
			printf("%-*s", d->max_len + 2, d->arr[idx]);
		col++;
	}
	printf("\n");
}

static int	handle_more_prompt(t_sug_data *d)
{
	write(2, "--More--", 8);
	while (read(STDIN_FILENO, &d->c, 1) > 0)
	{
		if (d->c == '\n')
			return (1);
		if (d->c == 'q')
		{
			write(1, "\n", 1);
			write(1, d->prompt, ft_strlen(d->prompt));
			write(1, d->buf, ft_strlen(d->buf));
			return (0);
		}
	}
	return (1);
}

static void	display_suggestions_grid(t_sug_data *d)
{
	int	row;

	write(1, "\n", 1);
	row = 0;
	while (row < d->rows)
	{
		print_suggestion_row(d, row);
		d->lines_printed++;
		if (d->lines_printed == 56 && (row + 1) < d->rows)
		{
			if (!handle_more_prompt(d))
				return ;
			write(1, "\r        \r", 10);
			d->lines_printed = 55;
		}
		row++;
	}
	write(1, d->prompt, ft_strlen(d->prompt));
	write(1, d->buf, ft_strlen(d->buf));
}

void	print_suggestions(char **arr, const char *prompt, const char *buf)
{
	t_sug_data	d;

	if (!arr)
		return ;
	init_sug_data(&d, arr, prompt, buf);
	if (d.count == 0)
		return ;
	if (d.cols < 1)
		d.cols = 1;
	if (d.cols * 57 < d.count)
	{
		if (!handle_display_all(&d))
			return ;
	}
	display_suggestions_grid(&d);
}
