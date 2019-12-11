/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Polygon.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: QFM <quentin.feuillade33@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 12:36:41 by QFM               #+#    #+#             */
/*   Updated: 2019/12/11 15:17:26 by QFM              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Polygon.hpp"

Polygon::Polygon(bool s, std::list<Vector> vert)
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

std::list<Vector>	 Polygon::get_vertex() const
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

std::map<int, Vector>	Polygon::get_real_vertex() const
{
	std::list<Vector>::iterator it = get_vertex().begin();
	std::map<int, Vector> map;
	
	for (int i = 0; i < get_size(); i++)
		map[i] = Vector(g_vertex[(int)(*it).getX()]);
	return (map);
}

std::map<int, Vector>	Polygon::get_real_uvs() const
{
	std::list<Vector>::iterator it = get_vertex().begin();
	std::map<int, Vector> map;
	
	for (int i = 0; i < get_size(); i++)
		map[i] = Vector(g_uvs[(int)(*it).getY()]);
	return (map);
}

std::map<int, Vector>	Polygon::get_real_normal() const
{
	std::list<Vector>::iterator it = get_vertex().begin();
	std::map<int, Vector> map;
	
	for (int i = 0; i < get_size(); i++)
		map[i] = Vector(g_normal[(int)(*it).getZ()]);
	return (map);
}

std::ostream& operator<<(std::ostream &o, const Polygon &p)
{
	std::list<Vector> vertex = p.get_vertex();
	std::list<Vector>::iterator itv = vertex.begin();
	
	o << "The polygon has parameters :" << std::endl;
	for (int i = 0; i < vertex.size(); i++)
	{
		o << "Vertex :" << std::endl; 
		o << g_vertex[(int)(*itv).getX()] << std::endl;
		o << "Normal :" << std::endl;
		o << g_normal[(int)(*itv).getZ()] << std::endl;
		o << "Texture coords :" << std::endl;
		o << g_uvs[(int)(*itv).getY()] << std::endl;
		std::advance(itv, 1);
	}
	if (p.get_s())
		o << "and he has smooth shading on" << std::endl;
	else
		o << "and he has smooth shading off" <<  std::endl;
	return (o);
}

Hit						Polygon::interect(Ray const &r)
{
	float	t = INFINITY;
	Vector	normal(42);

	return (Hit(t, normal));
}
