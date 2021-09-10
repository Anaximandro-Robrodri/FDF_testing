/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 15:08:10 by robrodri          #+#    #+#             */
/*   Updated: 2021/09/10 11:33:45 by robrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->ptr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	mlx_image(t_program *mlx_p, t_data *img)
{
	img->img = mlx_new_image(mlx_p->mlx, WIN_L, WIN_H);
	img->ptr = mlx_get_data_addr(img->img, &img->bpp,
			&img->line_length, &img->endian);
}

void	mlx_start(t_program *mlx_p, t_data *img)
{
	mlx_p->mlx = mlx_init();
	mlx_p->mlx_win = mlx_new_window(mlx_p->mlx, WIN_L, WIN_H, "FDF");
	mlx_image(mlx_p, img);
}

int	ft_key(int keycode, t_fdf *fdf)
{
	if (keycode == 53)
	{
		mlx_destroy_image(fdf->prg.mlx, fdf->img.img);
		mlx_destroy_window(fdf->prg.mlx, fdf->prg.mlx_win);
		free_matrix(&fdf->val);
		exit(0);
	}
	else if ((keycode == 34 && fdf->val.f_amp < 200)
		|| (keycode == 31 && fdf->val.f_amp > 0))
		zoom_changes(fdf, keycode);
	else if (keycode == 124 || keycode == 123
		|| keycode == 126 || keycode == 125)
		dsp_changes(fdf, keycode);
	return (0);
}
