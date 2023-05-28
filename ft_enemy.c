/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_enemy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 12:47:19 by okraus            #+#    #+#             */
/*   Updated: 2023/05/28 18:24:33 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/so_long.h"


static void	ft_domovee(t_max *max, int i, int d)
{
	ft_printf("d = %i, e[%i]: x = %i, y = %i\n", d, i, max->map->ex[i], max->map->ey[i]);
	if (d == 4)
	{
		max->img->ei[i].y -= 32;
		max->map->ey[i]--;
	}
	if (d == 2)
	{
		max->img->ei[i].y += 32;
		max->map->ey[i]++;
	}
	if (d == 3)
	{
		max->img->ei[i].x -= 32;
		max->map->ex[i]--;
	}
	if (d == 1)
	{
		max->img->ei[i].x += 32;
		max->map->ex[i]++;
	}
	ft_printf("d = %i, e[%i]: x = %i, y = %i\n", d, i, max->map->ex[i], max->map->ey[i]);
}

static int	ft_checkmovee(t_map *map, int i, int x, int y)
{
	if (map->ey[i] > map->py + 3 && map->m[y - 1][x] != '1' && (i + map->steps) % 4)
		return (4);
	if (map->ex[i] > map->px + 3 && map->m[y][x - 1] != '1' && (i + map->steps) % 4)
		return (3);
	if (map->ey[i] < map->py - 2 && map->m[y + 1][x] != '1' && (i + map->steps) % 3)
		return (2);
	if (map->ex[i] < map->px - 2 && map->m[y][x + 1] != '1' && (i + map->steps) % 3)
		return (1);
	if (map->ex[i] < map->px && map->m[y][x + 1] != '1' && !((i + map->steps) % 2))
		return (1);
	if (map->ey[i] < map->py && map->m[y + 1][x] != '1' && !((1 + i + map->steps) % 2))
		return (2);
	if (map->ex[i] > map->px && map->m[y][x - 1] != '1' && (i + map->steps % 3))
		return (3);
	if (map->ey[i] > map->py && map->m[y - 1][x] != '1' && map->steps % 3)
		return (4);
	if (map->m[y][x - 1] != '1' && ((i + map->steps) % 3))
		return (3);
	if (map->m[y - 1][x] != '1')
		return (4);
	if (map->m[y][x + 1] != '1' && ((i + map->steps) % 2))
		return (1);
	if (map->m[y + 1][x] != '1')
		return (2);
	if (map->m[y][x - 1] != '1')
		return (3);
	if (map->m[y][x + 1] != '1')
		return (1);
	return (0);
}

void	ft_check_enemy(t_max *max)
{
	int	i;

	i = 0;
	while (max->map->e[i])
	{
		if (max->map->e[i] && max->map->px == max->map->ex[i] && max->map->py == max->map->ey[i])
		{
			max->map->p = 0;
			ft_printf("\n\nYou stepped on enemy and died:(\n\n\n");
		}
		i++;
	}
}

void	ft_check_player(t_max *max, int i)
{
	if (max->map->px == max->map->ex[i] && max->map->py == max->map->ey[i])
	{
		max->map->p = 0;
		ft_printf("\n\nEnemy got you and you are now dead:(\n\n\n");
	}
}

void	ft_moveenemy(t_max *max, int i, int x, int y)
{
	int	d;

	x = max->map->ex[i];
	y = max->map->ey[i];

	d = ft_checkmovee(max->map, i, x, y);
	if (d)
	{
		ft_domovee(max, i, d);
		ft_check_player(max, i);
	}
}

void	ft_moveenemies(t_max *max)
{
	int x;
	int y;
	int	i;

	i = 0;
	x = 0;
	y = 0;
	while (i < max->map->et)
	{
		if (max->map->e[i])
		{
			ft_moveenemy(max, i, x, y);
			i++;
		}
	}
}