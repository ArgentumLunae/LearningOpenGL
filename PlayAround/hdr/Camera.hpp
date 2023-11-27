/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Camera.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: argentumlunae <argentumlunae@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/23 18:29:58 by argentumlun   #+#    #+#                 */
/*   Updated: 2023/11/27 15:45:10 by argentumlun   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_HPP
# define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
	private:
		glm::vec3	_pos;
		glm::vec3	_front;
		glm::vec3	_up;
		glm::vec3	_right;
		glm::vec3	_direction;

		float	_yaw;
		float	_pitch;
		float	_fov;
		float	_vertSpeed;

		bool	_grounded;

	public:
		Camera();
		Camera(glm::vec3 const position);
		Camera(Camera & src);
		~Camera();

		Camera & operator=(Camera & rhs);

		void	moveForward(float const speed);
		void	moveBack(float const speed);
		void	strafeRight(float const speed);
		void	strafeLeft(float const speed);
		void	jump();

		void	updateYaw(float const change);
		void	updatePitch(float const change);
		void	updateDirection();

		void	updateFOV(float const change);

		glm::vec3	getPos() const;
		void	setPos(glm::vec3 const pos);
		glm::vec3	getFront() const;
		void	setFront(glm::vec3 const front);
		glm::vec3	getUp() const;
		void	setUp(glm::vec3 const up);
		glm::vec3	getRight() const;
		void	setRight(glm::vec3 const right);
		glm::vec3	getDirection() const;
		void	setDirection(glm::vec3 const direction);

		float	getYaw() const;
		void	setYaw(float const yaw);
		float	getPitch() const;
		void	setPitch(float const pitch);
		float	getFOV() const;
		void	setFOV(float const fov);
		float	getVertSpeed() const;
		void	setVertSpeed(float const vertSpeed);

		bool	getGrounded() const;
		void	setGrounded(bool const grounded);
};

#endif
