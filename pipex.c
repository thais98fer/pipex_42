/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfernan <thfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 20:18:28 by thfernan          #+#    #+#             */
/*   Updated: 2025/12/30 09:00:52 by thfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exec(char *cmd, char **envp)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args)
		ft_error();
	cmd_path = ft_find_cmd(cmd_args[0], envp);
	if (!cmd_path)
	{
		ft_putstr_fd("command not found\n", 2);
		exit(127);
	}
	execve(cmd_path, cmd_args, envp);
}

void	ft_child_process(char **argv, char **envp, int *fd)
{
	int	infile;

	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
		ft_error();
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(infile);
	ft_exec(argv[2], envp);
}

void	ft_parent_process(char **argv, char **envp, int *fd)
{
	int outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile == -1)
		ft_error();
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[1]);
	close(fd[0]);
	close(outfile);
	ft_exec(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (argc != 5) // Colocar mensagem de erro
		return (1);
	if (pipe(fd) == -1)
		ft_error();
	pid = fork();
	if (pid == -1)
		ft_error();
	if (pid == 0)
		ft_child_process(argv, envp, fd);
	else
	{
		waitpid(pid, NULL, 0);
		ft_parent_process(argv, envp, fd);
	}
	return (0);
}
