/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ray.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: QFM <quentin.feuillade33@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 12:46:25 by QFM               #+#    #+#             */
/*   Updated: 2019/12/11 13:41:35 by QFM              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_HPP
#define RAY_HPP

#include "../global.hpp"

class Ray
{
private:

	Vector pos;
	Vector dir;

public:

	Ray();
	Ray(Vector pos, Vector dir);
	~Ray();
	Ray(Ray const &);

	Vector	get_pos(void) const;
	Vector	get_dir(void) const;
};

#endif