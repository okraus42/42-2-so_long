/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:43:08 by okraus            #+#    #+#             */
/*   Updated: 2023/05/25 15:38:07 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H

# define SO_LONG_H

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

typedef struct data_s
{
	int			x;
	int			y;
	int			z;
	int			temp2;
	int			iter;
	int			c;
	long double	x0;
	long double	y0;
	long double	l;
	long double	alp;	//default alp
	long double	alpha; //final alpha
	int			amag; //magnitude of alpha
	int			afract;
	long double	power;
	long double	tmp[2];
	long double	zxy[2];
	long double	cxy[2];
	long double	temp;
} data_t;

// typedef struct map_s
// {
// 	char	**m;		//map saved in array
// 	int		w;			//width of map
// 	int		h;			//height of map
// 	int		p;			//player status 1-alive, 0 dead
// 	int		px;			//player position on map the x axis
// 	int		py;			//player position on map the y axis
//						//add player direction?
// 	int		ct;			//total number of collectibles
//	int		cr;			//number of remaining collectibles
// 	int		*c;			//collectible status 
// 	int		*cx;		//collectible position on the x axis
// 	int		*cy;		//collectible position on the y axis
// 	int		et;			//total number of enemies
// 	int		*e;			//array of enemies 0 dead, 1 alive
// 	int		*ex;		//enemy position on map the x axis
// 	int		*ey;		//enemy position on map the y axis
//						//add enemy direction?
//	int		x;			// exit status 0 closed, 1 open
//	int		xx;		// exit X
//	int		xy;		// exit Y
// } map_t;

typedef struct map_s
{
	char	**m;
	int		w;
	int		h;
	int		p;
	int		px;
	int		py;
	int		ct;
	int		cr;
	int		*c;
	int		*cx;
	int		*cy;
	int		et;
	int		*e;
	int		*ex;
	int		*ey;
	int		x;
	int		xx;
	int		xy;
} map_t;


typedef struct max_s
{
	mlx_t*		mlx;
	map_t*  	map;
	data_t*  	data;
} max_t;

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

#endif
