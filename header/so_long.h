/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:43:08 by okraus            #+#    #+#             */
/*   Updated: 2023/05/12 18:15:12 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

// INCLUDES

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdarg.h>
# include <sys/wait.h> //check if needed, but it must be
# include <time.h> //check if needed
# include <sys/types.h> //open function1
# include <sys/stat.h> //open function2
# include <fcntl.h> //open function3
# include "../libft/header/libft.h"

// DEFINITIONS

// STRUCTURES
// PIPEX structure

typedef struct s_pipex_info
{
	int		ac;
	int		fdi;
	int		fdo;
	int		arg;
	int		hd;
	int		*pids;
	int		**pipes;
	char	**av;
	char	**ev;
	char	**paths;
	char	***args;
}	t_pipex_info;

// typedef struct s_pipex_info
// {
// 	int		ac;			//argc
// 	int		fdi;		//fd of infile
// 	int		fdo;		//fd of outfile
//	int		arg;		//number of arguments
//	int		hd;			//1 if argv[1] == "here_doc"
//	int		*pids;		//pids of child processes
//	int		**pipes;	//pipe fds
// 	char	**av;		//*argv[]
// 	char	**ev;		//*envp[]
// 	char	**paths;	//array of paths from envp
// 	char	***args;		//array of arrays of arguments
// }	t_pipex_info;

// PROTOTYPES

//	ft_paths
void	ft_fix_first_path(char **s);
char	*ft_pathjoin(char *path, char *cmd);
int		ft_paths(t_pipex_info *info);

// ft_utils
int		ft_exec(t_pipex_info *info, int n);
int		ft_fail_exec(t_pipex_info *info, int n);
int		ft_args(t_pipex_info *info);
int		ft_copy_strarray(int n, char **src, char ***dst);
int		ft_dup(int newinput, int newoutput);

// ft_pipes
void	ft_heredoc(t_pipex_info *info, int i);
int		ft_pipes(t_pipex_info *info);

// ft_getinfo
int		ft_open_pipes(t_pipex_info *info);
int		ft_check_files(t_pipex_info *info);
int		ft_get_info(t_pipex_info *info, int ac, char *av[], char *ev[]);
int		ft_free_info(t_pipex_info *info);

#endif
