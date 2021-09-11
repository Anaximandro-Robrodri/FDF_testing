# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: robrodri <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/19 14:44:36 by robrodri          #+#    #+#              #
#    Updated: 2021/09/11 18:54:46 by robrodri         ###   ########.fr        #
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

RED 			= \033[0;31m
GREEN 			= \033[0;32m
NONE 			= \033[0m

OBJ = $(SRC:.c=.o)
LIBFT_DIR = ./libft/
LIBFT = libft.a
HEADER = fdf.h

FLAGS = -Wall -Wextra -Werror #-fsanitize=address
LINKS = -lmlx -framework OpenGL -framework AppKit

all: proyect make-libft $(NAME) $(HEADER)
	@echo "Proyect $(NAME) ready!"

proyect:
	@echo "\t $(NAME) IS COMMING!!"

$(NAME): $(OBJ)
	@echo "\t[ $(GREEN)✔$(NONE) ] compiling..."
	@$(CC) $(FLAGS) $(OBJ) $(LINKS) $(LIBFT_DIR)$(LIBFT) -o $(NAME)
	@echo "\t[ $(GREEN)✔$(NONE) ] $@ executable"

make-libft:
	@make -C $(LIBFT_DIR)

$(OBJ): $(SRC)
	@$(CC) $(FLAGS) -c $(SRC)

bonus: all

norm:
	norminette $(SRC) $(HEADER) $(LIBFT_DIR)

clean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	@rm -rf $(OBJ)

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@rm -rf $(NAME)
	@echo "\t[ $(RED)✗$(NONE) ] $(OBJ) recycle"
re: fclean all

.PHONY: all re m clean fclean bonus
