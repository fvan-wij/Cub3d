#include <cub3d.h>
#include <math.h>

double	vec_dot(t_vec2d a, t_vec2d b)
{
	return ((a.x * b.x) + (a.y * b.y));
}

double	vec_distance(t_vec2d a, t_vec2d b)
{
	return (sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2)));
}

void	vec_normalize(t_vec2d *vec)
{
	float length = sqrt((vec->x * vec->x) + (vec->y * vec->y));

	vec->x = vec->x / length;
	vec->y = vec->y / length;
}

t_vec2d	vec_assign(double x, double y)
{
	t_vec2d new;

	new.x = x;
	new.y = y;
	return (new);
}

t_vec2i	vec2i_assign(double x, double y)
{
	t_vec2i new;

	new.x = x;
	new.y = y;
	return (new);

}

t_vec2d	vec_rotate(t_vec2d direction, double angle)
{
	t_vec2d new;

	new.x = (direction.x * cos(angle)) - (direction.y * sin(angle));
	new.y = (direction.x * sin(angle)) + (direction.y * cos(angle));

	direction.x = new.x;
	direction.y = new.y;
	return new;
}

double	vec_length(t_vec2d vec)
{
	return (sqrt((vec.x * vec.x) + (vec.y * vec.y)));
}

t_vec2i	vec_to_int(t_vec2d vec)
{
	t_vec2i int_vec;

	int_vec.x = roundf(vec.x);
	int_vec.y = roundf(vec.y);
	return (int_vec);
}

t_vec2d vec_to_float(t_vec2i vec)
{
	t_vec2d float_vec;

	float_vec.x = (float) vec.x;
	float_vec.y = (float) vec.y;
	return (float_vec);
}

t_vec2d	vec_divide(t_vec2d vec, double denominator)
{
	vec.x = vec.x / denominator;
	vec.y = vec.y / denominator;
	return (vec);
}

t_vec2i vec_divide_int(t_vec2i vec, double denominator)
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

t_vec2d vec_min(t_vec2d a, t_vec2d b)
{
    t_vec2d result;

	if (a.x < b.x)
		result.x = a.x;
	else
		result.x = b.x;

	if (a.y < b.y)
		result.y = a.y;
	else
		result.y = b.y;
    return (result);
}

t_vec2d vec_max(t_vec2d a, t_vec2d b)
{
    t_vec2d result;

	if (a.x > b.x)
		result.x = a.x;
	else
		result.x = b.x;

	if (a.y > b.y)
		result.y = a.y;
	else
		result.y = b.y;
    return (result);
}

t_vec2d vec_sub(t_vec2d a, t_vec2d b)
{
    t_vec2d result;

    result.x = a.x - b.x;
    result.y = a.y - b.y;
    return (result);
}

t_vec2d vec_add(t_vec2d a, t_vec2d b)
{
    t_vec2d result;

    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return (result);
}

t_vec2d vec_mult(t_vec2d a, float scalar)
{
	t_vec2d result;

	result.x = a.x * scalar;
	result.y = a.y * scalar;
	return (result);
}
