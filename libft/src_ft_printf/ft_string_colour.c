/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_colour.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:55:41 by okraus            #+#    #+#             */
/*   Updated: 2023/03/14 15:12:38 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

int	ft_print_colour_fd(int fd, t_output	*t)
{
	int	i;

	i = 0;
	if (t->padsize == 1)
		i += write(fd, "\033[31m", 5);
	else if (t->padsize == 2)
		i += write(fd, "\033[32m", 5);
	else if (t->padsize == 3)
		i += write(fd, "\033[1;32m", 7);
	else if (t->padsize == 4)
		i += write(fd, "\033[94m", 5);
	else if (t->padsize == 5)
		i += write(fd, "\033[1;103m", 8);
	else if (t->padsize == 6)
		i += write(fd, "\033[1;42m", 7);
	else if (t->padsize == 7)
		i += write(fd, "\033[1;97;44m", 10);
	else if (t->padsize == 8)
		i += write(fd, "\033[1;97;41m", 10);
	else if (t->padsize == 9)
		i += write(fd, "\033[1;5;97;41m", 12);
	else
		i += write(fd, "\033[0m", 4);
	return (i);
}

int	ft_putcolour_fd(int fd, t_output *t)
{
	int		i;

	i = 0;
	i = ft_print_colour_fd(fd, t);
	return (i);
}
