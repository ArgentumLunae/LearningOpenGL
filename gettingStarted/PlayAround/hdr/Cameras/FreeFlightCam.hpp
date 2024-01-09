#ifndef FREEFLIGHTCAM_HPP
# define FREEFLIGHTCAM_HPP

# include "Camera.hpp"

class FreeFlightCam : public Camera
{
	private:
		float	_yaw;
		float	_pitch;
	
	public:
		FreeFlightCam();
		FreeFlightCam(FreeFlightCam & src);
		~FreeFlightCam();

		FreeFlightCam & operator=(FreeFlightCam & rhs);

		void	moveForward(float const speed);
		void	moveBack(float const speed);
		void	strafeRight(float const speed);
		void	strafeLeft(float const speed);
		void	moveUp(float const speed);
		void	moveDown(float const speed);

		void	updateYaw(float const change);
		void	updatePitch(float const change);
		void	updateDirection();

		float	getYaw() const;
		void	setYaw(float const yaw);
		float	getPitch() const;
		void	setPitch(float const pitch);
		float	getFOV() const;
		void	setFOV(float const fov);
};

#endif