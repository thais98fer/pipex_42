/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfernan <thfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 14:36:29 by thfernan          #+#    #+#             */
/*   Updated: 2025/12/30 09:20:30 by thfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

int		main(int argc, char **argv, char **envp);
void	ft_error(void);
void	ft_child_process(char **argv, char **envp, int *fd);
void	ft_parent_process(char **argv, char **envp, int *fd);
void	ft_exec(char *cmd, char **envp);
char	*ft_find_cmd(char *cmd, char **envp);
char	*ft_get_path(char **envp);

#endif
