/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Obj_group.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: QFM <quentin.feuillade33@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 19:40:44 by QFM               #+#    #+#             */
/*   Updated: 2019/12/09 23:08:47 by QFM              ###   ########.fr       */
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
	polys = obj.polys;
	name = obj.name;
}

Obj_group 		&Obj_group::operator=(Obj_group const & obj)
{
	material = obj.material;
	polys = obj.polys;
	name = obj.name;
	return (*this);
}

Obj_group 		Obj_group::copy()
{
	return (Obj_group(*this));
}

void			Obj_group::push_back(Polygon const &poly)
{
	polys.push_back(poly);
}

std::list<Polygon>		Obj_group::get_polys() const
{
	return (polys);
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
	o << g.get_polys().size();
	o << " polygons in the group : " << g.get_name() << std::endl;
	return (o);
}
