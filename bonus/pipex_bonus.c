/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfernan <thfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 15:04:44 by thfernan          #+#    #+#             */
/*   Updated: 2026/01/04 19:40:45 by thfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	paramts;

	if (argc < 5)
	{
		ft_putstr_fd("Error: Invalid arguments\n", 2);
		return (1);
	}
	if (ft_strncmp(argv[1], "here_doc", 9) == 0 && argc < 6)
	{
		ft_putstr_fd("Error: here_doc needs at least 6 arguments\n", 2);
		return (1);
	}
	ft_init_pipex(&paramts, argc, argv, envp);
	if (paramts.is_heredoc)
		ft_handle_heredoc(&paramts);
	ft_create_pipes(&paramts);
	ft_execute_cmds(&paramts);
	ft_close_pipes(&paramts);
	ft_wait_children(&paramts);
	ft_cleanup(&paramts);
	return (paramts.exit_status);
}

void	ft_init_pipex(t_pipex *px, int argc, char **argv, char **envp)
{
	px->argc = argc;
	px->argv = argv;
	px->envp = envp;
	px->is_heredoc = (ft_strncmp(argv[1], "here_doc", 9) == 0);
	if (px->is_heredoc)
	{
		px->cmd_start = 3;
		px->cmds = argc - 4;
	}
	else
	{
		px->cmd_start = 2;
		px->cmds = argc - 3;
	}
	px->pipes = NULL;
	px->pids = NULL;
}

void	ft_create_pipes(t_pipex *px)
{
	int	i;

	px->pipes = malloc(sizeof(int *) * (px->cmds - 1));
	if (!px->pipes)
		exit(1);
	i = 0;
	while (i < px->cmds - 1)
	{
		px->pipes[i] = malloc(sizeof(int) * 2);
		if (!px->pipes[i] || pipe(px->pipes[i]) == -1)
		{
			ft_cleanup(px);
			exit(1);
		}
		i++;
	}
	px->pids = malloc(sizeof(pid_t) * px->cmds);
	if (!px->pids)
	{
		ft_cleanup(px);
		exit(1);
	}
}

void	ft_handle_heredoc(t_pipex *px)
{
	int		fd[2];

	if (pipe(fd) == -1)
	{
		ft_cleanup(px);
		exit(1);
	}
	ft_read_heredoc_lines(fd[1], px->argv[2]);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

void	ft_read_heredoc_lines(int fd_write, char *limiter)
{
	char	*line;
	int		limiter_len;

	limiter_len = ft_strlen(limiter);
	while (1)
	{
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(0);
		if (!line)
			break ;
		if (!ft_strncmp(line, limiter, limiter_len)
			&& line[limiter_len] == '\n')
		{
			free(line);
			break ;
		}
		write(fd_write, line, ft_strlen(line));
		free(line);
	}
}
