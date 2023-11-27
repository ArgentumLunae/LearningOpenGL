/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Camera.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: argentumlunae <argentumlunae@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/23 18:29:52 by argentumlun   #+#    #+#                 */
/*   Updated: 2023/11/27 15:57:12 by argentumlun   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/Camera.hpp"
#include <iostream>

#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"

/* -------- Member Functions -------- */

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

void	Camera::updateFOV(float const change)
{
	this->_fov -= change;
	if (this->_fov < 1.0f)
		this->_fov = 1.0f;
	if (this->_fov > 60.0f)
		this->_fov = 60.0f;
}


/* -------- Constructors & Destructor -------- */

Camera::Camera()
{
	this->_pos = glm::vec3(0.0f, 0.0f, 3.0f);
	this->_front = glm::vec3(0.0f, 0.0f, -1.0f);
	this->_up = glm::vec3(0.0f, 1.0f, 0.0f);
	this->_right = glm::normalize(glm::cross(this->_up, this->_front));
	
	this->_yaw = -90.0f;
	this->_pitch = 0.0f;
	this->_fov = 45.0f;
	this->_vertSpeed = 0.0f;

	this->_grounded = false;
}

Camera::Camera(glm::vec3 const position) : _pos(position)
{
	this->_front = glm::vec3(0.0f, 0.0f, -1.0f);
	this->_up = glm::vec3(0.0f, 1.0f, 0.0f);
	this->_right = glm::normalize(glm::cross(this->_up, this->_front));
	
	this->_yaw = -90.0f;
	this->_pitch = 0.0f;
	this->_fov = 45.0f;
	this->_vertSpeed = 0.0f;

	this->_grounded = false;
}

Camera::Camera(Camera & src)
{
	*this = src;
}

Camera::~Camera() {}


/* -------- Operator Overloads -------- */

Camera & Camera::operator=(Camera & rhs)
{
	if (this != &rhs)
	{
		this->_pos = rhs._pos;
		this->_front = rhs._front;
		this->_up = rhs._up;
		this->_right = rhs._right;
		this->_direction = rhs._direction;

		this->_yaw = rhs._yaw;
		this->_pitch = rhs._pitch;
		this->_fov = rhs._fov;
		this->_vertSpeed = rhs._vertSpeed;
		this->_grounded = rhs._grounded;
	}
	return *this; 
}

/* -------- Getters & Setters -------- */

glm::vec3	Camera::getPos() const {
	return this->_pos;
}

void	Camera::setPos(glm::vec3 const pos) {
	this->_pos = pos;
}

glm::vec3	Camera::getFront() const {
	return this->_front;
}

void	Camera::setFront(glm::vec3 const front) {
	this->_front = front;
}

glm::vec3	Camera::getUp() const {
	return this->_up;
}

void	Camera::setUp(glm::vec3 const up) {
	this->_up = up;
}

glm::vec3	Camera::getRight() const {
	return this->_right;
}

void	Camera::setRight(glm::vec3 const right) {
	this->_right = right;
}

glm::vec3	Camera::getDirection() const {
	return this->_direction;
}

void	Camera::setDirection(glm::vec3 const direction) {
	this->_direction = direction;
}

float	Camera::getYaw() const {
	return this->_yaw;
}

void	Camera::setYaw(float const yaw) {
	this->_yaw = yaw;
}

float	Camera::getPitch() const {
	return this->_pitch;
}

void	Camera::setPitch(float const pitch) {
	this->_pitch = pitch;
}

float	Camera::getFOV() const {
	return this->_fov;
}

void	Camera::setFOV(float const fov) {
	this->_fov = fov;
}

float	Camera::getVertSpeed() const {
	return this->_vertSpeed;
}

void	Camera::setVertSpeed(float const vertSpeed) {
	this->_vertSpeed = vertSpeed;
}

bool	Camera::getGrounded() const {
	return this->_grounded;
}

void	Camera::setGrounded(bool const grounded) {
	this->_grounded = grounded;
}

/* --------  -------- */

/* --------  -------- */

