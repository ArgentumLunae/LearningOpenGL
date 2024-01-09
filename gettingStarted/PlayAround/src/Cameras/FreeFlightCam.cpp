#include "../../hdr/Cameras/FreeFlightCam.hpp"

/* -------- Member Functions -------- */

void	FreeFlightCam::moveForward(float const speed) {
	this->_pos += speed * this->_front;
}
void	FreeFlightCam::moveBack(float const speed) {
	this->_pos -= speed * this->_front;
}
void	FreeFlightCam::strafeRight(float const speed) {
	this->_pos += speed * this->_right;
}
void	FreeFlightCam::strafeLeft(float const speed) {
	this->_pos -= speed * this->_right;
}
void	FreeFlightCam::moveUp(float const speed) {
	this->_pos += speed * this->_worldUp;
}
void	FreeFlightCam::moveDown(float const speed) {
	this->_pos -= speed * this->_worldUp;
}

void	FreeFlightCam::updateYaw(float const change) {
	this->_yaw += change;
}

void	FreeFlightCam::updatePitch(float const change)
{
	this->_pitch += change;
	if (this->_pitch > 89.0f)
		this->_pitch = 89.0f;
	if (this->_pitch < -89.0f)
		this->_pitch = -89.0f;
}

void	FreeFlightCam::updateDirection()
{
	glm::vec3 direction;

	direction.x = cos(glm::radians(this->_yaw)) * cos(glm::radians(this->_pitch));
	direction.y = sin(glm::radians(this->_pitch));
	direction.z = sin(glm::radians(this->_yaw)) * cos(glm::radians(this->_pitch));

	this->_front = glm::normalize(direction);
	this->_right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), this->_front));
}

/* -------- Constructors & Destructor -------- */

FreeFlightCam::FreeFlightCam()
{
	this->_pos = glm::vec3(0.0f);
	this->_yaw = -90.0f;
	this->_pitch = 0.0f;
}

FreeFlightCam::FreeFlightCam(FreeFlightCam & src) {
	*this = src;
}

FreeFlightCam::~FreeFlightCam() {}

/* -------- Operator Overloads -------- */

FreeFlightCam & FreeFlightCam::operator=(FreeFlightCam & rhs)
{
	if (this != &rhs)
	{
		this->_pos = rhs.getPos();
		this->_front = rhs.getFront();
		this->_up = rhs.getUp();
		this->_right = rhs.getRight();
		this->_yaw = rhs.getYaw();
		this->_pitch = rhs.getPitch();
		this->_fov = rhs.getFOV();
	}
	return *this;
}

/* -------- Getters & Setters -------- */

float	FreeFlightCam::getYaw() const {
	return this->_yaw;
}

void	FreeFlightCam::setYaw(float const yaw) {
	this->_yaw = yaw;
}

float	FreeFlightCam::getPitch() const {
	return this->_pitch;
}

void	FreeFlightCam::setPitch(float const pitch) {
	this->_pitch = pitch;
}

float	FreeFlightCam::getFOV() const {
	return this->_fov;
}

void	FreeFlightCam::setFOV(float const fov) {
	this->_fov = fov;
}
