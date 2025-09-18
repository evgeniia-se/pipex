#include "pipex.h"

char *get_full_path(char **paths, char **cmd)
{
	int		i;
	char	*full_path;
	char	*temp;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, cmd[0]);
		if (access(full_path, X_OK) == 0)
		{
			free_split(paths);
			free(temp);
			return (full_path);
		}
		free(full_path);
		free(temp);
		i++;
	}
	free_split(paths);
	return (NULL);
}
char *get_command_path(char **cmd, char **envp)
{
	char	*path1;
	char	**paths;

	path1 = NULL;
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			path1 = *envp + 5;
			break ;
		}
		envp++;
	}
	if (!path1)
		return (NULL);
	paths = ft_split(path1, ':');
	if (!paths)
		return (NULL);
	return (get_full_path(paths, cmd));
}

void	execute_command(char *cmd1, char **envp)
{
	char	*path;
	char	**cmd;
	cmd = ft_split(cmd1, ' ');
	if (!cmd)
		return ;
	path = get_command_path(cmd, envp);
	if (!path)
	{
		free_split(cmd);
		perror("Command not found");
		exit(EXIT_FAILURE);
	}
	if (execve(path, cmd, envp) == -1)
	{
		perror("Error executing command");
		exit(EXIT_FAILURE);
	}
}

void	for_pid2(int fd1, int fd2, int *pipefd, char *cmd2, char **envp)
{
	dup2(pipefd[0], STDIN_FILENO);
	dup2(fd2, STDOUT_FILENO);
	func_close(fd1, fd2, pipefd);
	execute_command(cmd2, envp);
	perror("Error executing cmd2");
	exit(EXIT_FAILURE);
}

void	for_pid1(int fd1, int fd2, int *pipefd, char *cmd1, char **envp)
{
	dup2(fd1, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);	
    func_close(fd1, fd2, pipefd);
	execute_command(cmd1, envp);
	perror("Error executing cmd1");
	exit(EXIT_FAILURE);
}