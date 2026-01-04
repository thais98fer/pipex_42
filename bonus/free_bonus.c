/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfernan <thfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 19:01:25 by thfernan          #+#    #+#             */
/*   Updated: 2026/01/04 19:40:28 by thfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_free(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	ft_cleanup(t_pipex *px)
{
	int	i;

	if (px->pipes)
	{
		i = 0;
		while (i < px->cmds - 1)
		{
			if (px->pipes[i])
				free(px->pipes[i]);
			i++;
		}
		free(px->pipes);
	}
	if (px->pids)
		free(px->pids);
}

void	ft_close_pipes(t_pipex *px)
{
	int	i;

	i = 0;
	while (i < px->cmds - 1)
	{
		close(px->pipes[i][0]);
		close(px->pipes[i][1]);
		i++;
	}
}
