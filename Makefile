# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/16 15:04:52 by okraus            #+#    #+#              #
#    Updated: 2023/05/28 14:04:06 by okraus           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= so_long
CCC		:= cc
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX	:= ./MLX42
LIBFT_F	:=	libft/
CMFLAGS	:= -DCMAKE_C_COMPILER=/usr/bin/gcc -DCMAKE_CXX_COMPILER=/usr/bin/g++ -B build
HEADERS	:= -I ./include -I $(LIBMLX)/include
LIB1	:= libft/libft.a
LIB2	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
# SRCS	:= $(shell find ./src -iname "*.c")
# SRCS	:= test.c
SRCS	:=	ft_so_long.c \
			ft_test.c \
			ft_player.c \
			ft_collectible.c \
			ft_enemy.c \
			ft_init.c \
			ft_update.c \
			ft_draw.c
OBJS	:= ${SRCS:.c=.o}

all: libft libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) $(CMFLAGS) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	@make -s -C $(LIBFT_F)

%.o: %.c
	@$(CCC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	@$(CCC) $(OBJS) $(LIB1) $(LIB2) $(HEADERS) -o $(NAME)

clean:
	@rm -f $(OBJS)
	@make fclean -s -C $(LIBFT_F)
	@rm -rf $(LIBMLX)/build
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -f $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx, libft
