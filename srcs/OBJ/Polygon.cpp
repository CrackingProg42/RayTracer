/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Polygon.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 12:36:41 by QFM               #+#    #+#             */
/*   Updated: 2019/12/14 14:08:13 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Polygon.hpp"

#define EPSILON 10e-10

Polygon::Polygon(bool s, std::map<int, Vector> vert)
{
	vertex = vert;
	s = s;
}

Polygon::Polygon() {}

Polygon::~Polygon() {}

Polygon::Polygon(Polygon const & poly)
{
	s = poly.s;
	vertex = poly.vertex;
}

Polygon 		&Polygon::operator=(Polygon const &pol)
{
	s = pol.s;
	vertex = pol.vertex;
	return (*this);
}

std::map<int, Vector>	 Polygon::get_vertex() const
{
	return (vertex);
}

bool				Polygon::get_s() const
{
	return (s);
}

int					Polygon::get_size() const
{
	return (vertex.size());
}

std::ostream& operator<<(std::ostream &o, const Polygon &p)
{
	std::map<int, Vector> vertex = p.get_vertex();
	
	o << "The polygon has parameters :" << std::endl;
	for (int i = 0; i < vertex.size(); i++)
	{
		o << "Vertex :" << std::endl; 
		o << vertex[i] << std::endl;
	}
	if (p.get_s())
		o << "and he has smooth shading on" << std::endl;
	else
		o << "and he has smooth shading off" <<  std::endl;
	return (o);
}

Hit						Polygon::intersect(Ray const &r)
{
	Vector	e1;
	Vector	e2;
	Vector	tvec;
	Vector	pvec;
	Vector	qvec;

	e1 = vertex[1] - vertex[0];
	e2 = vertex[2] - vertex[0];
	if (e1.dot(pvec = r.get_dir().cross(e2)) > -1e-8 && e1.dot(pvec) < 1e-8)
		return Hit(INFINITY, Vector(0));
	if ((tvec = r.get_pos() - vertex[0]).dot(pvec) * \
		(1 / e1.dot(pvec)) < 0 || tvec.dot(pvec) * (1 / e1.dot(pvec)) > 1)
		return Hit(INFINITY, Vector(0));
	qvec = tvec.cross(e1);
	if (r.get_dir().dot(qvec) * (1 / e1.dot(pvec)) < 0 || tvec.dot(pvec) * \
		(1 / e1.dot(pvec)) + r.get_dir().dot(qvec) * (1 / e1.dot(pvec)) > 1)
		return Hit(INFINITY, Vector(0));
	float t = e2.dot(qvec) * (1 / e1.dot(pvec));
	qvec = e1.cross(e2);
	tvec = qvec.normalize();
	// process_normal(r, tvec);
	return (Hit(t, tvec));
}
