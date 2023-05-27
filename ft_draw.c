/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:04:17 by okraus            #+#    #+#             */
/*   Updated: 2023/05/27 17:24:05 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/so_long.h"

void	ft_put_background(t_max *max)
{
	int			x;
	int			y;
	xpm_t		*wall_xpm;
	xpm_t		*ground_xpm;
	mlx_image_t	*wall_img;
	mlx_image_t	*grnd_img;

	x = 0;
	y = 0;
	ft_printf("test00-1\n");
	wall_xpm = mlx_load_xpm42("./imgs/wall.xpm42");
	if (!wall_xpm)
		exit(-4);
	ground_xpm = mlx_load_xpm42("./imgs/ground.xpm42");
	if (!ground_xpm)
		exit(-4);
	ft_printf("test0000\n");
	wall_img = mlx_texture_to_image(max->mlx, &wall_xpm->texture);
	if (!wall_img)
		exit(-8);
	grnd_img = mlx_texture_to_image(max->mlx, &ground_xpm->texture);
	if (!grnd_img)
		exit(-8);
	ft_printf("test0001\n");
	while (max->map->m[y])
	{
		x = 0;
		while (max->map->m[y][x])
		{
			if (max->map->m[y][x] == '1')
			{
				if (mlx_image_to_window(max->mlx, wall_img, x * 32, y * 32) < 0)
					exit(-5);
			}
			else
			{
				if (mlx_image_to_window(max->mlx, grnd_img, x * 32, y * 32) < 0)
					exit(-5);
			}
			x++;
		}
		y++;
	}
	ft_printf("test1111\n");
}

void	ft_put_collectibles(t_max *max)
{
	int			x;
	int			y;
	xpm_t		*col_xpm;
	mlx_image_t	*col_img;

	x = 0;
	y = 0;
	col_xpm = mlx_load_xpm42("./imgs/collectible1.xpm42");
	if (!col_xpm)
		exit(-4);
	col_img = mlx_texture_to_image(max->mlx, &col_xpm->texture);
	if (!col_img)
		exit(-8);
	while (max->map->m[y])
	{
		x = 0;
		while (max->map->m[y][x])
		{
			if (max->map->m[y][x] == 'c')
			{
				if (mlx_image_to_window(max->mlx, col_img, x * 32, y * 32) < 0)
					exit(-5);
			}
			x++;
		}
		y++;
	}
}

void	ft_put_enemies(t_max *max)
{
	int			x;
	int			y;
	xpm_t		*en_xpm;
	mlx_image_t	*en_img;

	x = 0;
	y = 0;
	en_xpm = mlx_load_xpm42("./imgs/enemy1.xpm42");
	if (!en_xpm)
		exit(-4);
	en_img = mlx_texture_to_image(max->mlx, &en_xpm->texture);
	if (!en_img)
		exit(-8);
	while (max->map->m[y])
	{
		x = 0;
		while (max->map->m[y][x])
		{
			if (max->map->m[y][x] == 's')
			{
				if (mlx_image_to_window(max->mlx, en_img, x * 32, y * 32) < 0)
					exit(-5);
			}
			x++;
		}
		y++;
	}
}

void	ft_put_door(t_max *max)
{
	int			x;
	int			y;
	xpm_t		*door_xpm;
	mlx_image_t	*door_img;

	x = 0;
	y = 0;
	door_xpm = mlx_load_xpm42("./imgs/door.xpm42");
	if (!door_xpm)
		exit(-4);
	door_img = mlx_texture_to_image(max->mlx, &door_xpm->texture);
	if (!door_img)
		exit(-8);
	while (max->map->m[y])
	{
		x = 0;
		while (max->map->m[y][x])
		{
			if (max->map->m[y][x] == 'e')
			{
				if (mlx_image_to_window(max->mlx, door_img, x * 32, y * 32) < 0)
					exit(-5);
			}
			x++;
		}
		y++;
	}
}


void	ft_put_player(t_max *max)
{
	int			x;
	int			y;
	xpm_t		*play_xpm;
	mlx_image_t	*play_img;

	x = 0;
	y = 0;
	play_xpm = mlx_load_xpm42("./imgs/player.xpm42");
	if (!play_xpm)
		exit(-4);
	play_img = mlx_texture_to_image(max->mlx, &play_xpm->texture);
	if (!play_img)
		exit(-8);
	while (max->map->m[y])
	{
		x = 0;
		while (max->map->m[y][x])
		{
			if (max->map->m[y][x] == 'p')
			{
				if (mlx_image_to_window(max->mlx, play_img, x * 32, y * 32) < 0)
					exit(-5);
			}
			x++;
		}
		y++;
	}
}