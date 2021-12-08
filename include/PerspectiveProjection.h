/*****************************************************
** Project: Math 3200 Project
** File: PerspectiveProjection.h
** Author: Luke Leontowich,
** Date: November 19, 2021
** Description: Concrete Projection factory class
*****************************************************/

#ifndef PERSPECTIVEPROJECTION_H
#define PERSPECTIVEPROJECTION_H

#include "AbstractProjectionFactory.h"


class PerspectiveProjection : public AbstractProjectionFactory {
public:
    PerspectiveProjection(const float& l, const float& r,
                          const float& b, const float& t,
                          const float& n, const float& f,
                          const float& fovy = 45.0f,
                          const float& aspect = 1.0f);
    ~PerspectiveProjection();

    glm::mat4 createProjection() override;

    void print() override;
private:
    float fovy;
    float aspect;
};

#endif // PERSPECTIVEPROJECTION_H
