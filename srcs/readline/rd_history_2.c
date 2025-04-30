/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_history_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 22:26:31 by Evan              #+#    #+#             */
/*   Updated: 2025/04/30 17:10:15 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_clear_prompt_area(const char *prompt, const char *buf)
{
	size_t	total;
	size_t	i;

	total = visible_len(prompt) + strlen(buf);
	i = 0;
	while (i < total)
	{
		write(1, "\x1b[D", 3);
		i++;
	}
	write(1, "\x1b[K", 3);
}

static void	ft_rewrite_line(t_hv *hv, const char *line)
{
	ft_print_prompt(hv->prompt);
	write(1, line, ft_strlen(line));
	ft_memcpy(hv->buf, line, ft_strlen(line) + 1);
	*(hv->pos) = ft_strlen(line);
}

void	ft_history_up(t_hv *hv)
{
	char	*old_buf;

	if (*(hv->tail) == NULL)
		return ;
	if (*(hv->curr) == NULL)
	{
		old_buf = hv->buf;
		hv->save = ft_strdup(hv->buf);
	}
	else
		old_buf = (*(hv->curr))->line;
	ft_clear_prompt_area(hv->prompt, old_buf);
	if (*(hv->curr) == NULL)
		*(hv->curr) = *(hv->tail);
	else if ((*(hv->curr))->prev)
		*(hv->curr) = (*(hv->curr))->prev;
	ft_rewrite_line(hv, (*(hv->curr))->line);
}

void	ft_history_down(t_hv *hv)
{
	char	*old_buf;

	if (*(hv->curr) == NULL)
		return ;
	old_buf = (*(hv->curr))->line;
	ft_clear_prompt_area(hv->prompt, old_buf);
	if ((*(hv->curr))->next)
		*(hv->curr) = (*(hv->curr))->next;
	else
		*(hv->curr) = NULL;
	if (*(hv->curr))
		ft_rewrite_line(hv, (*(hv->curr))->line);
	else if (hv->save)
		ft_rewrite_line(hv, hv->save);
	else
		ft_rewrite_line(hv, "");
}
