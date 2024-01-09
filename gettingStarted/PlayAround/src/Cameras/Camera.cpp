/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Camera.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: argentumlunae <argentumlunae@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/23 18:29:52 by argentumlun   #+#    #+#                 */
/*   Updated: 2023/12/24 15:43:39 by argentumlun   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdr/Cameras/Camera.hpp"
#include <iostream>

#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"

/* -------- Member Functions -------- */

void	Camera::updateFOV(float const change) {
	this->_fov += change;

	if (this->_fov < 15.0f)
		this->_fov = 15.0f;
	if (this->_fov > 130.0f)
		this->_fov = 130.0f;
}

/* -------- Constructors & Destructor -------- */

Camera::Camera()
{
	this->_worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

	this->_pos = glm::vec3(0.0f, 0.0f, 3.0f);
	this->_front = glm::vec3(0.0f, 0.0f, -1.0f);
	this->_right = glm::normalize(glm::cross(this->_worldUp, this->_front));
	this->_up = glm::normalize(glm::cross(this->_front, this->_right));

	this->_fov = 60.0f;
}

Camera::Camera(glm::vec3 const position) : _pos(position)
{
	this->_worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

	this->_front = glm::vec3(0.0f, 0.0f, -1.0f);
	this->_right = glm::normalize(glm::cross(this->_worldUp, this->_front));
	this->_up = glm::normalize(glm::cross(this->_front, this->_right));

	this->_fov = 60.0f;
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
		this->_pos = rhs.getPos();
		this->_front = rhs.getFront();
		this->_up = rhs.getUp();
		this->_right = rhs.getRight();
	}
	return *this; 
}

/* -------- Getters & Setters -------- */

float	Camera::getFOV() const {
	return this->_fov;
}

void	Camera::setFOV(float const fov) {
	this->_fov = fov;
}

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
