/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 13:44:01 by robrodri          #+#    #+#             */
/*   Updated: 2021/09/10 11:37:08 by robrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	do_changes(t_fdf *fdf)
{
	mlx_clear_window(fdf->prg.mlx, fdf->prg.mlx_win);
	mlx_destroy_image(fdf->prg.mlx, fdf->img.img);
	mlx_image(&fdf->prg, &fdf->img);
	ft_draw(&fdf->val, &fdf->img);
	mlx_put_image_to_window(fdf->prg.mlx, fdf->prg.mlx_win, fdf->img.img, 0, 0);
}

int	close_win(t_fdf *fdf)
{
	mlx_destroy_window(fdf->prg.mlx, fdf->prg.mlx_win);
	free_matrix(&fdf->val);
	exit (0);
	return (0);
}

void	zoom_changes(t_fdf *fdf, int keycode)
{
	if (keycode == 34 && fdf->val.f_amp < 200)
	{
		fdf->val.f_amp += 2;
		do_changes(fdf);
	}
	else if (keycode == 31 && fdf->val.f_amp > 0)
	{
		fdf->val.f_amp -= 2;
		do_changes(fdf);
	}
}

void	dsp_changes(t_fdf *fdf, int keycode)
{
	if (keycode == 123)
	{
		fdf->val.shift_x += 2;
		do_changes(fdf);
	}
	else if (keycode == 124)
	{
		fdf->val.shift_x -= 2;
		do_changes(fdf);
	}
	else if (keycode == 125)
	{
		fdf->val.shift_y -= 2;
		do_changes(fdf);
	}
	else if (keycode == 126)
	{
		fdf->val.shift_y += 2;
		do_changes(fdf);
	}
}

void	print_instructions(void)
{
	ft_putstr("Welcome to FDF by Robrodri\n");
	write(1, "\n", 1);
	ft_putstr("This FDF will try to fit your image inside the given window\n");
	ft_putstr("If you image is too tall and can barely be seen, don't worry\n");
	ft_putstr("Remember to include a map this way : ./fdf [your_map]\n");
	ft_putstr("You can addapt the scale and position using the controls : \n");
	ft_putstr("-Zoom in    :	'i'\n");
	ft_putstr("-Zoom out   :	'o'\n");
	ft_putstr("-Move right :	'→'\n");
	ft_putstr("-Move left  :	'←'\n");
	ft_putstr("-Move Up    :	'↑'\n");
	ft_putstr("-Move Down  :	'↓'\n");
}
