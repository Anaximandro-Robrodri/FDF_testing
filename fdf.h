/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 14:44:12 by robrodri          #+#    #+#             */
/*   Updated: 2021/09/10 13:52:18 by robrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define WIN_L 1920
# define WIN_H 1080
# define MAX_H 500
# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "./libft/libft.h"

typedef struct s_program
{
	void	*mlx;
	void	*mlx_win;
}	t_program;

typedef struct s_data
{
	void	*img;
	char	*ptr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_values
{
	int		len;
	int		ret;
	int		row;
	int		pos;
	int		fd;
	int		f_amp;
	int		**nbr;
	int		**color;
	int		y;
	int		shift_x;
	int		shift_y;
}	t_values;

typedef struct s_axis
{
	float		x_0;
	float		x_1;
	float		y_0;
	float		y_1;
}	t_axis;

typedef struct s_draw
{
	int	x;
	int	y;
}	t_draw;

typedef struct s_fdf
{
	t_values	val;
	t_data		img;
	t_program	prg;
}	t_fdf;

int		ft_is_space(char a);
int		ft_is_sign(char a);
int		is_hexa(char *line, t_values *val);
void	ft_init_struct_val(t_values *val);
int		ft_error_control(char *line, t_values *val);
int		get_len(char *line, t_values *val);
int		ft_split_len(char **str);
void	get_line(char *line, t_values *val);
void	ft_draw(t_values *val, t_data *data);
void	get_f_amp(t_values *val);
void	perspec(float *x, float *y, int z, t_values *val);
void	free_matrix(t_values *val);
void	print_instructions(void);
void	my_pixel_put(t_data *data, int x, int y, int color);
void	mlx_start(t_program *mlx_p, t_data *img);
int		ft_key(int keycode, t_fdf *fdf);
void	zoom_changes(t_fdf *fdf, int keycode);
void	dsp_changes(t_fdf *fdf, int keycode);
void	mlx_image(t_program *mlx_p, t_data *img);
int		close_win(t_fdf *fdf);
#endif
