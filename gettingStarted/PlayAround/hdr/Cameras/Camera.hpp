/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Camera.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: argentumlunae <argentumlunae@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/23 18:29:58 by argentumlun   #+#    #+#                 */
/*   Updated: 2023/12/24 15:42:25 by argentumlun   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_HPP
# define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
	protected:
		float		_fov;
		glm::vec3	_worldUp;

		glm::vec3	_pos;
		glm::vec3	_target;
		glm::vec3	_front;
		glm::vec3	_up;
		glm::vec3	_right;

	public:
		Camera();
		Camera(glm::vec3 const position);
		Camera(Camera & src);
		~Camera();

		Camera & operator=(Camera & rhs);

		void	updateFOV(float const change);

		float	getFOV() const;
		void	setFOV(float const fov);
		glm::vec3	getPos() const;
		void	setPos(glm::vec3 const pos);
		glm::vec3	getFront() const;
		void	setFront(glm::vec3 const front);
		glm::vec3	getUp() const;
		void	setUp(glm::vec3 const up);
		glm::vec3	getRight() const;
		void	setRight(glm::vec3 const right);
};

#endif
