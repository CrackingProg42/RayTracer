/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: QFM <quentin.feuillade33@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 19:18:05 by QFM               #+#    #+#             */
/*   Updated: 2019/12/11 13:52:29 by QFM              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <math.h>

class Vector 
{
public :

	Vector();
	Vector(float x, float y, float z);
	Vector(float n);
	~Vector();
	Vector(Vector const & vector);

	Vector 		&operator=(Vector const & vector);

	float getX() const;
	float getY() const;
	float getZ() const;

	Vector 		operator+(Vector const & vector);
	Vector 		operator-(Vector const & vector);
	Vector 		operator*(Vector const & vector);
	Vector 		operator/(Vector const & vector);
	Vector 		operator+(float n);
	Vector 		operator-(float n);
	Vector 		operator*(float n);
	Vector 		operator/(float n);
	bool 		operator==(Vector const & vector);
	bool 		operator!=(Vector const & vector);

	float		dot(Vector const &);
	Vector		cross(Vector const &);
	Vector		normalize();
	float		dist(Vector const &);

private:

	float 		x;
	float 		y;
	float 		z;
};

std::ostream& operator<<(std::ostream &, const Vector &);

#endif