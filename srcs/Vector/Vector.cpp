/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: QFM <quentin.feuillade33@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 19:18:14 by QFM               #+#    #+#             */
/*   Updated: 2019/12/11 13:23:08 by QFM              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vector.hpp"

Vector::Vector() {}

Vector::Vector(float x, float y, float z) : x(x), y(y), z(z) {}

Vector::Vector(float n) : x(n), y(n), z(n) {}

Vector::Vector(Vector const &vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
}

Vector::~Vector() {}

Vector 				&Vector::operator=(Vector const & vec)
{
	if (this != &vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
	}
	return (*this);
}

std::ostream		&operator<<(std::ostream &o, Vector const &v)
{
	o << "x : " << std::to_string(v.getX()) << " ";
	o << "y : " << std::to_string(v.getY()) << " ";
	o << "z : " << std::to_string(v.getZ()) << " ";
	return (o);
}

float			Vector::getX() const
{
	return (x);
}

float			Vector::getY() const
{
	return (y);
}

float			Vector::getZ() const
{
	return (z);
}

float				Vector::dist(Vector const &v)
{
	return (sqrtf(powf(x - v.getX(), 2) + powf(y - v.getY(), 2) + powf(z - v.getZ(), 2)));
}

float				Vector::dot(Vector const &v)
{
	return (v.getX() * x + v.getY() * y + v.getZ() * z);
}

Vector				Vector::cross(Vector const &v)
{
	return (Vector(y * v.getZ() - z * v.getY(), z * v.getX() - x * v.getZ(), x * v.getY() - y * v.getX()));
}

Vector 		Vector::operator+(Vector const & vector)
{
	return (Vector(x + vector.getX(), y + vector.getY(), z + vector.getZ()));
}

Vector 		Vector::operator-(Vector const & vector)
{
	return (Vector(x - vector.getX(), y - vector.getY(), z - vector.getZ()));
}

Vector 		Vector::operator*(Vector const & vector)
{
	return (Vector(x * vector.getX(), y * vector.getY(), z * vector.getZ()));
}

Vector 		Vector::operator/(Vector const & vector)
{
	return (Vector(x / vector.getX(), y / vector.getY(), z / vector.getZ()));
}

Vector 		Vector::operator+(float n)
{
	return (Vector(x + n, y + n, z + n));
}

Vector 		Vector::operator-(float n)
{
	return (Vector(x - n, y - n, z - n));
}

Vector 		Vector::operator*(float n)
{
	return (Vector(x * n, y * n, z * n));
}

Vector 		Vector::operator/(float n)
{
	return (Vector(x / n, y / n, z / n));
}

bool 		Vector::operator==(Vector const & vector)
{
	if (vector.x == x && vector.y == y && vector.z == z)
		return (true);
	return(false);
}

bool 		Vector::operator!=(Vector const & vector)
{
	if (vector.x == x && vector.y == y && vector.z == z)
		return (false);
	return(true);
}