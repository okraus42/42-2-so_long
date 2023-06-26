/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:04:17 by okraus            #+#    #+#             */
/*   Updated: 2023/06/26 15:30:56 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

void	ft_put_walls(t_max *max, mlx_image_t *wall_img)
{
	int	x;
	int	y;

	y = 0;
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
			x++;
		}
		y++;
	}
}

void	ft_put_ground(t_max *max, mlx_image_t *grnd_img)
{
	int	x;
	int	y;

	y = 0;
	while (max->map->m[y])
	{
		x = 0;
		while (max->map->m[y][x])
		{
			if (max->map->m[y][x] != '1')
			{
				if (mlx_image_to_window(max->mlx, grnd_img, x * 32, y * 32) < 0)
					exit(-5);
			}
			x++;
		}
		y++;
	}
}

void	ft_put_background(t_max *max)
{
	xpm_t		*wall_xpm;
	xpm_t		*ground_xpm;
	mlx_image_t	*wall_img;
	mlx_image_t	*grnd_img;

	wall_xpm = mlx_load_xpm42("./imgs/wall.xpm42");
	if (!wall_xpm)
		exit(-4);
	wall_img = mlx_texture_to_image(max->mlx, &wall_xpm->texture);
	if (!wall_img)
		exit(-8);
	ground_xpm = mlx_load_xpm42("./imgs/ground.xpm42");
	if (!ground_xpm)
		exit(-4);
	grnd_img = mlx_texture_to_image(max->mlx, &ground_xpm->texture);
	if (!grnd_img)
		exit(-8);
	ft_put_walls(max, wall_img);
	ft_put_ground(max, grnd_img);
	mlx_delete_xpm42(wall_xpm);
	mlx_delete_xpm42(ground_xpm);
}

void	ft_put_collectibles3(t_max *max, mlx_image_t *col_img)
{
	int	x;
	int	y;

	y = 0;
	while (max->map->m[y])
	{
		x = 0;
		while (max->map->m[y][x])
		{
			if (max->map->m[y][x] == 'c')
			{
				if (mlx_image_to_window(max->mlx, col_img, x * 32, y * 32) < 0)
					exit(-5);
				max->img->ci = col_img->instances;
			}
			x++;
		}
		y++;
	}
}

void	ft_put_collectibles(t_max *max)
{
	xpm_t		*col_xpm;
	mlx_image_t	*col_img;

	col_xpm = mlx_load_xpm42("./imgs/collectible1.xpm42");
	if (!col_xpm)
		exit(-4);
	col_img = mlx_texture_to_image(max->mlx, &col_xpm->texture);
	if (!col_img)
		exit(-8);
	ft_put_collectibles3(max, col_img);
	mlx_delete_xpm42(col_xpm);
}

void	ft_put_collectibles4(t_max *max, mlx_image_t *col2_img)
{
	int			x;
	int			y;

	y = 0;
	while (max->map->m[y])
	{
		x = 0;
		while (max->map->m[y][x])
		{
			if (max->map->m[y][x] == 'c')
			{
				if (mlx_image_to_window(max->mlx,
						col2_img, (max->map->w + x) * 32, y * 32) < 0)
					exit(-5);
				max->img->c2i = col2_img->instances;
			}
			x++;
		}
		y++;
	}
}

void	ft_put_collectibles2(t_max *max)
{
	xpm_t		*col2_xpm;
	mlx_image_t	*col2_img;

	col2_xpm = mlx_load_xpm42("./imgs/collectible2.xpm42");
	if (!col2_xpm)
		exit(-4);
	col2_img = mlx_texture_to_image(max->mlx, &col2_xpm->texture);
	if (!col2_img)
		exit(-8);
	ft_put_collectibles4(max, col2_img);
	mlx_delete_xpm42(col2_xpm);
}

void	ft_put_enemies2(t_max *max, mlx_image_t *en_img)
{
	int			x;
	int			y;
	int			i;

	y = 0;
	i = 0;
	while (max->map->m[y])
	{
		x = 0;
		while (max->map->m[y][x])
		{
			if (max->map->m[y][x] == 's')
			{
				if (mlx_image_to_window(max->mlx, en_img, x * 32, y * 32) < 0)
					exit(-5);
				max->img->ei = en_img->instances;
				i++;
			}
			x++;
		}
		y++;
	}
}

void	ft_put_enemies(t_max *max)
{
	xpm_t		*en_xpm;
	mlx_image_t	*en_img;

	en_xpm = mlx_load_xpm42("./imgs/enemy1.xpm42");
	if (!en_xpm)
		exit(-4);
	en_img = mlx_texture_to_image(max->mlx, &en_xpm->texture);
	if (!en_img)
		exit(-8);
	ft_put_enemies2(max, en_img);
	mlx_delete_xpm42(en_xpm);
}

void	ft_put_door2(t_max *max, mlx_image_t *door_img)
{
	int			x;
	int			y;

	y = 0;
	while (max->map->m[y])
	{
		x = 0;
		while (max->map->m[y][x])
		{
			if (max->map->m[y][x] == 'e')
			{
				if (mlx_image_to_window(max->mlx, door_img, x * 32, y * 32) < 0)
					exit(-5);
				max->img->dci = door_img->instances;
			}
			x++;
		}
		y++;
	}
}

void	ft_put_door(t_max *max)
{
	xpm_t		*door_xpm;
	mlx_image_t	*door_img;

	door_xpm = mlx_load_xpm42("./imgs/door.xpm42");
	if (!door_xpm)
		exit(-4);
	door_img = mlx_texture_to_image(max->mlx, &door_xpm->texture);
	if (!door_img)
		exit(-8);
	ft_put_door2(max, door_img);
	mlx_delete_xpm42(door_xpm);
}

void	ft_put_opendoor2(t_max *max, mlx_image_t *opendoor_img)
{
	int			x;
	int			y;

	y = 0;
	while (max->map->m[y])
	{
		x = 0;
		while (max->map->m[y][x])
		{
			if (max->map->m[y][x] == 'e')
			{
				if (mlx_image_to_window(max->mlx,
						opendoor_img, x * 32, y * 32) < 0)
					exit(-5);
				max->img->doi = opendoor_img->instances;
			}
			x++;
		}
		y++;
	}
}

void	ft_put_opendoor(t_max *max)
{
	xpm_t		*opendoor_xpm;
	mlx_image_t	*opendoor_img;

	opendoor_xpm = mlx_load_xpm42("./imgs/dooropen.xpm42");
	if (!opendoor_xpm)
		exit(-4);
	opendoor_img = mlx_texture_to_image(max->mlx, &opendoor_xpm->texture);
	if (!opendoor_img)
		exit(-8);
	ft_put_opendoor2(max, opendoor_img);
	mlx_delete_xpm42(opendoor_xpm);
}

void	ft_put_player2(t_max *max, mlx_image_t *play_img)
{
	int			x;
	int			y;

	y = 0;
	while (max->map->m[y])
	{
		x = 0;
		while (max->map->m[y][x])
		{
			if (max->map->m[y][x] == 'p')
			{
				if (mlx_image_to_window(max->mlx, play_img, x * 32, y * 32) < 0)
					exit(-5);
				max->img->pi = play_img->instances;
				max->map->px = x;
				max->map->py = y;
			}
			x++;
		}
		y++;
	}
}

void	ft_put_player(t_max *max)
{
	xpm_t		*play_xpm;
	mlx_image_t	*play_img;

	play_xpm = mlx_load_xpm42("./imgs/player.xpm42");
	if (!play_xpm)
		exit(-4);
	play_img = mlx_texture_to_image(max->mlx, &play_xpm->texture);
	if (!play_img)
		exit(-8);
	ft_put_player2(max, play_img);
	mlx_delete_xpm42(play_xpm);
}
