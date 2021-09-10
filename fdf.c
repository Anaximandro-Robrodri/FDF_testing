/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 14:44:07 by robrodri          #+#    #+#             */
/*   Updated: 2021/09/10 11:37:07 by robrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_matrix(t_values *val)
{
	int	i;

	i = 0;
	while (i < val->row)
	{
		free(val->nbr[i]);
		free(val->color[i]);
		i++;
	}
	free(val->nbr);
	free(val->color);
}

static void	ft_error(void)
{
	ft_putstr("An error has ocurred\n");
	exit(-1);
}

static int	check_map(char *argv, t_values *val)
{
	char	*line;

	val->fd = open(argv, O_RDONLY);
	ft_init_struct_val(val);
	val->ret = get_next_line(val->fd, &line);
	while (val->ret == 1)
	{
		if (!ft_error_control(line, val) || !get_len(line, val))
		{
			free(line);
			return (0);
		}
		free(line);
		val->row++;
		val->ret = get_next_line(val->fd, &line);
	}
	if (line)
		free(line);
	close(val->fd);
	if (val->ret == -1)
		return (0);
	return (1);
}

static void	store_values(char *argv, t_values *val)
{
	char	*line;

	val->fd = open(argv, O_RDONLY);
	val->ret = get_next_line(val->fd, &line);
	val->nbr = ft_calloc(val->row, sizeof(int *));
	val->color = ft_calloc(val->row, sizeof(int *));
	while (val->ret == 1)
	{
		get_line(line, val);
		free(line);
		val->y++;
		val->ret = get_next_line(val->fd, &line);
	}
	if (line)
		free(line);
	close(val->fd);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc == 2)
	{
		if (check_map(argv[1], &fdf.val))
		{
			if (fdf.val.len < 2 || fdf.val.row < 2)
				ft_error();
			mlx_start(&fdf.prg, &fdf.img);
			store_values(argv[1], &fdf.val);
			get_f_amp(&fdf.val);
			ft_draw(&fdf.val, &fdf.img);
			mlx_put_image_to_window(fdf.prg.mlx,
				fdf.prg.mlx_win, fdf.img.img, 0, 0);
			mlx_hook(fdf.prg.mlx_win, 17, 0, close_win, &fdf);
			mlx_hook(fdf.prg.mlx_win, 2, 0, ft_key, &fdf);
			mlx_loop(fdf.prg.mlx);
		}
		else
			ft_error();
	}
	print_instructions();
	return (0);
}
