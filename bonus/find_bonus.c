/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfernan <thfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 19:05:19 by thfernan          #+#    #+#             */
/*   Updated: 2026/01/04 19:40:32 by thfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_find_cmd(char *cmd, char **envp)
{
	char	**paths;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	paths = ft_split(ft_get_path(envp), ':');
	if (!paths)
		return (NULL);
	return (ft_search_in_paths(paths, cmd));
}

char	*ft_check_path(char *path, char *cmd)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(path, "/");
	full_path = ft_strjoin(temp, cmd);
	free(temp);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

char	*ft_search_in_paths(char **paths, char *cmd)
{
	char	*result;
	int		i;

	i = 0;
	while (paths[i])
	{
		result = ft_check_path(paths[i], cmd);
		if (result)
		{
			ft_free(paths);
			return (result);
		}
		i++;
	}
	ft_free(paths);
	return (NULL);
}

char	*ft_get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}
