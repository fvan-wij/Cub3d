#include <cub3d.h>
#include <math.h>

void	vec_normalize(t_vec_f *vec)
{
	float length = sqrt((vec->x * vec->x) + (vec->y * vec->y));

	vec->x = vec->x / length;
	vec->y = vec->y / length;
}

t_vec_f	vec_assign(double x, double y)
{
	t_vec_f new;

	new.x = x;
	new.y = y;
	return (new);
}

void	vec_rotate(t_vec_f *direction, double angle)
{
	t_vec_f new;

	new.x = (direction->x * cos(angle)) - (direction->y * sin(angle));
	new.y = (direction->x * sin(angle)) + (direction->y * cos(angle));

	direction->x = new.x;
	direction->y = new.y;
}

double	vec_length(t_vec_f vec)
{
	return (sqrt((vec.x * vec.x) + (vec.y * vec.y)));
}

t_vec	vec_to_int(t_vec_f vec)
{
	t_vec int_vec;

	int_vec.x = roundf(vec.x);
	int_vec.y = roundf(vec.y);
	return (int_vec);
}

t_vec_f vec_to_float(t_vec vec)
{
	t_vec_f float_vec;

	float_vec.x = (float) vec.x;
	float_vec.y = (float) vec.y;
	return (float_vec);
}

t_vec_f	vec_divide(t_vec_f vec, double denominator)
{
	vec.x = vec.x / denominator;
	vec.y = vec.y / denominator;
	return (vec);
}

t_vec vec_divide_int(t_vec vec, double denominator)
{
	if (denominator == 2)
	{
		vec.x = vec.x>>1;
		vec.y = vec.y>>1;
		return (vec);
	}
	vec.x = vec.x / denominator;
	vec.y = vec.y / denominator;
	return (vec);
}

t_vec_f vec_min(t_vec_f a, t_vec_f b) 
{
    t_vec_f result;
    result.x = (a.x < b.x) ? a.x : b.x;
    result.y = (a.y < b.y) ? a.y : b.y;
    return result;
}

t_vec_f vec_max(t_vec_f a, t_vec_f b) 
{
    t_vec_f result;
    result.x = (a.x > b.x) ? a.x : b.x;
    result.y = (a.y > b.y) ? a.y : b.y;
    return result;
}

t_vec_f vec_sub(t_vec_f a, t_vec_f b) 
{
    t_vec_f result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    return result;
}

t_vec_f vec_add(t_vec_f a, t_vec_f b) 
{
    t_vec_f result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

t_vec_f vec_mult(t_vec_f a, float scalar)
{
	t_vec_f result;

	result.x = a.x * scalar;
	result.y = a.y * scalar;
	return (result);
}
