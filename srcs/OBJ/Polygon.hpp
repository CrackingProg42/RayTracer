/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Polygon.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: QFM <quentin.feuillade33@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 19:31:34 by QFM               #+#    #+#             */
/*   Updated: 2019/12/11 16:38:22 by QFM              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "../global.hpp"
#include "../Ray/Ray.hpp"
#include "../Hit/Hit.hpp"

class Polygon
{
private:
	std::map<int, Vector>	vertex; 						// list of vertex that describe the polgon
	bool s; 											// smooth shading

public:
	
	Polygon(bool s, std::map<int, Vector> vert);
	Polygon();
	~Polygon();
	Polygon(Polygon const &);
	
	Polygon 				&operator=(Polygon const &);
	std::map<int, Vector>	get_vertex() const;
	int						get_size() const;
	std::map<int, Vector>	get_real_vertex() const;
	std::map<int, Vector>	get_real_uvs() const;
	std::map<int, Vector>	get_real_normal() const;

	bool					get_s() const;

	Hit						intersect(Ray const &);
};

std::ostream				&operator<<(std::ostream &, const Polygon &);

#endif