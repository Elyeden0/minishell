/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 22:55:44 by Evan              #+#    #+#             */
/*   Updated: 2025/04/30 02:59:52 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_escape(t_hv *hv)
{
	char	c;

	if (read(STDIN_FILENO, &c, 1) <= 0)
		return (0);
	if (c != '[' && c != 'O')
		return (0);
	while (read(STDIN_FILENO, &c, 1) > 0)
		if ((unsigned char)c >= 0x40 && (unsigned char)c <= 0x7E)
			break ;
	if (c == 'A')
		ft_history_up(hv);
	else if (c == 'B')
		ft_history_down(hv);
	else if (c == 'C' && *(hv->pos) < ft_strlen(hv->buf))
	{
		write(1, "\x1b[C", 3);
		(*(hv->pos))++;
	}
	else if (c == 'D' && *(hv->pos) > 0)
	{
		write(1, "\x1b[D", 3);
		(*(hv->pos))--;
	}
	return (0);
}

void	ft_add_history(char *line, t_hist **tail)
{
	t_hist	*n;

	if (ft_strlen(line) == 0)
		return ;
	n = ft_malloc(sizeof(*n));
	n->line = ft_strdup(line);
	n->prev = *tail;
	n->next = NULL;
	if (*tail)
		(*tail)->next = n;
	*tail = n;
}
