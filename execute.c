/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfernan <thfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 19:10:24 by thfernan          #+#    #+#             */
/*   Updated: 2026/01/04 19:24:16 by thfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_execute_cmds(t_pipex *px)
{
	int	i;

	i = 0;
	while (i < px->cmds)
	{
		px->pids[i] = fork();
		if (px->pids[i] == -1)
		{
			ft_cleanup(px);
			exit(1);
		}
		if (px->pids[i] == 0)
			ft_child_process(px, i);
		i++;
	}
}

void	ft_child_process(t_pipex *px, int i)
{
	ft_setup_redirections(px, i);
	ft_close_pipes(px);
	ft_exec(px->argv[px->cmd_start + i], px->envp, px);
}

void	ft_exec_error(char *msg, char **to_free, t_pipex *px)
{
	ft_putstr_fd(msg, 2);
	if (to_free)
		ft_free(to_free);
	ft_cleanup(px);
	exit(127);
}

void	ft_exec(char *cmd, char **envp, t_pipex *px)
{
	char	**cmd_args;
	char	*cmd_path;

	if (!cmd || cmd[0] == '\0')
		ft_exec_error("command not found\n", NULL, px);
	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args || !cmd_args[0])
		ft_exec_error("command not found\n", cmd_args, px);
	cmd_path = ft_find_cmd(cmd_args[0], envp);
	if (!cmd_path)
		ft_exec_error("command not found\n", cmd_args, px);
	execve(cmd_path, cmd_args, envp);
	free(cmd_path);
	ft_free(cmd_args);
	ft_cleanup(px);
	exit(127);
}

void	ft_wait_children(t_pipex *px)
{
	int	i;
	int	status;
	int	last_exit;

	i = 0;
	last_exit = 0;
	while (i < px->cmds)
	{
		waitpid(px->pids[i], &status, 0);
		if (WIFEXITED(status))
			last_exit = WEXITSTATUS(status);
		i++;
	}
	px->exit_status = last_exit;
}
