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
	char			*path;
	char			*flags;
	int				trunc;
	int				here_doc;
	char			**infiles;
	char			**outfiles;
	int				fd_in;
	int				tuvo[2];
}t_cmds;

typedef struct s_mini_shell
{
	char	**envp;
	int		old_tubes[2];
	int		new_tubes[2];
	t_cmds	*cmds;
	int		num_cmds;
	pid_t	*childs;
}t_mini_shell;

void	parse(char* txt, char **envp);

void	find_infile(char *txt, t_mini_shell *ms);

void	find_outfile(char *txt, t_mini_shell *ms);

void	find_cmd(char *txt, t_mini_shell *ms);

void	heredoc(char *limitador, t_mini_shell *ms, int index);


char	*get_next_line(int fd);
size_t	gnl_strlen(const char *str);
int		ft_find_line(char *buff);
char	*gnl_strjoin(char *s1, char const *s2);
char	*gnl_substr(char const *s, unsigned int str, size_t len);


///////////////////////////////////////////POLLACULO///////////////////////////////////////////
void	pipex(t_mini_shell *ms);

int		do_forks(t_mini_shell *ms);
int		open_outfiles(t_mini_shell *ms, int index);
int		open_infiles(t_mini_shell *ms, int index);

void	do_one_child(t_mini_shell *ms);

int		ft_valid_name_char(int c);
//rutes
void	find_path(t_mini_shell *ms, int cmd_index);

char	**get_paths(t_mini_shell *ms);

//childs
void	do_first_child(t_mini_shell *ms);
void	do_middle_child(t_mini_shell *ms, int child_index);
void	do_last_child(t_mini_shell *ms, int child_index);
void	exit_child(t_mini_shell *ms);

//forks
#endif