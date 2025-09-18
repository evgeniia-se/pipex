#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
#include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

char	**ft_split(const char *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	free_split(char **str);
char	*get_command_path(char **cmd, char **envp);
void    for_pid1(int fd1, int fd2, int *pipefd, char *cmd1, char **envp);
void    for_pid2(int fd1, int fd2, int *pipefd, char *cmd2, char **envp);
void	execute_command(char *cmd1, char **envp);
void    work_pids(int fd1, int fd2, int *pipefd, char *cmd1, char *cmd2, char **envp);
char	*get_full_path(char **paths, char **cmd);
void    func_close(int fd1, int fd2, int *pipefd);
void    func_exit(int fd1, int fd2, int *pipefd);

#endif

