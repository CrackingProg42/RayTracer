/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Polygon.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: QFM <quentin.feuillade33@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 12:36:41 by QFM               #+#    #+#             */
/*   Updated: 2019/12/11 22:36:42 by QFM              ###   ########.fr       */
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
	float	t = INFINITY;
	Vector	normal = (vertex[1] - vertex[0]).cross(vertex[2] - vertex[0]).normalize();
	
	float NdotRayDirection = normal.dot(r.get_dir()); 
    if (fabs(NdotRayDirection) < EPSILON) // almost 0 
        return Hit(INFINITY, Vector(42)); // they are parallel so they don't intersect 
	
	float	d = normal.dot(vertex[0]);
	
	t =  (normal.dot(r.get_pos()) + d) / NdotRayDirection; 
	if (t < 0) return Hit(INFINITY, Vector(42));
	
    Vector Answer = r.get_pos() + r.get_dir() * t;

    // verify that the point falls inside the polygon
	/*
    Vector test_line = Answer - vertex[0];
    Vector test_axis = normal.cross(test_line);

    bool point_is_inside = false;

    Vector test_point = vertex[1] - Answer;
    bool prev_point_ahead = (test_line.dot(test_point) > 0);
    bool prev_point_above = (test_axis.dot(test_point) > 0);

    bool this_point_ahead;
    bool this_point_above;

    int index = 2;
    while (index < vertex.size())
    {
        test_point = vertex[index] - Answer;
        this_point_ahead = (test_line.dot(test_point) > 0);

        if (prev_point_ahead || this_point_ahead)
        {
            this_point_above = (test_axis.dot(test_point) > 0);

            if (prev_point_above != this_point_above)
            {
                point_is_inside = !point_is_inside;
            }
        }
		
        prev_point_ahead = this_point_ahead;
        prev_point_above = this_point_above;
        index++;
    }
	if (!point_is_inside)
    	return (Hit(INFINITY, Vector(42)));*/
	return (Hit(t, normal));
}
