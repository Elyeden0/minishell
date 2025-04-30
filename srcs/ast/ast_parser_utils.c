/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnard <abonnard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:08:01 by Evan              #+#    #+#             */
/*   Updated: 2025/04/30 10:34:48 by abonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token_type	peek_type(t_token *cur)
{
	if (cur)
		return (cur->type);
	return (T_EOL);
}

bool	consume_token(t_token_type type, t_token **cur)
{
	if (peek_type(*cur) == type)
	{
		*cur = (*cur)->next;
		return (true);
	}
	return (false);
}

char	**collect_arguments(t_token **cur)
{
	int		cap;
	int		argc;
	char	**argv;

	cap = 8;
	argc = 0;
	argv = ft_malloc(sizeof(*argv) * cap);
	while (peek_type(*cur) == T_WORD)
	{
		if (argc + 1 >= cap)
		{
			cap *= 2;
			argv = ft_realloc(argv, sizeof(*argv) * cap);
		}
		argv[argc] = ft_strdup((*cur)->value);
		argc++;
		consume_token(T_WORD, cur);
	}
	argv[argc] = NULL;
	return (argv);
}

void	add_redirection(t_redir **head, t_redir **tail, t_redir *new_node)
{
	if (!*head)
	{
		*head = new_node;
		*tail = new_node;
	}
	else
	{
		(*tail)->next = new_node;
		*tail = new_node;
	}
}

t_redir	*collect_redirections(t_token **cur)
{
	t_redir			*head;
	t_redir			*tail;
	t_token_type	rt;
	char			*target;
	t_redir			*r;

	head = NULL;
	tail = NULL;
	while (peek_type(*cur) == T_REDIR_IN || peek_type(*cur) == T_REDIR_OUT
		|| peek_type(*cur) == T_APPEND || peek_type(*cur) == T_HEREDOC)
	{
		rt = peek_type(*cur);
		consume_token(rt, cur);
		if (peek_type(*cur) != T_WORD)
			break ;
		target = ft_strdup((*cur)->value);
		consume_token(T_WORD, cur);
		r = redir_new(rt, target);
		add_redirection(&head, &tail, r);
	}
	return (head);
}
