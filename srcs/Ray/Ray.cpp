/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ray.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: QFM <quentin.feuillade33@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 12:46:27 by QFM               #+#    #+#             */
/*   Updated: 2019/12/11 13:42:53 by QFM              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ray.hpp"

Ray::Ray(Vector p, Vector d) 
{
	pos = p;
	dir = d;
}

Ray::Ray(Ray const &r)
{
	pos = r.pos;
	dir = r.dir;
}

Ray::Ray() { }

Vector	Ray::get_pos(void) const
{
	return (pos);	
}

Vector	Ray::get_dir(void) const
{
	return (dir);
}

Ray::~Ray() { }