/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 03:03:13 by Evan              #+#    #+#             */
/*   Updated: 2025/05/01 23:46:09 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_to_charpp(t_env *env)
{
	int		count;
	t_env	*tmp;
	char	**arr;
	int		i;

	count = 0;
	tmp = env;
	while (tmp)
	{
		if (tmp->show)
			count++;
		tmp = tmp->next;
	}
	arr = ft_malloc(sizeof(*arr) * (count + 1));
	tmp = env;
	i = 0;
	while (tmp)
	{
		if (tmp->show)
			arr[i++] = ft_strdup(tmp->data);
		tmp = tmp->next;
	}
	arr[i] = NULL;
	return (arr);
}

int	wait_child(pid_t pid)
{
	int	status;
	int	sig;

	while (1)
	{
		if (waitpid(pid, &status, 0) < 0)
		{
			if (errno == EINTR)
				return (128 + SIGINT);
			perror("waitpid");
			return (1);
		}
		break ;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		print_signal_error(sig);
		return (128 + sig);
	}
	return (status);
}

static char	*search_in_path_dirs(char **dirs, const char *cmd)
{
	char	*tmpdir;
	char	*full;
	int		i;

	i = 0;
	while (dirs[i])
	{
		tmpdir = ft_strjoin(dirs[i], "/");
		full = ft_strjoin(tmpdir, cmd);
		if (!access(full, X_OK))
			return (full);
		i++;
	}
	return (NULL);
}

static char	*search_path(const char *cmd, t_env *env)
{
	t_env	*tmp;
	char	**dirs;

	if (ft_strchr(cmd, '/'))
	{
		if (!access(cmd, X_OK))
			return (ft_strdup(cmd));
		return (NULL);
	}
	tmp = env;
	while (tmp && ft_strcmp(tmp->name, "PATH="))
		tmp = tmp->next;
	if (!tmp || !tmp->params)
		return (NULL);
	dirs = ft_split(tmp->params, ":");
	if (!dirs)
		return (NULL);
	return (search_in_path_dirs(dirs, cmd));
}

int	exec_cmd(t_ast *cmd, t_env **env, int last_status)
{
	pid_t	pid;
	char	*path;

	if (is_builtin(cmd->argv[0]) && (!ft_strcmp(cmd->argv[0], "cd")
			|| !ft_strcmp(cmd->argv[0], "export") || !ft_strcmp(cmd->argv[0],
				"unset") || !ft_strcmp(cmd->argv[0], "exit")))
		return (run_builtin(cmd->argv, env, last_status));
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		apply_redirections(cmd->redirs);
		if (!cmd->argv[0])
			handle_empty_command();
		if (is_builtin(cmd->argv[0]))
			exit(run_builtin(cmd->argv, env, last_status));
		path = search_path(cmd->argv[0], *env);
		if (path)
			execve(path, cmd->argv, env_to_charpp(*env));
		printf("minishell: %s: command not found\n", cmd->argv[0]);
		exit(127);
	}
	return (wait_child(pid));
}
