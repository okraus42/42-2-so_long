/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:05:57 by okraus            #+#    #+#             */
/*   Updated: 2023/05/28 14:18:53 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/so_long.h"

static void	ft_domovep(t_max *max, int d)
{
	if (d == 8)
	{
		max->img->pi[0].y -= 32;
		max->map->py--;
	}
	if (d == 4)
	{
		max->img->pi[0].y += 32;
		max->map->py++;
	}
	if (d == 2)
	{
		max->img->pi[0].x -= 32;
		max->map->px--;
	}
	if (d == 1)
	{
		max->img->pi[0].x += 32;
		max->map->px++;
	}
	ft_printf("px = %i, py = %i\n", max->map->px, max->map->py);
	usleep(200000);
}

static int	ft_checkmovep(t_max *max, int x, int y)
{
	ft_printf("px = %i, py = %i", max->map->px, max->map->py);
	if (max->map->m[y][x] != '1')
	{
		if (max->map->m[y][x] == 'c')
		{
			max->map->cr--;
			ft_remove_collectible(max, x, y);
			if (!max->map->cr)
				ft_open_door(max);
			max->map->m[y][x] = 'o';
		}
		return (0);	
	}
	return (1);
}

void	ft_moveplayer(t_max *max, int d)
{
	int	t;
	int	x;
	int	y;

	x = max->map->px;
	y = max->map->py;
	ft_printf("d == %i\n", d);
	if (d == 1)
		x++;
	if (d == 2)
		x--;
	if (d == 4)
		y++;
	if (d == 8)
		y--;
	t = ft_checkmovep(max, x, y);
	if (!t)
	{
		ft_domovep(max, d);
		max->map->steps++;
		ft_moveenemies(max);
		//check enemies
		//check door
		ft_printf("Steps: %i\n", max->map->steps);
	}
	ft_init_key(max->key, 0);
}
// else if (t == 1)
// 	ft_killplayer();
// else if (t == 2)
// 	ft_wingame();
// else if (t == 3)
// 	ft_stepondoor(); maybe if p = 2?