/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_so_long.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:35:23 by okraus            #+#    #+#             */
/*   Updated: 2023/06/10 14:57:36 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/so_long.h"

void	ft_game(t_max *max)
{
	if ((max->key->w || max->key->a || max->key->s || max->key->d) && !(max->key->t))
	{
		ft_moveplayer(max, max->key->w << 3 | max->key->s << 2
			| max->key->a << 1 | max->key->d);
		max->key->t++;
	}
	if (max->key->t && max->key->time)
	{
		ft_init_key(max->key, 0);
	}
	max->key->time++;
	if (max->key->t && max->key->t < 10)
	{
		max->key->t++; 
	}
	else
	{
		max->key->t = 0;
	}
	if (max->key->time > 10)
	{
		max->key->time = 0;
	}
	ft_check_time(max);
}

void	ft_hook(void *param)
{
	t_max	*max;

	max = param;
	if (mlx_is_key_down(max->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(max->mlx);
	}
	if (max->map->p && mlx_is_key_down(max->mlx, MLX_KEY_UP))
	{
		ft_init_key(max->key, 1);
	}
	if (max->map->p && mlx_is_key_down(max->mlx, MLX_KEY_DOWN))
	{
		ft_init_key(max->key, 2);
	}
	if (max->map->p && mlx_is_key_down(max->mlx, MLX_KEY_LEFT))
	{
		ft_init_key(max->key, 3);
	}
	if (max->map->p && mlx_is_key_down(max->mlx, MLX_KEY_RIGHT))
	{
		ft_init_key(max->key, 4);
	}
	ft_game(max);
}

// -----------------------------------------------------------------------------

void	ft_fill_map(t_map *map, char *mapfile)
{
	int		fd;
	char	*gamemap;
	char	*line;

	fd = open(mapfile, O_RDONLY);
	if (fd < 0)
		exit(-1);
	line = get_next_line(fd);
	gamemap = ft_strdup("");
	map->w = ft_strlen(line) - 1;
	while (line)
	{
		gamemap = ft_strjoin_freeleft(gamemap, line);
		free(line);
		line = get_next_line(fd);
		map->h++;
	}
	free(line);
	map->m = ft_split(gamemap, '\n');
	ft_test_map(map);
	free(gamemap);
}

void	ft_so_long(t_max *max, char *mapfile)
{
	ft_init_map(max->map);
	ft_init_keys(max->key);
	ft_fill_map(max->map, mapfile);
	ft_update_map(max->map);
	ft_print_map(max->map);
	ft_put_strarray(max->map->m);
}

void	ft_so_long2(t_max *max)
{
	ft_put_background(max);
	ft_put_collectibles(max);
	ft_put_collectibles2(max);
	ft_put_opendoor(max);
	ft_put_door(max);
	//ft_update_map(max->map);
	ft_put_enemies(max);
	ft_put_player(max);
	max->map->cr = max->map->ct;
	max->key->time = 0;
}

int32_t	main(int32_t argc, char *argv[])
{
	mlx_t				*mlx;
	t_max				max;
	t_map				mapt;
	t_imgs				imgt;
	t_controls			keyt;

	max.map = &mapt;
	max.key = &keyt;
	max.img = &imgt;
	if (argc != 2)
	{
		ft_printf_fd(2, "%9CError%0C\n");
		return (1);
	}
	ft_so_long(&max, argv[1]);
	mlx = mlx_init(max.map->w * 32, max.map->h * 32, "MLX42", true);
	if (!max.mlx)
	{
		puts(mlx_strerror(mlx_errno));
		exit(-999);
	}
	max.mlx = mlx;
	ft_so_long2(&max);
	mlx_loop_hook(mlx, ft_hook, &max);
	mlx_loop(mlx);
	write(1, "1", 1);
	ft_free(&max);
	write(1, "\n", 1);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
