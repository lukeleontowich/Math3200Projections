/**********************************************
** Project: Math 3200 Project
** File: Camera.cpp
** Author: Luke Leontowich
** Date: September 10, 2021
** Description: Implements Camera class
**********************************************/

#include "Camera.h"

Camera::Camera() {}
Camera::~Camera() {}

void Camera::update() {
    _dir.x = cos(glm::radians(this->_yaw)) * cos(glm::radians(this->_pitch));
    _dir.y = sin(glm::radians(this->_pitch));
    _dir.z = sin(glm::radians(this->_yaw)) *
                 cos(glm::radians(this->_pitch));
    _dir = glm::normalize(this->_dir);
}

void Camera::updatePos(const glm::vec3& pos) {
    _pos += pos;
}

void Camera::updatePitch(const float& pitch) {
    _pitch += pitch;
}

void Camera::updateYaw(const float& yaw) {
    _yaw += yaw;
}

void Camera::setPitch(const float& pitch) {
    _pitch = pitch;
}

void Camera::setYaw(const float& yaw) {
    _yaw = yaw;
}

void Camera::setPos(const glm::vec3& pos) {
    _pos = pos;
}

glm::vec3 Camera::pos() {
    return _pos;
}

glm::vec3 Camera::up() {
    return _up;
}

glm::vec3 Camera::dir() {
    return _dir;
}

float Camera::yaw() {
    return _yaw;
}

float Camera::pitch() {
    return _pitch;
}
