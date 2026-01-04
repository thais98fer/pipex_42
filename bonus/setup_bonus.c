/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfernan <thfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 19:25:41 by thfernan          #+#    #+#             */
/*   Updated: 2026/01/04 19:40:56 by thfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_setup_input(t_pipex *px, int i)
{
	int	fd;

	if (i == 0 && !px->is_heredoc)
	{
		fd = open(px->argv[1], O_RDONLY);
		if (fd < 0)
		{
			perror(px->argv[1]);
			ft_close_pipes(px);
			ft_cleanup(px);
			exit(1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (i > 0)
		dup2(px->pipes[i - 1][0], STDIN_FILENO);
}

void	ft_setup_output(t_pipex *px)
{
	int		fd;
	char	*file;

	file = px->argv[px->argc - 1];
	if (px->is_heredoc)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(file);
		ft_close_pipes(px);
		ft_cleanup(px);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	ft_setup_redirections(t_pipex *px, int i)
{
	ft_setup_input(px, i);
	if (i == px->cmds - 1)
		ft_setup_output(px);
	else
		dup2(px->pipes[i][1], STDOUT_FILENO);
}
