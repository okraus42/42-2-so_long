/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_so_long.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:35:23 by okraus            #+#    #+#             */
/*   Updated: 2023/05/25 19:49:05 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "MLX42/include/MLX42/MLX42.h"
#include "header/so_long.h"

static mlx_image_t* image;

/*
typedef enum scroll_keys
{
	MLX_ZOOM_IN		= 4,
	MLX_ZOOM_OUT	= 5,
}	scroll_key_t

bool mlx_is_scroll_in(mlx_t* mlx, scroll_key_t key)
{
	MLX_NONNULL(mlx);

	return (glfwGetMouseButton(mlx->window, key) == GLFW_PRESS);
}

bool mlx_is_scroll_out(mlx_t* mlx, scroll_key_t key)
{
	MLX_NONNULL(mlx);

	return (glfwGetMouseButton(mlx->window, key) == GLFW_PRESS);
}
*/
// -----------------------------------------------------------------------------

// struct s_colour
// {
// 	unsigned char	alpha;
// 	unsigned char	blue;
// 	unsigned char	green;
// 	unsigned char	red;
// }	t_colour;


union u_colour
{
	struct s_colour
	{
		unsigned char	alpha;
		unsigned char	blue;
		unsigned char	green;
		unsigned char	red;
	}	srgba;
	int				rgbai;
}	u_rgba;

/*int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}*/

void zoom(double xdelta, double ydelta, void* param)
{
	max_t*	max;
	long double	len;

	max = param;
	len = max->data->l;
	mlx_get_mouse_pos(max->mlx, &(max->data->x), &(max->data->y));
	/*if (ydelta < 0)
		*(int *)param = -1;
	if (ydelta > 0)
		*(int *)param = 1;
	if (xdelta < 0)
		*(int *)param = -1;
	if (xdelta > 0)
		*(int *)param = 1;*/
	if (ydelta < 0 && max->data->z > 1 && max->data->x >=0 && max->data->x <= 511
		&& max->data->y >=0 && max->data->y <= 511)
	{
		max->data->z -= 1;
		max->data->l *= 1.25;
	}
	if (ydelta > 0 && max->data->z < 256 && max->data->x >=0 && max->data->x <= 511
		&& max->data->y >=0 && max->data->y <= 511)
	{
		max->data->z += 1;
		max->data->l *= 0.8;
	}
	if (xdelta < 0)
		max->data->z += 0;
	//if (xdelta > 0)
	//	max->data->z += 1;
	//printf("B: %p | %d\n", param, *(int *)param);
	
	//max->data->l = 0.0078125 / max->data->z;
	max->data->x0 = max->data->x0 + max->data->x * len - max->data->x * max->data->l;
	max->data->y0 = max->data->y0 + max->data->y * len - max->data->y * max->data->l;

}

int ft_iter(max_t* max)
{
	int			iter;
	long double	zx;
	long double	zy;
	long double	cx;
	long double	cy;
    // zx = scaled x coordinate of pixel # (scale to be between -R and R)
    //    # zx represents the real part of z.
    // zy = scaled y coordinate of pixel # (scale to be between -R and R)
    //    # zy represents the imaginary part of z.

    // iteration = 0
    // max_iteration = 1000
  
// xtmp=(x*x+y*y)^(n/2)*cos(n*atan2(y,x)) + a
// y=(x*x+y*y)^(n/2)*sin(n*atan2(y,x)) + b
// x=xtmp
    // }
	zx = 0;
	zy = 0;
	cx = 0;
	cy = 0; 
	iter = 0;
	while (iter < max->data->iter && (cx + cy) <= 4)
	{
		zy = 2 * zx * zy + max->data->zxy[1];
		zx = cx - cy + max->data->zxy[0];
		cx = zx * zx;
		cy = zy * zy;
		iter++;
	}
	return (iter);
}

void ft_colourize3(void* max2)
{
	union u_colour	test;
	int32_t	x;
	int32_t	y;
	int32_t	z;
	int32_t	iter;
	max_t*	max;

	max = max2;
	test.rgbai = 0x00000000;
	test.srgba.alpha = 0xff;
	max->data->temp2++;
	max->data->alp = M_PI / max->data->afract;
	max->data->alpha = max->data->alp * max->data->amag;
	max->data->tmp[0] = max->data->cxy[0];
	max->data->tmp[1] = max->data->cxy[1];
	x = -1;
	y = -1;
	//printf("A1: %p | %d\n", &(max->data->z), max->data->z);

	z = max->data->z;
		
	//printf("%d\n", z);
	//max->data->l = 0.0078125;
	
	//usleep(10);
	//printf("A2: %p | %d\n", &(max->data->z), max->data->z);

	for (uint32_t i = 0; i < image->width; ++i)
	{
		//test.srgba.blue -= 16;
		for (uint32_t j = 0; j < image->height; ++j)
		{
			max->data->zxy[0] = max->data->x0 + (max->data->l * i);
			max->data->zxy[1] = max->data->y0 + (max->data->l * j);
			//printf("%10Lf\n", max->data->l);
			//printf("%Lf, %Lf\n", max->data->xy[0], max->data->xy[1]);
			iter = ft_iter(max);
			test.srgba.blue = ((max->data->c + iter) * 16) % 256;
			test.srgba.red = ((iter) * 4) % 256;
			//test.srgba.green = ((iter / 16)) % 256;
			if (iter == max->data->iter)
				test.rgbai = 0x000000ff;
			//test.srgba.green = iter / 0xf0;
			uint32_t colour = test.rgbai;
			mlx_put_pixel(image, i, j, colour);
		}
	}
	// max->data->cxy[0] = max->data->tmp[0] * cosl(max->data->alpha) - max->data->tmp[1] * sinl(max->data->alpha);
	// max->data->cxy[1] = max->data->tmp[1] * cosl(max->data->alpha) + max->data->tmp[0] * sinl(max->data->alpha);
}

/**
 * Returns the current, relative, mouse cursor position on the window, starting
 * from the top left corner.
 * 
 * Negative values or values greater than window width or height 
 * indicate that it is outside the window.
 * 
 * @param[in] mlx The MLX instance handle. 
 * @param[out] x The position.
 * @param[out] y The position.

void mlx_get_mouse_pos(mlx_t* mlx, int32_t* x, int32_t* y);
 */

/**
 * This function sets the scroll callback, which is called when a scrolling 
 * device is used, such as a mouse wheel.
 * 
 * @param[in] mlx The MLX instance handle.
 * @param[in] func The scroll wheel callback function.
 * @param[in] param An additional optional parameter.

void mlx_scroll_hook(mlx_t* mlx, mlx_scrollfunc func, void* param);
*/

/**
 * Callback function used to handle scrolling.
 * 
 * @param[in] xdelta The mouse x delta.
 * @param[in] ydelta The mouse y delta.
 * @param[in] param Additional parameter to pass on to the function.

typedef void (*mlx_scrollfunc)(double xdelta, double ydelta, void* param);

*/

void ft_hook(void* param)
{
	max_t*	max;

	max = param;

	if (mlx_is_key_down(max->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(max->mlx);
	if (mlx_is_key_down(max->mlx, MLX_KEY_UP))
		max->data->y0 -= max->data->l * 16;
	if (mlx_is_key_down(max->mlx, MLX_KEY_DOWN))
		max->data->y0 += max->data->l * 16;
	if (mlx_is_key_down(max->mlx, MLX_KEY_LEFT))
		max->data->x0 -= max->data->l * 16;
	if (mlx_is_key_down(max->mlx, MLX_KEY_RIGHT))
		max->data->x0 += max->data->l * 16;
	if (mlx_is_key_down(max->mlx, MLX_KEY_KP_DIVIDE))
	{
		if (max->data->power > 0.1)
			max->data->power -= 0.015625;
	}
	if (mlx_is_key_down(max->mlx,MLX_KEY_KP_MULTIPLY))
	{
		if (max->data->power < 100)
			max->data->power += 0.015625;
		printf("%Lf\n", max->data->power);
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_KP_8))
	{
		if (max->data->iter < 1024)
			max->data->iter += 16;
	}
	if (mlx_is_key_down(max->mlx,MLX_KEY_KP_2))
	{
		if (max->data->iter > 16)
			max->data->iter -= 16;
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_KP_4))
	{
		max->data->c--;
	}
	if (mlx_is_key_down(max->mlx,MLX_KEY_KP_6))
	{
		max->data->c++;
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_KP_ADD))
		max->data->amag = 1;
	if (mlx_is_key_down(max->mlx, MLX_KEY_KP_0))
		max->data->amag = 0;
	if (mlx_is_key_down(max->mlx, MLX_KEY_KP_SUBTRACT))
		max->data->amag = -1;


}

// -----------------------------------------------------------------------------

void	ft_init_map(map_t* map)
{
	map->m = NULL;
	map->w = 0;
	map->h = 0;
	map->p = 0;
	map->px = 0;
	map->py = 0;
	map->ct = 0;
	map->cr = 0;
	map->c = NULL;
	map->cx = NULL;
	map->cy = NULL;
	map->et = 0;
	map->e = NULL;
	map->ex = NULL;
	map->ey = NULL;
	map->x = 0;
	map->xx = 0;
	map->xy = 0;
}

void	ft_flood_map(map_t* map, int x, int y)
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

void	ft_check_flood(map_t* map)
{
	int	x;
	int	y;
	int	z;

	y = 1;
	z = 0;
	while (y < map->h - 1)
	{
		x = 1;
		while(x < map->w - 1)
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

void	ft_check_map(map_t* map)
{
	int	x;
	int	y;
	int	z;

	y = 0;
	z = 0;
	while (y < map->h)
	{
		x = 0;
		while(map->m[y][x])
		{
			if (y == 0 || y == map->h - 1 || x == 0 || x == map->w - 1)
			{
				if (map->m[y][x] != '1')
				{
					ft_printf("Wall ko%i,%i\n", x , y);
					exit(3);
				}
				ft_printf("Wall ok%i,%i\n", x , y);
			}
			else if (map->m[y][x] == 'P' && !(z & 1))
			{
				ft_printf("player position found%i, %i, %i\n", z, x , y);
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
			else if (map->m[y][x] != '1' && map->m[y][x] != '0'
				&& map->m[y][x] != 'C' && map->m[y][x] != 'S')
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

void	ft_test_map(map_t* map)
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

void	ft_fill_map(map_t* map, char* mapfile)
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
		free (line);
		line = get_next_line(fd);
		map->h++;
	}
	map->m = ft_split(gamemap, '\n');
	ft_put_strarray(map->m);
	ft_test_map(map);
}

void	ft_domove(map_t* map, int x, int y)
{
	if (map->m[y][x] == 'o')
	{
		map->m[map->py][map->px] = 'o';
		map->py = y;
		map->px = x;
		map->m[y][x] = 'p';
	}
}

int	ft_checkmove(map_t* map, int x, int y)
{
	ft_printf("Check\n");
	if (map->m[y][x] == 'o')
		return (0);
	if (map->m[y][x] == 'c')
	{
		map->c--;
		map->m[y][x] = 'o';
		return (0);
	}
	return (1);
}

void	ft_moveplayer(map_t* map, int d)
{
	int	t;
	int x;
	int y;

	x = map->px;
	y = map->py;
	if (d == 1)
		x++;
	if (d == 2)
		x--;
	if (d == 3)
		y++;
	if (d == 4)
		y--;
	t = ft_checkmove(map, x, y);
	if (!t)
		ft_domove(map, x, y);
	// else if (t == 1)
	// 	ft_killplayer();
	// else if (t == 2)
	// 	ft_wingame();
	// else if (t == 3)
	// 	ft_stepondoor();
}

void	ft_so_long(max_t* max, char* mapfile)
{
	map_t	mapt;

	max->map = &mapt;
	ft_init_map(max->map);
	ft_fill_map(max->map, mapfile);
	ft_moveplayer(max->map, 1);
	ft_put_strarray(max->map->m);
}

int32_t main(int32_t argc, char* argv[])
{
	mlx_t* mlx;
	data_t	datat;
	max_t	maxt;
	data_t*	data;
	max_t*	max;

	data = &datat;
	max = &maxt;
	data->x = 0;
	data->y = 0;
	data->z = 1;
	data->iter = 8048;
	data->c = 0;
	data->power = 2;
	data->l = 0.0078125;
	data->x0 = -2;
	data->y0 = -2;
	data->amag = 0;
	data->alp = 0;
	data->afract = 1;
	data->alpha = data->alp * data->amag;
	data->temp2 = 0;
	data->cxy[0] = 0;
	data->cxy[1] = 0;
	data->temp = 0;
	max->data = data;
	if (argc != 2)
	{
		ft_printf_fd(2, "%9CError%0C\n");
		return (1);
	}
	ft_printf("map name is: %s\n", argv[1]);
	ft_so_long(max, argv[1]);
	// Gotta error check this stuff
	if (!(mlx = mlx_init(max->map->w * 32, max->map->h * 32, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	max->mlx = mlx;
	if (!(image = mlx_new_image(mlx, 511, 511)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	//printf("%i", max->data->z);
	mlx_scroll_hook(mlx, &zoom, max);
	//mlx_loop_hook(mlx, ft_colourize, mlx);
	//mlx_loop_hook(mlx, ft_colourize2, max);
	max->data->zxy[0] = -2;
	max->data->zxy[1] = -2;
	//mlx_loop_hook(mlx, ft_colourize3, max);
	mlx_loop_hook(mlx, ft_hook, max);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
