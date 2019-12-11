/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: QFM <quentin.feuillade33@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 12:52:11 by QFM               #+#    #+#             */
/*   Updated: 2019/12/11 15:15:18 by QFM              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Camera.hpp"

Camera::Camera(Vector p, Vector d, int f, Vector u)
{
	fov = f;
	pos = p;
	dir = d;
	up = u;
}

Camera::Camera() { }

Camera::~Camera() { }

Ray		Camera::cast_ray(int x, int y)
{
	float imageAspectRatio = IMAGE_W / (float)IMAGE_H;
	float Px = (2 * ((x + 0.5) / IMAGE_W) - 1) * tan(fov / 2 * M_PI / 180) * imageAspectRatio; 
	float Py = (1 - 2 * ((y + 0.5) / IMAGE_H) * tan(fov / 2 * M_PI / 180)); 
	Vector rayDirection = Vector(Px, Py, -1);
	rayDirection = rayDirection.normalize();
	return (Ray(pos, rayDirection));
}

Camera::Camera(Camera const &c)
{
	fov = c.fov;
	pos = c.pos;
	dir = c.dir;
}

Vector		Camera::get_pos() const
{
	return (pos);
}

Vector		Camera::get_dir() const
{
	return (dir);
}

void		Camera::set_pos(Vector p)
{
	pos = p;
}

void		Camera::set_dir(Vector d)
{
	dir = d;
}
