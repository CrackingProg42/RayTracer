/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Obj_group.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 19:29:52 by QFM               #+#    #+#             */
/*   Updated: 2019/12/14 14:49:50 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_GROUP_HPP
#define OBJ_GROUP_HPP

#include "../global.hpp"
#include "Polygon.hpp"
#include "../Hit/Hit.hpp"

class Obj_group
{
private:

	Material			material;
	std::list<Polygon>	polyv;
	std::list<Polygon>	polyn;
	std::list<Polygon>	polyu;
	std::string			name;

public:

	Obj_group(Material mat, std::string);
	Obj_group();
	~Obj_group();
	Obj_group(Obj_group const &);
	
	Obj_group 		&operator=(Obj_group const &);

	Obj_group		copy();

	std::list<Polygon>		get_polyv() const;
	std::list<Polygon>		get_polyn() const;
	std::list<Polygon>		get_polyu() const;
	void					push_back_v(Polygon const &poly);
	void					push_back_n(Polygon const &poly);
	void					push_back_u(Polygon const &poly);
	Material				get_material() const;
	std::string				get_name() const;
	Hit						intersect(Ray const &);
	
};

std::ostream			&operator<<(std::ostream &, const Obj_group &);

#endif