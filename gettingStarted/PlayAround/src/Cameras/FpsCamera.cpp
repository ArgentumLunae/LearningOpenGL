#include "../../hdr/Cameras/FpsCamera.hpp"

#include <iostream>
#include <glm/gtx/string_cast.hpp>

#define FPS_EPSILON 0.0001

/* -------- Member Functions -------- */

void	FpsCamera::moveForward(float const speed) {
	if (!this->_crouch)
		this->_pos += speed * glm::vec3(this->_front.x, 0.0f, this->_front.z);
	else
		this->_pos += 0.6f * speed * glm::vec3(this->_front.x, 0.0f, this->_front.z);
}

void	FpsCamera::moveBack(float const speed) {
	if (!this->_crouch)
		this->_pos -= speed * glm::vec3(this->_front.x, 0.0f, this->_front.z);
	else
		this->_pos -= 0.6f * speed * glm::vec3(this->_front.x, 0.0f, this->_front.z);
	
}

void	FpsCamera::strafeRight(float const speed) {
	if (!this->_crouch)
		this->_pos += speed * this->_right;
	else
		this->_pos += 0.6f * speed * this->_right;
}

void	FpsCamera::strafeLeft(float const speed) {
	if (!this->_crouch)
		this->_pos -= speed * this->_right;
	else
		this->_pos -= 0.6f * speed * this->_right;
}

void	FpsCamera::jump() {
	if (this->_grounded)
		this->_verticalSpeed = this->_jumpSpeed;
}

void	FpsCamera::crouch() {
	if (this->_crouch == false)
	{
		this->_pos.y -= (this->_height / 3.0f);
		this->_height -= (this->_height / 3.0f);
		this->_crouch = true;
	}
	else
	{
		this->_pos.y += (this->_height / 3.0f);
		this->_height += (this->_height / 3.0f);
		this->_crouch = false;
	}
}

void	FpsCamera::updateYaw(float const change) {
	this->_yaw += change;
}

void	FpsCamera::updatePitch(float const change)
{
	this->_pitch += change;
	if (this->_pitch > 89.0f)
		this->_pitch = 89.0f;
	if (this->_pitch < -89.0f)
		this->_pitch = -89.0f;
}

void	FpsCamera::updateDirection()
{
	glm::vec3 direction;

	direction.x = cos(glm::radians(this->_yaw)) * cos(glm::radians(this->_pitch));
	direction.y = sin(glm::radians(this->_pitch));
	direction.z = sin(glm::radians(this->_yaw)) * cos(glm::radians(this->_pitch));

	this->_front = glm::normalize(direction);
	this->_right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), this->_front));
}

void	FpsCamera::fall(float const deltaTime) {
	if (!this->_grounded)
	{
		this->_verticalSpeed -= 0.03 * deltaTime * this->_gravAcceleration;
		if (this->_verticalSpeed <= -(10 * deltaTime))
			this->_verticalSpeed = -(10 * deltaTime);
		this->_pos.y += this->_verticalSpeed;
	}
}

void	FpsCamera::isGrounded(std::deque<glm::vec3> ground) {
	for (int i = 0; i < ground.size(); i++)
	{
		if (this->_verticalSpeed > 0.0f)
		{
			std::cout << "isGrounded: velocity factor" << std::endl;
			break ;
		}
		glm::vec3 relativePos = this->_pos - ground[i];
		if (!(relativePos.x > -0.55 && relativePos.x < 0.55 && relativePos.z > -0.55 && relativePos.z < 0.55))
			continue ;
		if (relativePos.y < this->_height + 0.5 + FPS_EPSILON && relativePos.y > ((this->_height + 0.5 )* 0.9) - FPS_EPSILON)
		{
			if(this->_grounded)
				return ;
			std::cout << this->_pos.y << " - " << ground[i].y << " = " << relativePos.y << ", " << this->_height << ", " << FPS_EPSILON << std::endl;
			this->_verticalSpeed = 0.0f;
			this->_pos.y = ground[i].y + 0.5 + this->_height;
			this->_grounded = true;
			std::cout << this->_pos.y << " - " << ground[i].y << " = " << relativePos.y << ", " << this->_height << ", " << FPS_EPSILON << std::endl << std::endl;
			return ;
		}
	}
	this->_grounded = false;
}

/* -------- Constructors & Destructors -------- */

FpsCamera::FpsCamera()
{
	this->_height = 1.5f;
	this->_yaw = -90.0f;
	this->_pitch = 0.0f;
	this->_pos = glm::vec3(0.0f, (0.5f + _height), 0.0f);

	this->_verticalSpeed = 0.0f;
	this->_jumpSpeed = 0.15f;
	this->_gravAcceleration = 9.81;
}

FpsCamera::FpsCamera(FpsCamera & src)
{
	*this = src;
}

FpsCamera::~FpsCamera() {};


/* -------- Operator Overloads -------- */

FpsCamera & FpsCamera::operator=(FpsCamera & rhs)
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

float	FpsCamera::getHeight() const {
	return this->_height;
}

void	FpsCamera::setHeight(float const height) {
	this->_height = height;
}

bool	FpsCamera::getCrouch() const {
	return this->_crouch;
}

void	FpsCamera::setCrouch(bool const crouch) {
	this->_crouch = crouch;
}

bool	FpsCamera::getGrounded() const {
	return this->_grounded;
}

void	FpsCamera::setGrounded(bool const grounded) {
	this->_grounded = grounded;
}

float	FpsCamera::getYaw() const {
	return this->_yaw;
}

void	FpsCamera::setYaw(float const yaw) {
	this->_yaw = yaw;
}

float	FpsCamera::getPitch() const {
	return this->_pitch;
}

void	FpsCamera::setPitch(float const pitch) {
	this->_pitch = pitch;
}

float	FpsCamera::getVerticalSpeed() const {
	return this->_verticalSpeed;
}

void	FpsCamera::setVerticalSpeed(float const vertSpeed) {
	this->_verticalSpeed = vertSpeed;
}

float	FpsCamera::getJumpSpeed() const {
	return this->_jumpSpeed;
}

void	FpsCamera::setJumpSpeed(float const jumSpeed) {
	this->_jumpSpeed = jumSpeed;
}

float	FpsCamera::getgravAcceleration() const {
	return this->_gravAcceleration;
}

void	FpsCamera::setGravConstatn(float const gravAcceleration) {
	this->_gravAcceleration = gravAcceleration;
}
