/*****************************************************
** Project: Math 3200 Project
** File: ObliqueProjection.h
** Author: Luke Leontowich,
** Date: November 19, 2021
** Description: Concrete Projection factory class
*****************************************************/

#ifndef OBLIQUEPROJECTION_H
#define OBLIQUEPROJECTION_H

#include <cmath>

#include "AbstractProjectionFactory.h"


class ObliqueProjection : public AbstractProjectionFactory {
public:
    ObliqueProjection(const float& l, const float& r,
                      const float& b, const float& t,
                      const float& n, const float& f,
                      const float& atheta, const float& aphi);
    ~ObliqueProjection();

    glm::mat4 createProjection() override;

    void print() override;
private:
    float theta, phi;
};

#endif // OBLIQUEPROJECTION_H
