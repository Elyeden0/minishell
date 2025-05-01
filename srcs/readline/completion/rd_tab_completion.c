/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_tab_completion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 00:19:11 by Evan              #+#    #+#             */
/*   Updated: 2025/05/02 00:24:00 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_prefix_info(t_v *v, t_completion_data *d)
{
	d->start = v->pos - 1;
	while (d->start >= 0 && v->buf[d->start] != ' ' && v->buf[d->start] != '\t')
		d->start--;
	d->start++;
	d->plen = v->pos - d->start;
	d->prefix = ft_strndup(v->buf + d->start, d->plen);
}

static void	get_suggestions(t_completion_data *d, t_env *env)
{
	d->suggestions = NULL;
	if (d->type == CT_CMD || d->type == CT_NONE)
		d->suggestions = get_command_suggestions(d->prefix, env);
	else
		d->suggestions = get_file_suggestions(d->prefix);
	d->count = count_items(d->suggestions);
}

static void	insert_suggestion(t_v *v, t_completion_data *d)
{
	d->j = 0;
	while (d->insertion[d->j])
	{
		ft_insert_char(&v->buf, &v->pos, &v->cap, d->insertion[d->j]);
		d->j++;
	}
	if (v->pos > 0 && v->buf[v->pos - 1] != '/')
		ft_insert_char(&v->buf, &v->pos, &v->cap, ' ');
}

static void	replace_prefix_with_suggestion(t_v *v, t_completion_data *d)
{
	d->last_slash = ft_strrchr(d->prefix, '/');
	if (d->last_slash)
		d->to_delete = d->plen - (int)(d->last_slash - d->prefix + 1);
	else
		d->to_delete = d->plen;
	while (d->to_delete > 0)
	{
		ft_handle_backspace(v->buf, &v->pos);
		d->to_delete--;
	}
	insert_suggestion(v, d);
}

void	handle_tab_completion(t_v *v, t_hv *hv, t_env *env)
{
	t_completion_data	d;

	d.type = get_completion_type(v->buf, v->pos);
	get_prefix_info(v, &d);
	get_suggestions(&d, env);
	if (d.count == 1)
	{
		d.insertion = d.suggestions[0];
		replace_prefix_with_suggestion(v, &d);
	}
	else
		print_suggestions(d.suggestions, hv->prompt, v->buf);
}
