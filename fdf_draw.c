/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 15:55:08 by robrodri          #+#    #+#             */
/*   Updated: 2021/09/05 18:07:04 by robrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	hex_to_dec(char *aux, int i)
{
	int	len;
	int	dec;
	int	base;

	len = ft_strlen(aux) - 1;
	dec = 0;
	base = 1;
	while (len != i + 1)
	{
		if (ft_isdigit(aux[len]))
			dec += (aux[len] - 48) * base;
		else if (aux[len] >= 'A' && aux[len] <= 'F')
			dec += (aux[len] - 55) * base;
		else if (aux[len] >= 'a' && aux[len] <= 'f')
			dec += (aux[len] - 87) * base;
		base *= 16;
		len--;
	}
	return (dec);
}

static void	get_color(char *aux, t_values *val, int j)
{
	int	i;

	i = 0;
	while (aux[i])
	{
		if (aux[i] == ',')
		{
			val->color[val->y][j] = hex_to_dec(aux, i);
			return ;
		}
		i++;
	}
	val->color[val->y][j] = 0xFFFFFF;
}

void	get_line(char *line, t_values *val)
{
	char	**aux;
	int		i;

	aux = ft_split(line, ' ');
	val->nbr[val->y] = ft_calloc(val->len, sizeof(int));
	val->color[val->y] = ft_calloc(val->len, sizeof(int));
	i = 0;
	while (aux[i])
	{
		val->nbr[val->y][i] = ft_atoi(aux[i]);
		get_color(aux[i], val, i);
		free(aux[i]);
		i++;
	}
	free(aux);
}

void	perspec(float *x, float *y, int z, t_values *val)
{
	int	x_aux;
	int	y_aux;
	int	x_dsp;
	int	y_dsp;

	x_aux = *x;
	y_aux = *y;
	y_dsp = (val->row * val->f_amp) / 2;
	if (val->len == val->row)
		x_dsp = 0;
	else
		x_dsp = ((val->len - val->row) * val->f_amp) / 2;
	*x = (((x_aux - y_aux) * cos(0.523599))
			+ (WIN_L / 2) - x_dsp) - val->shift_x;
	*y = ((-z + (x_aux + y_aux) * sin(0.523599))
			+ ((WIN_H / 2) - y_dsp)) - val->shift_y;
}
