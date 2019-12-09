/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: QFM <quentin.feuillade33@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 19:18:14 by QFM               #+#    #+#             */
/*   Updated: 2019/12/08 13:37:32 by QFM              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vector.hpp"

Vector::Vector() {}

Vector::Vector(float x, float y, float z) : x(x), y(y), z(z) {}

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

float const			Vector::getX() const
{
	return (x);
}

float const			Vector::getY() const
{
	return (y);
}

float const			Vector::getZ() const
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

