/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: QFM <quentin.feuillade33@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 13:35:02 by QFM               #+#    #+#             */
/*   Updated: 2019/12/09 00:52:54 by QFM              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <iostream>
#include <list>
#include <map>
#include "Vector/Vector.hpp"
#include "Material/Material.hpp"
#include <fstream>

extern std::map<int, Vector>				g_normal;				// must start at index 1 !!
extern std::map<int, Vector>				g_uvs;					// must start at index 1 !!
extern std::map<int, Vector>				g_vertex;				// must start at index 1 !!
extern std::map<std::string, Material> 	materials;					// list of all material

#endif