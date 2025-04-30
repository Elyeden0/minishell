/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 01:52:11 by Evan              #+#    #+#             */
/*   Updated: 2025/04/28 01:54:49 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_literal(t_expander *ex)
{
	char	tmp[2];

	tmp[0] = ex->s[ex->i];
	tmp[1] = '\0';
	ex->res = append_str(ex->res, tmp);
	ex->i++;
}

static void	handle_dollar(t_expander *ex)
{
	char	*num;
	int		j;

	if (ex->s[ex->i + 1] == '?')
	{
		num = itoa_status(ex->last_status);
		ex->res = append_str(ex->res, num);
		ex->i += 2;
	}
	else if ((ex->s[ex->i + 1] >= 'A' && ex->s[ex->i + 1] <= 'Z')
		|| (ex->s[ex->i + 1] >= 'a' && ex->s[ex->i + 1] <= 'z') || ex->s[ex->i
			+ 1] == '_')
	{
		j = ex->i + 1;
		while (ex->s[j] && (is_alpha(ex->s[j]) || (ex->s[j] >= '0'
					&& ex->s[j] <= '9') || ex->s[j] == '_'))
			j++;
		ex->res = append_str(ex->res, get_env_value(ex->env, ft_strndup(ex->s
						+ ex->i + 1, j - (ex->i + 1))));
		ex->i = j;
	}
	else
		ex->i++;
}

static void	handle_double(t_expander *ex)
{
	ex->i++;
	while (ex->s[ex->i] && ex->s[ex->i] != '"')
	{
		if (ex->s[ex->i] == '$')
			handle_dollar(ex);
		else
			handle_literal(ex);
	}
	if (ex->s[ex->i] == '"')
		ex->i++;
}

static char	*expand_str(const char *s, t_env *env, int last_status)
{
	t_expander	ex;

	ex.s = s;
	ex.env = env;
	ex.last_status = last_status;
	ex.res = ft_malloc(1);
	ex.res[0] = '\0';
	ex.i = 0;
	while (ex.s[ex.i])
	{
		if (ex.s[ex.i] == '\'')
			handle_single(&ex);
		else if (ex.s[ex.i] == '"')
			handle_double(&ex);
		else if (ex.s[ex.i] == '$')
			handle_dollar(&ex);
		else
			handle_literal(&ex);
	}
	return (ex.res);
}

void	expand_tokens(t_token *tok, t_env *env, int last_status)
{
	while (tok)
	{
		if (tok->type == T_WORD && tok->value)
			tok->value = expand_str(tok->value, env, last_status);
		tok = tok->next;
	}
}
