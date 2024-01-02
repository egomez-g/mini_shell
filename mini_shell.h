#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# define BUFFER_SIZE 43

typedef struct s_cmds
{
	char			*cmd;
	char			*flags;
	int				trunc;
	int				here_doc;
	char			*infile;
	char			*outfile;
	int				fd_in;
	int				tuvo[2];
}t_cmds;

typedef struct s_mini_shell
{
	t_cmds	*cmds;
	pid_t	*childs;
	int		num_cmds;
	char	**envp;
}t_mini_shell;

void	parse(char* txt, char **envp);

void	find_infile(char *txt, t_mini_shell *ms);

void	find_outfile(char *txt, t_mini_shell *ms);

//void	find_cmd(char *txt, t_mini_shell *ms);

void	heredoc(char *limitador, t_mini_shell *ms, int index);


char	*get_next_line(int fd);
size_t	gnl_strlen(const char *str);
int		ft_find_line(char *buff);
char	*gnl_strjoin(char *s1, char const *s2);


///////////////////////////////////////////POLLACULO///////////////////////////////////////////


typedef struct s_pipex
{
	char	**envp;
	int		argc;
	char	**argv;
	int		new_tubes[2];
	int		old_tubes[2];
	int		fd_file_in;
	int		fd_file_out;
	int		here_doc;
	char	*path;
	char	**cmd;
	int		*childs;
	int		arg_i;
}	t_pipex;

//rutes
int		get_vals(char *cmd, t_pipex *pipex);
char	**get_paths(t_pipex *pipex);

//childs
void	do_first_child(t_pipex *pipex);
void	do_middle_child(t_pipex *pipex, char *arg);
void	do_last_child(t_pipex *pipex);

//forks
int		do_forks(t_pipex *pipex);


int	pipex(int argc, char **argv, char **envp);
#endif