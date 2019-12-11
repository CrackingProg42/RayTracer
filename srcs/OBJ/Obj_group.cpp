/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Obj_group.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: QFM <quentin.feuillade33@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 19:40:44 by QFM               #+#    #+#             */
/*   Updated: 2019/12/11 16:47:10 by QFM              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Obj_group.hpp"

Obj_group::Obj_group(Material mat, std::string nme)
{
	material = mat;
	name = nme;
}

Obj_group::Obj_group() {}

Obj_group::~Obj_group() {}


Obj_group::Obj_group(Obj_group const & obj)
{
	material = obj.material;
	polyv = obj.polyv;
	polyn = obj.polyn;
	polyu = obj.polyu;
	name = obj.name;
}

Obj_group 		&Obj_group::operator=(Obj_group const & obj)
{
	material = obj.material;
	polyv = obj.polyv;
	polyn = obj.polyn;
	polyu = obj.polyu;
	name = obj.name;
	return (*this);
}

Obj_group 		Obj_group::copy()
{
	return (Obj_group(*this));
}

void			Obj_group::push_back_v(Polygon const &poly)
{
	polyv.push_back(poly);
}

void			Obj_group::push_back_n(Polygon const &poly)
{
	polyn.push_back(poly);
}

void			Obj_group::push_back_u(Polygon const &poly)
{
	polyu.push_back(poly);
}

std::list<Polygon>		Obj_group::get_polyv() const
{
	return (polyv);
}

std::list<Polygon>		Obj_group::get_polyn() const
{
	return (polyn);
}

std::list<Polygon>		Obj_group::get_polyu() const
{
	return (polyu);
}


std::string		Obj_group::get_name() const
{
	return (name);
}

Material				Obj_group::get_material() const
{
	return (material);
}

std::ostream			&operator<<(std::ostream &o, const Obj_group &g)
{
	o << "There is : ";
	o << g.get_polyv().size();
	o << " polygons in the group : " << g.get_name() << std::endl;
	return (o);
}

Hit						Obj_group::intersect(Ray const &r)
{
	std::list<Polygon>::iterator	it = polyv.begin();
	Hit	min = Hit(INFINITY, Vector(42));
	Hit hit;

	for (int i = 0; i < polyv.size(); i++)
	{
		hit = (*it).intersect(r);
		if (hit.get_t() < min.get_t() && hit.get_t() >= 0)
			min = hit;
		std::advance(it, 1);
	}
	return (min);
}
