#ifndef FPSCAMERA_HPP
# define FPSCAMERA_HPP

#include "Camera.hpp"
#include <glm/glm.hpp>
#include <deque>

class FpsCamera: public Camera
{
	private:
		float _height;
		bool _crouch;
		bool _grounded;

		float _yaw;
		float _pitch;

		float _verticalSpeed;
		float _jumpSpeed;
		float _gravAcceleration;

	public:
		FpsCamera();
		FpsCamera(FpsCamera & src);
		~FpsCamera();

		FpsCamera & operator=(FpsCamera & rhs);

		void	moveForward(float const speed);
		void	moveBack(float const speed);
		void	strafeRight(float const speed);
		void	strafeLeft(float const speed);
		void	jump();
		void	crouch();

		void	updateYaw(float const change);
		void	updatePitch(float const change);
		void	updateDirection();

		void	fall(float const deltaTime);
		void	isGrounded(std::deque<glm::vec3> ground);

		float	getHeight() const;
		void	setHeight(float const height);
		bool	getCrouch() const;
		void	setCrouch(bool const crouch);
		bool	getGrounded() const;
		void	setGrounded(bool const grounded);
		float	getYaw() const;
		void	setYaw(float const yaw);
		float	getPitch() const;
		void	setPitch(float const pitch);
		float	getVerticalSpeed() const;
		void	setVerticalSpeed(float const vertSpeed);
		float	getJumpSpeed() const;
		void	setJumpSpeed(float const jumpSpeed);
		float	getgravAcceleration() const;
		void	setGravConstatn(float const gravAcceleration);
};

#endif
