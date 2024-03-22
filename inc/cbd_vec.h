#ifndef CBD_VEC_H
# define CBD_VEC_H

typedef struct 	s_vec2i {
	int	x;
	int y;
}	t_vec2i;

typedef struct 	s_vec2d {
	double	x;
	double	y;
}	t_vec2d;

void	vec_normalize(t_vec2d *vec);
double	vec_length(t_vec2d vec);
t_vec2d	vec_assign(double x, double y);
t_vec2i	vec2i_assign(double x, double y);
t_vec2d	vec_rotate(t_vec2d direction, double angle);
t_vec2i	vec_to_int(t_vec2d vec);
t_vec2d	vec_to_float(t_vec2i vec);
t_vec2d	vec_divide(t_vec2d vec, double denominator);
t_vec2i vec_divide_int(t_vec2i vec, double denominator);
t_vec2d vec_min(t_vec2d a, t_vec2d b);
t_vec2d vec_max(t_vec2d a, t_vec2d b);
t_vec2d vec_sub(t_vec2d a, t_vec2d b);
t_vec2d vec_add(t_vec2d a, t_vec2d b);
t_vec2d vec_mult(t_vec2d a, float scalar);
double	vec_dot(t_vec2d a, t_vec2d b);
double	vec_distance(t_vec2d a, t_vec2d b);

#endif //CBD_VEC_H
