/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_collectible.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 12:47:19 by okraus            #+#    #+#             */
/*   Updated: 2023/05/28 14:17:42 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/so_long.h"

void	ft_remove_collectible(t_max *max, int x, int y)
{
	int	i;

	i = 0;
	while (i < max->map->ct)
	{
		if (max->map->cx[i] == x && max->map->cy[i] == y)
			max->img->ci[i].x = 32 * max->map->w + 32;
		i++;
	}
}

void	ft_open_door(t_max *max)
{
	int			x;
	int			y;
	xpm_t		*opendoor_xpm;
	mlx_image_t	*opendoor_img;

	x = 0;
	y = 0;
	opendoor_xpm = mlx_load_xpm42("./imgs/dooropen.xpm42");
	if (!opendoor_xpm)
		exit(-4);
	opendoor_img = mlx_texture_to_image(max->mlx, &opendoor_xpm->texture);
	if (!opendoor_img)
		exit(-8);
	while (max->map->m[y])
	{
		x = 0;
		while (max->map->m[y][x])
		{
			if (max->map->m[y][x] == 'e')
			{
				if (mlx_image_to_window(max->mlx, opendoor_img, x * 32, y * 32) < 0)
					exit(-5);
				max->img->dci = opendoor_img->instances;
			}
			x++;
		}
		y++;
	}
}
