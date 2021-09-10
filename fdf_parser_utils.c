/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 14:44:19 by robrodri          #+#    #+#             */
/*   Updated: 2021/09/05 18:07:00 by robrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_len(char *line, t_values *val)
{
	char	**split;
	int		j;

	j = 0;
	split = ft_split(line, ' ');
	if (!val->len)
		val->len = ft_split_len(split);
	if (val->len != ft_split_len(split))
		val->len = 0;
	while (split[j])
	{
		free(split[j]);
		j++;
	}
	free(split);
	if (val->len == 0)
		return (0);
	return (1);
}

int	ft_error_control(char *line, t_values *val)
{
	val->pos = 0;
	while (line[val->pos])
	{
		if (!ft_isdigit(line[val->pos]) && !ft_is_space(line[val->pos])
			&& !ft_is_sign(line[val->pos]) && line[val->pos] != ',')
			return (0);
		if (line[val->pos] == ',')
		{
			if (!is_hexa(line, val))
				return (0);
		}
		if (ft_is_sign(line[val->pos]))
		{
			if (!ft_isdigit(line[val->pos + 1]) || !line[val->pos + 1])
				return (0);
			val->pos++;
		}
		if (line[val->pos])
			val->pos++;
	}
	return (1);
}

static void	check_window_h(t_axis *x, t_draw *c, t_values *v)
{
	x->x_0 = (c->x - 1) * v->f_amp;
	x->x_1 = c->x * v->f_amp;
	x->y_0 = c->y * v->f_amp;
	x->y_1 = x->y_0;
	perspec(&x->x_0, &x->y_0, (v->nbr[c->y][c->x - 1]) * (v->f_amp / 1.25), v);
	perspec(&x->x_1, &x->y_1, (v->nbr[c->y][c->x]) * (v->f_amp / 1.25), v);
	if (x->x_0 > WIN_L || x->x_1 > WIN_L || x->y_0 > WIN_H || x->y_1 > WIN_H
		|| x->x_0 < 0 || x->x_1 < 0 || x->y_0 < 0 || x->y_1 < 0)
	{
		c->x = 0;
		c->y = 0;
		v->f_amp -= 2;
	}
}

static void	check_window_v(t_axis *x, t_draw *c, t_values *v)
{
	x->x_0 = c->x * v->f_amp;
	x->x_1 = x->x_0;
	x->y_0 = (c->y - 1) * v->f_amp;
	x->y_1 = c->y * v->f_amp;
	perspec(&x->x_0, &x->y_0, (v->nbr[c->y - 1][c->x]) * (v->f_amp / 1.25), v);
	perspec(&x->x_1, &x->y_1, (v->nbr[c->y][c->x]) * (v->f_amp / 1.25), v);
	if (x->x_0 > WIN_L || x->x_1 > WIN_L || x->y_0 > WIN_H || x->y_1 > WIN_H
		|| x->x_0 < 0 || x->x_1 < 0 || x->y_0 < 0 || x->y_1 < 0)
	{
		c->x = 0;
		c->y = 0;
		v->f_amp -= 2;
	}
}

void	get_f_amp(t_values *val)
{
	t_draw	crd;
	t_axis	axis;

	val->f_amp = 200;
	crd.y = 0;
	while (crd.y < val->row)
	{
		crd.x = 0;
		while (crd.x < val->len)
		{
			if (crd.x != 0)
				check_window_h(&axis, &crd, val);
			if (crd.y != 0)
				check_window_v(&axis, &crd, val);
			crd.x++;
		}
		crd.y++;
	}
	if (val->f_amp < 1)
		val->f_amp = 50;
}
