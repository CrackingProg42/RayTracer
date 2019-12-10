/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Material.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: QFM <quentin.feuillade33@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 14:19:03 by QFM               #+#    #+#             */
/*   Updated: 2019/12/10 16:22:01 by QFM              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "../Vector/Vector.hpp"

class Material
{
public :

	Material(float Ns, float Ni, float d, int illum, Vector Ka, Vector Kd, Vector Ks, Vector Ke);
	Material();
	~Material();
	Material(Material const &);

	Material 				&operator=(Material const &);

	float		get_Ns() const;
	float		get_Ni() const;
	float		get_d() const;
	Vector		get_Kd() const;
	Vector		get_Ks() const;
	Vector		get_Ke() const;
	Vector		get_Ka() const;
	int			get_illum() const;

	void		set_Ns(float);
	void		set_Ni(float);
	void		set_d(float);
	void		set_Kd(Vector);
	void		set_Ks(Vector);
	void		set_Ke(Vector);
	void		set_Ka(Vector);
	void		set_illum(int);

private :

	float Ns, Ni, d;
	Vector Ka, Kd, Ks, Ke;
	int	illum;

/*
newmtl Material_#144
Ns 179.999996
Ka 1.000000 1.000000 1.000000
Kd 0.000000 0.000000 0.000000
Ks 1.000000 1.000000 1.000000
Ke 0.000000 0.000000 0.000000
Ni 1.450000
d 0.630588
illum 6
*/

};

#endif