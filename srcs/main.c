/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnard <abonnard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:11:11 by Evan              #+#    #+#             */
/*   Updated: 2025/04/30 13:53:32 by abonnard         ###   ########.fr       */
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

char	*ft_get_prompt(t_env *env)
{
	char	*prompt;
	char	*pwd;
	char	*user;
	char	*temp;

	user = get_env_value(env, "USER");
	if (!user)
		user = ft_strdup("");
	pwd = get_env_value(env, "PWD");
	if (!pwd)
		pwd = ft_strdup("");
	temp = ft_strjoin(BOLD_GREEN, user);
	user = ft_strjoin(temp, RESET_COLOR":"BOLD_BLUE);
	temp = ft_strjoin(user, pwd);
	prompt = ft_strjoin(temp, BOLD_YELLOW"$ "RESET_COLOR);
	return (prompt);
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
		input = ft_readline(ft_get_prompt(env));
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
