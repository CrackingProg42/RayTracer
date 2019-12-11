/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Obj.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: QFM <quentin.feuillade33@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 19:21:28 by QFM               #+#    #+#             */
/*   Updated: 2019/12/11 16:42:39 by QFM              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_HPP
#define OBJ_HPP

#include "Obj_group.hpp"
#include "../global.hpp"
#include <cstdio>

class Obj
{
public :	

	Obj(std::string file, float si);
	Obj();
	~Obj();
	Obj(Obj const &);

	Obj 					&operator=(Obj const &);

	std::list<Obj_group>	get_groups() const;
	Hit						intersect(Ray const &r);

private:

	std::map<int, Vector>	vertex;
	std::map<int, Vector>	normal;
	std::map<int, Vector>	uvs;
	std::list<Obj_group> 	groups;
	std::string 			name;
	float					size;
};

std::ostream			&operator<<(std::ostream &, const Obj &);

#endif