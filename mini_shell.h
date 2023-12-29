#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_cmds
{
	char			*cmd;
	char			*outfile;
	char			*flags;
	struct s_cmds	*next;
}t_cmds;

typedef struct s_mini_shell
{
	int		here_doc;
	char	*infile;
	t_cmds	*cmds;
	pid_t	*childs;
	int		num_cmds;
	char	**envp;
}t_mini_shell;

void	parse(char* txt, char **envp);

void	new_list(t_mini_shell *ms);

void	find_infile(char *txt, t_mini_shell *ms);

#endif