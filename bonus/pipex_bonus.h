/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfernan <thfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 14:36:29 by thfernan          #+#    #+#             */
/*   Updated: 2026/01/04 19:42:43 by thfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_pipex
{
	int		argc;
	char	**argv;
	char	**envp;
	int		cmds;
	int		cmd_start;
	int		is_heredoc;
	int		**pipes;
	int		exit_status;
	pid_t	*pids;
}			t_pipex;

int		main(int argc, char **argv, char **envp);
void	ft_init_pipex(t_pipex *paramts, int argc, char **argv, char **envp);
void	ft_create_pipes(t_pipex *paramts);
void	ft_close_pipes(t_pipex *paramts);
void	ft_execute_cmds(t_pipex *paramts);
void	ft_handle_heredoc(t_pipex *paramts);
void	ft_read_heredoc_lines(int fd_write, char *limiter);
void	ft_child_process(t_pipex *paramts, int i);
void	ft_setup_redirections(t_pipex *paramts, int i);
void	ft_setup_output(t_pipex *px);
void	ft_setup_input(t_pipex *px, int i);
void	ft_cleanup(t_pipex *paramts);
void	ft_wait_children(t_pipex *paramts);
void	ft_exec(char *cmd, char **envp, t_pipex *paramts);
void	ft_exec_error(char *msg, char **to_free, t_pipex *px);
char	*ft_find_cmd(char *cmd, char **envp);
char	*ft_check_path(char *path, char *cmd);
char	*ft_search_in_paths(char **paths, char *cmd);
char	*ft_get_path(char **envp);
void	ft_free(char **array);

#endif
