/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Obj_group.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: QFM <quentin.feuillade33@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 19:29:52 by QFM               #+#    #+#             */
/*   Updated: 2019/12/09 13:34:15 by QFM              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_GROUP_HPP
#define OBJ_GROUP_HPP

#include "../global.hpp"
#include "Polygon.hpp"

class Obj_group
{
private:

	Material			material;
	std::list<Polygon>	polys;
	std::string			name;

public:

	Obj_group(Material mat, std::string);
	Obj_group();
	~Obj_group();
	Obj_group(Obj_group const &);
	
	Obj_group 		&operator=(Obj_group const &);

	Obj_group		copy();

	void			push_back(Polygon const &);
	std::list<Polygon>		get_polys() const;
	Material				get_material() const;
	std::string				get_name() const;
	
};

std::ostream			&operator<<(std::ostream &, const Obj_group &);

#endif