# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: robrodri <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/19 14:44:36 by robrodri          #+#    #+#              #
#    Updated: 2021/09/10 14:16:01 by robrodri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
SRC = fdf.c \
	  fdf_utils.c \
	  fdf_parser_utils.c \
	  fdf_draw.c \
	  fdf_mlx.c \
	  fdf_maths.c \
	  fdf_control.c

OBJ = $(SRC:.c=.o)
LIBFT_DIR = ./libft/
LIBFT = libft.a

FLAGS = -Wall -Wextra -Werror #-fsanitize=address
LINKS = -lmlx -framework OpenGL -framework AppKit

all: make-libft $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(LINKS) $(LIBFT_DIR)$(LIBFT) -o $(NAME)

make-libft:
	make -C $(LIBFT_DIR)

$(OBJ): $(SRC)
	$(CC) $(FLAGS) -c $(SRC)

bonus: all

norm: $(SRC)
	norminette $(SRC)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -rf $(OBJ)
fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -rf $(NAME)
re: fclean all

.PHONY: all re m clean fclean bonus
