/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Material.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: QFM <quentin.feuillade33@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 14:18:25 by QFM               #+#    #+#             */
/*   Updated: 2019/12/10 17:41:17 by QFM              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Material.hpp"

Material::Material(float Ns, float Ni, float d, int illum, Vector Ka, Vector Kd, Vector Ks, Vector Ke) : Ns(Ns), Ni(Ni), d(d), illum(illum), Ka(Ka), Kd(Kd), Ks(Ks), Ke(Ke) { }

Material::Material() { }

Material::~Material() { }

Material::Material(Material const &mat)
{
	Ns = mat.get_Ns();
	Ni = mat.get_Ni();
	d = mat.get_d();
	illum = mat.get_illum();
	Ka = mat.get_Ka();
	Kd = mat.get_Kd();
	Ks = mat.get_Ks();
	Ke = mat.get_Ke();
}

Material 	&Material::operator=(Material const &mat)
{
	Ns = mat.get_Ns();
	Ni = mat.get_Ni();
	d = mat.get_d();
	illum = mat.get_illum();
	Ka = mat.get_Ka();
	Kd = mat.get_Kd();
	Ks = mat.get_Ks();
	Ke = mat.get_Ke();
	return(*this);
}

Material 		Material::copy()
{
	return (Material(*this));
}

float		Material::get_Ns() const
{
	return (Ns);
}

float		Material::get_Ni() const
{
	return (Ni);
}

float		Material::get_d() const
{
	return (d);
}

Vector		Material::get_Kd() const
{
	return (Kd);
}

Vector		Material::get_Ks() const
{
	return (Ks);
}

Vector		Material::get_Ke() const
{
	return (Ke);
}

Vector		Material::get_Ka() const
{
	return (Ka);
}

int			Material::get_illum() const
{
	return (illum);
}

void		Material::set_Ns(float val)
{
	Ns = val;
}

void		Material::set_Ni(float val)
{
	Ni = val;
}

void		Material::set_d(float val)
{
	d = val;
}

void		Material::set_Kd(Vector val)
{
	Kd = val;
}

void		Material::set_Ks(Vector val)
{
	Ks = val;
}

void		Material::set_Ke(Vector val)
{
	Ke = val;
}

void		Material::set_Ka(Vector val)
{
	Ka = val;
}

void		Material::set_illum(int val)
{
	illum = val;
}

