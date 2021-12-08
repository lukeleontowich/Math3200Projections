/*****************************************************
** Project: Math 3200 Project
** File: AbstractProjectionFactory.h
** Author: Luke Leontowich,
** Date: November 19, 2021
** Description: Base class for the projection factories
*****************************************************/

#ifndef ABSTRACTPROJECTIONFACTORY_H
#define ABSTRACTPROJECTIONFACTORY_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

class AbstractProjectionFactory {
public:
    AbstractProjectionFactory();
    virtual ~AbstractProjectionFactory();

    virtual glm::mat4 createProjection() = 0;
    virtual void print() = 0;

protected:
    float left, right;
    float bottom, top;
    float near, far;
};

#endif // ABSTRACTPROJECTIONFACTORY_H
