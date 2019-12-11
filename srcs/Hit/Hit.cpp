/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Hit.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: QFM <quentin.feuillade33@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 14:55:11 by QFM               #+#    #+#             */
/*   Updated: 2019/12/11 15:14:46 by QFM              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Hit.hpp"

Hit::Hit(float t, Vector normal)
{
	this->t = t;
	this->normal = normal;
}

Hit::Hit(Hit const &h)
{
	t = h.t;
	normal = h.normal;
}

Hit::Hit() { }

Hit::~Hit() { }

float		Hit::get_t() const
{
	return (t);
}

Vector		Hit::get_normal() const
{
	return (normal);
}

void		Hit::set_t(float v)
{
	t = v;
}

void		Hit::set_normal(Vector n)
{
	normal = n;
}
