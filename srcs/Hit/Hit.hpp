/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Hit.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: QFM <quentin.feuillade33@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 14:55:08 by QFM               #+#    #+#             */
/*   Updated: 2019/12/11 15:14:54 by QFM              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	HIT_HPP
#define HIT_HPP

#include "../global.hpp"

class	Hit
{
private :

	float	t;
	Vector	normal;

public :

	Hit(float t, Vector normal);
	Hit(Hit	const &);
	Hit();
	~Hit();
	
	float		get_t() const;
	Vector		get_normal() const;
	void		set_t(float);
	void		set_normal(Vector);

};

#endif