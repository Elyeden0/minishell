/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:11:11 by Evan              #+#    #+#             */
/*   Updated: 2025/04/30 02:42:07 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

t_env	*init_env(t_env *env, char **envp)
{
	t_env	*tmp;
	t_env	*node;

	tmp = NULL;
	while (envp && *envp)
	{
		node = create_node_env(*envp);
		if (!env)
			env = node;
		else
			tmp->next = node;
		tmp = node;
		envp++;
	}
	check_path_pwd_env(env);
	return (env);
}

void	minishell(t_env *env)
{
	char	*input;
	t_lexer	*lexer;
	int		last_status;
	t_ast	*root;

	last_status = 0;
	while (1)
	{
		input = ft_readline("[minishell] $> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (syntax_error(input))
			continue ;
		lexer = lexer_init(input);
		if (!lexer)
			continue ;
		tokenize(lexer);
		expand_tokens(lexer->head, env, last_status);
		expand_star_tokens(&lexer->head);
		root = parse_ast(lexer);
		last_status = exec_ast(root, &env, last_status);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	if (argc != 1 && argv)
		return (1);
	env = NULL;
	env = init_env(env, envp);
	minishell(env);
	ft_free_all();
	return (0);
}
