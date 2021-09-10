/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 14:44:30 by robrodri          #+#    #+#             */
/*   Updated: 2021/08/24 14:24:27 by robrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_is_space(char a)
{
	if ((a >= 9 && a <= 13) || a == ' ')
		return (1);
	return (0);
}

int	ft_is_sign(char a)
{
	if (a == '+' || a == '-')
		return (1);
	return (0);
}

int	ft_split_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	is_hexa(char *line, t_values *val)
{
	int	i;

	val->pos++;
	if (line[val->pos] != '0' || line[val->pos + 1] != 'x')
		return (0);
	val->pos += 2;
	i = 0;
	while (ft_isdigit(line[val->pos]) || ft_isalpha(line[val->pos]))
	{
		i++;
		val->pos++;
	}
	if ((!ft_is_space(line[val->pos]) && line[val->pos] != 0)
		|| i > 6)
		return (0);
	return (1);
}

void	ft_init_struct_val(t_values *val)
{
	val->len = 0;
	val->row = 0;
	val->y = 0;
	val->shift_x = 0;
	val->shift_y = 0;
}
