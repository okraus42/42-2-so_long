/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:09:29 by okraus            #+#    #+#             */
/*   Updated: 2023/05/27 17:12:03 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/so_long.h"

void	ft_print_map(t_map *map)
{
	int	i;

	i = 0;
	ft_printf("\nMAP STATUS\nWIDTH: %i, HEIGHT = %i\n", map->w, map->w);
	ft_put_strarray(map->m);
	ft_printf("Player status: %i, x = %i, y = %i\n", map->p, map->px, map->py);
	ft_printf("Collectibles total: %i, remaining: %i\n", map->ct, map->cr);
	while (i < map->ct && map->c)
	{
		ft_printf("C[%i]%i x=%i y=%i\n", i, map->c[i], map->cx[i], map->cy[i]);
		i++;
	}
	i = 0;
	ft_printf("Enemies total: %i\n", map->et);
	while (i < map->et && map->e)
	{
		ft_printf("E[%i]%i x=%i y=%i\n", i, map->e[i], map->ex[i], map->ey[i]);
		i++;
	}
	ft_printf("Exit status: %i, x= %i, y= %i\n\n", map->x, map->xx, map->xy);
}

void	ft_flood_map(t_map *map, int x, int y)
{
	if (map->m[y][x] == '1' || map->m[y][x] > 'a')
		return ;
	if (map->m[y][x] == '0')
		map->m[y][x] = 'O';
	map->m[y][x] += 32;
	ft_flood_map(map, x + 1, y);
	ft_flood_map(map, x - 1, y);
	ft_flood_map(map, x, y + 1);
	ft_flood_map(map, x, y - 1);
}

void	ft_check_flood(t_map *map)
{
	int	x;
	int	y;
	int	z;

	y = 1;
	z = 0;
	while (y < map->h - 1)
	{
		x = 1;
		while (x < map->w - 1)
		{
			if (map->m[y][x] == 'E' || map->m[y][x] == 'C')
			{
				ft_printf("not flooded\n");
				exit(6);
			}
			if (map->m[y][x] == 'c')
				map->c++;
			if (map->m[y][x] == 's' || map->m[y][x] == 'S')
				map->e++;
			x++;
		}
		y++;
	}
}

void	ft_check_map(t_map *map)
{
	int	x;
	int	y;
	int	z;

	y = 0;
	z = 0;
	while (y < map->h)
	{
		x = 0;
		while (map->m[y][x])
		{
			if (y == 0 || y == map->h - 1 || x == 0 || x == map->w - 1)
			{
				if (map->m[y][x] != '1')
				{
					ft_printf("Wall ko%i,%i\n", x, y);
					exit(3);
				}
				ft_printf("Wall ok%i,%i\n", x, y);
			}
			else if (map->m[y][x] == 'P' && !(z & 1))
			{
				ft_printf("player position found%i, %i, %i\n", z, x, y);
				map->px = x;
				map->py = y;
				z += 1;
			}
			else if (map->m[y][x] == 'E' && !(z & 2))
			{
				map->xx = x;
				map->xy = y;
				z += 2;
			}
			else if (map->m[y][x] == 'S')
				map->et++;
			else if (map->m[y][x] == 'C')
				map->ct++;
			else if (map->m[y][x] != '1' && map->m[y][x] != '0')
			{
				ft_printf("invalid or duplicated char\n");
				exit(4);
			}
			x++;
		}
		if (x < 3 || x != map->w)
		{
			ft_printf("width\n");
			exit(2);
		}
		y++;
	}
}

void	ft_test_map(t_map *map)
{
	int	error;

	error = 0;
	if (map->h < 3)
		exit(2);
	ft_check_map(map);
	printf("map ok\n");
	ft_flood_map(map, map->px, map->py);
	ft_put_strarray(map->m);
	ft_check_flood(map);
}
