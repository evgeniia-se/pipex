#include "pipex.h"

void	func_exit(int fd1, int fd2, int *pipefd)
{
	close(pipefd[0]);
	close(pipefd[1]);
	close(fd1);
	close(fd2);
	exit(EXIT_FAILURE);
}

void	func_close(int fd1, int fd2, int *pipefd)
{
	close(pipefd[0]);
	close(pipefd[1]);
	close(fd1);
	close(fd2);
}

void	work_pids(int fd1, int fd2, int *pipefd, char *cmd1, char *cmd2, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;	
	
	pid1 = fork();
	if (pid1 < 0)
	{
		perror("Error forking process 1");
		func_exit(fd1, fd2, pipefd);
	}
	if (pid1 == 0)
		for_pid1(fd1, fd2, pipefd, cmd1, envp);
	pid2 = fork();
	if (pid2 < 0)
	{
		perror("Error forking process 2");
		func_exit(fd1, fd2, pipefd);
	}
	if (pid2 == 0)
		for_pid2(fd1, fd2, pipefd, cmd2, envp);
	func_close(fd1, fd2, pipefd);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void	pipex(char *file1, char *cmd1, char *cmd2, char *file2, char **envp)
{
	int		fd1;
	int		fd2;
	int		pipefd[2];

	fd1 = open(file1, O_RDONLY);
	if (fd1 < 0)
	{
		perror("Error opening file1");
		exit(EXIT_FAILURE);
	}
	fd2 = open(file2, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd2 < 0)
	{	
		perror("Error opening/creating file2");
		close(fd1);
		exit(EXIT_FAILURE);
	}
	if (pipe(pipefd) == -1)
	{
		perror("Error creating pipe");
		func_exit(fd1, fd2, pipefd);
	}
	work_pids(fd1, fd2, pipefd, cmd1, cmd2, envp);
}

int main(int ac, char **av, char *envp[])
{
	if (ac != 5)
		return (printf("Error: not enough arguments\n"));

	pipex(av[1], av[2], av[3], av[4], envp);
	return (0);

}   // Rest of the code