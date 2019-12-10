/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: QFM <quentin.feuillade33@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 19:18:05 by QFM               #+#    #+#             */
/*   Updated: 2019/12/10 16:22:30 by QFM              ###   ########.fr       */
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
	~Vector();
	Vector(Vector const & vector);

	Vector 		&operator=(Vector const & vector);

	float getX() const;
	float getY() const;
	float getZ() const;

	float		dot(Vector const &);
	Vector		cross(Vector const &);

	float		dist(Vector const &);

private:

	float 		x;
	float 		y;
	float 		z;
};

std::ostream& operator<<(std::ostream &, const Vector &);

#endif