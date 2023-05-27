/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:05:57 by okraus            #+#    #+#             */
/*   Updated: 2023/05/27 17:12:48 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/so_long.h"

static void	ft_domove(t_map *map, int x, int y)
{
	if (map->m[y][x] == 'o')
	{
		map->m[map->py][map->px] = 'o';
		map->py = y;
		map->px = x;
		map->m[y][x] = 'p';
	}
}

static int	ft_checkmovep(t_map *map, int x, int y)
{
	ft_printf("Check1\n");
	if (map->m[y][x] == 'o')
		return (0);
	if (map->m[y][x] == 'c')
	{
		map->c--;
		map->m[y][x] = 'o';
		return (0);
	}
	ft_printf("Check2\n");
	return (1);
}

void	ft_moveplayer(t_max *max, int d)
{
	int	t;
	int	x;
	int	y;

	x = max->map->px;
	y = max->map->py;
	if (d == 1)
		x++;
	if (d == 2)
		x--;
	if (d == 8)
		y++;
	if (d == 4)
		y--;
	t = ft_checkmovep(max->map, x, y);
	if (!t)
		ft_domove(max->map, x, y);
}
// else if (t == 1)
// 	ft_killplayer();
// else if (t == 2)
// 	ft_wingame();
// else if (t == 3)
// 	ft_stepondoor(); maybe if p = 2?