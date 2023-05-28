/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_collectible.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 12:47:19 by okraus            #+#    #+#             */
/*   Updated: 2023/05/28 15:26:35 by okraus           ###   ########.fr       */
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
	max->img->dci[0].x = 32 * max->map->w + 32;
}

void	ft_check_door(t_max *max)
{
	if (!max->map->cr && max->map->p && max->map->px == max->map->xx
		&& max->map->py == max->map->xy)
	{
		max->map->p = 0;
		ft_printf("You win!\n\n\n");
	}
}
