/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Obj.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: QFM <quentin.feuillade33@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 19:21:28 by QFM               #+#    #+#             */
/*   Updated: 2019/12/10 15:40:19 by QFM              ###   ########.fr       */
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

	Obj(std::string file);
	Obj();
	~Obj();
	Obj(Obj const &);

	Obj 				&operator=(Obj const &);

	std::list<Obj_group>	get_groups() const;	

private:

	std::list<Obj_group> groups;
	std::string name;

};

std::ostream			&operator<<(std::ostream &, const Obj &);

#endif