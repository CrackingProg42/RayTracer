/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_parser.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: QFM <quentin.feuillade33@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 17:10:42 by QFM               #+#    #+#             */
/*   Updated: 2019/12/11 12:05:49 by QFM              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.hpp"


// return -1 if an error occure
int		material_parser(std::string	mtl_name)
{
	FILE 		*mtl = fopen(mtl_name.c_str(), "r");
	char		tm[2000];
	char		mat_name[2000];

	Material 	tmp;

	float		x = INFINITY, y, z;
	int			illum;

	while (std::fscanf(mtl, "%s", tm) > 0)
	{
		if (strcmp(tm, "Ns") == 0)
		{
			std::fscanf(mtl, "%f", &x);
			tmp.set_Ns(x);
		}
		else if (strcmp(tm, "Ni") == 0)
		{
			std::fscanf(mtl, "%f", &x);
			tmp.set_Ni(x);
		}
		else if (strcmp(tm, "d") == 0)
		{
			std::fscanf(mtl, "%f", &x);
			tmp.set_d(x);
		}
		else if (strcmp(tm, "illum") == 0)
		{
			std::fscanf(mtl, "%d", &illum);
			tmp.set_illum(illum);
		}
		else if (strcmp(tm, "Ka") == 0)
		{
			std::fscanf(mtl, "%f %f %f", &x, &y, &z);
			tmp.set_Ka(Vector(x, y, z));
		}
		else if (strcmp(tm, "Kd") == 0)
		{
			std::fscanf(mtl, "%f %f %f", &x, &y, &z);
			tmp.set_Kd(Vector(x, y, z));
		}
		else if (strcmp(tm, "Ks") == 0)
		{
			std::fscanf(mtl, "%f %f %f", &x, &y, &z);
			tmp.set_Ks(Vector(x, y, z));
		}
		else if (strcmp(tm, "Ke") == 0)
		{
			std::fscanf(mtl, "%f %f %f", &x, &y, &z);
			tmp.set_Ke(Vector(x, y, z));
		}
		else if (strcmp(tm, "newmtl") == 0)
		{
			if (x != INFINITY)
			{
				materials[mat_name] = tmp.copy();
				// std::cout << "ok\n";
			}
			fscanf(mtl, "%s", mat_name);
			// std::cout << "\033[1;31m" << mat_name << "\033[0m" << std::endl;
		}
	}
	if (x != INFINITY)
	{
		materials[mat_name] = tmp.copy();
		// std::cout << "ok\n";
	}
	return (0);
}