#include "../hdr/FPCharacter.hpp"

/* -------- MemberFunctions -------- */


	// Movement
void	Camera::moveForward(float const speed) {
	this->_pos += glm::vec3(speed * this->_front.x, 0.0f, speed * this->_front.z);
}

void	Camera::moveBack(float const speed) {
	this->_pos -= glm::vec3(speed * this->_front.x, 0.0f, speed * this->_front.z);
}

void	Camera::strafeRight(float const speed) {
	this->_pos += glm::vec3(speed * this->_right.x, 0.0f, speed * this->_right.z);
}

void	Camera::strafeLeft(float const speed) {
	this->_pos -= glm::vec3(speed * this->_right.x, 0.0f, speed * this->_right.z);
}

void	Camera::jump() {
	this->_vertSpeed = 0.05f;
	this->_grounded = false;
}

	// Rotation
void	Camera::updateYaw(float const change) {
	this->_yaw += change;
}

void	Camera::updatePitch(float const change)
{
	this->_pitch += change;
	if (this->_pitch > 89.0f)
		this->_pitch = 89.0f;
	if (this->_pitch < -89.0f)
		this->_pitch = -89.0f;
}

void	Camera::updateDirection()
{
	this->_direction.x = cos(glm::radians(this->_yaw)) * cos(glm::radians(this->_pitch));
	this->_direction.y = sin(glm::radians(this->_pitch));
	this->_direction.z = sin(glm::radians(this->_yaw)) * cos(glm::radians(this->_pitch));

	this->_front = glm::normalize(this->_direction);
	this->_right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), this->_front));
}