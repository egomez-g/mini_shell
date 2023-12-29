#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_cmds
{
	char	*cmd;
	char	*infile;
	char	*outfile;
	char	*flags;
	t_cmds	*next;
}t_cmds;

typedef struct s_mini_shell
{
	t_cmds	cmds;
	pid_t	*childs;
	int		num_cmds;
	char	**envp;
}t_mini_shell;




#endif