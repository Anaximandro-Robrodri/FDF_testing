/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_maths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 15:56:06 by robrodri          #+#    #+#             */
/*   Updated: 2021/09/05 15:56:08 by robrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_bresenham(t_axis *axis, t_data *data, int color)
{
	float	x_step;
	float	y_step;
	int		step;

	x_step = axis->x_1 - axis->x_0;
	y_step = axis->y_1 - axis->y_0;
	step = sqrt((pow(x_step, 2) + pow(y_step, 2)));
	x_step /= step;
	y_step /= step;
	while (step > 0)
	{
		if ((axis->x_0 > 0 && axis->x_0 < WIN_L)
			&& (axis->y_0 > 0 && axis->y_0 < WIN_H))
			my_pixel_put(data, axis->x_0, axis->y_0, color);
		axis->x_0 += x_step;
		axis->y_0 += y_step;
		step--;
	}
}

static void	ft_draw_horizontal(t_axis *x, t_draw c, t_data *d, t_values *v)
{
	x->x_0 = ((c.x - 1) * v->f_amp);
	x->x_1 = (c.x * v->f_amp);
	x->y_0 = (c.y * v->f_amp);
	x->y_1 = x->y_0;
	perspec(&x->x_0, &x->y_0, (v->nbr[c.y][c.x - 1]) * (v->f_amp / 1.25), v);
	perspec(&x->x_1, &x->y_1, (v->nbr[c.y][c.x]) * (v->f_amp / 1.25), v);
	ft_bresenham(x, d, v->color[c.y][c.x - 1]);
}

static void	ft_draw_vertical(t_axis *x, t_draw c, t_data *d, t_values *v)
{
	x->x_0 = (c.x * v->f_amp);
	x->x_1 = x->x_0;
	x->y_0 = ((c.y - 1) * v->f_amp);
	x->y_1 = (c.y * v->f_amp);
	perspec(&x->x_0, &x->y_0, (v->nbr[c.y - 1][c.x]) * (v->f_amp / 1.25), v);
	perspec(&x->x_1, &x->y_1, (v->nbr[c.y][c.x]) * (v->f_amp / 1.25), v);
	ft_bresenham(x, d, v->color[c.y - 1][c.x]);
}

int	ft_draw(t_values *val, t_data *data)
{
	t_draw	crd;
	t_axis	axis;

	crd.y = 0;
	while (crd.y < val->row)
	{
		crd.x = 0;
		while (crd.x < val->len)
		{
			if (crd.x != 0)
				ft_draw_horizontal(&axis, crd, data, val);
			if (crd.y != 0)
				ft_draw_vertical(&axis, crd, data, val);
			crd.x++;
		}
		crd.y++;
	}
	return (0);
}
