/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: QFM <quentin.feuillade33@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 12:24:51 by QFM               #+#    #+#             */
/*   Updated: 2019/12/11 15:14:57 by QFM              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Ray/Ray.hpp"

class Camera
{
private:

	Vector	pos;
	Vector	dir;
	Vector	up;
	int		fov;

public:

	Camera(Vector pos, Vector dir, int fov, Vector up);
	Camera();
	Camera(Camera const &);
	~Camera();
	
	Ray		cast_ray(int x, int y);

	Vector		get_pos() const;
	Vector		get_dir() const;
	void		set_pos(Vector);
	void		set_dir(Vector);
};