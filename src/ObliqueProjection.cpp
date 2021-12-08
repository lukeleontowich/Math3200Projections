/*****************************************************
** Project: Math 3200 Project
** File: ObliqueProjection.cpp
** Author: Luke Leontowich,
** Date: November 19, 2021
** Description: Concrete Projection factory class
*****************************************************/

#include "ObliqueProjection.h"

ObliqueProjection::ObliqueProjection(const float& left_old, const float& right_old,
                                     const float& bottom_old, const float& top_old,
                                     const float& near_old, const float& far_old,
                                     const float& atheta, const float& aphi) {
    //  No calculations need for angles, near and far. Just copy the values coming in.
    theta = atheta;
    phi = aphi;

    near = near_old;
    far = far_old;

    //  left, right, bottom, top are calculated based on the report
    //  Note that cmath doesn't have cot so using property cot(x) = 1 / tan(x)
    left = left_old - near * (1.0f / tan(glm::radians(theta)));
    right = right_old - near * (1.0f / tan(glm::radians(theta)));

    bottom = bottom_old - near * (1.0f / tan(glm::radians(phi)));
    top = top_old - near * (1.0f / tan(glm::radians(phi)));
}

ObliqueProjection::~ObliqueProjection() {}

glm::mat4 ObliqueProjection::createProjection() {
    //  initialize matrix to identity matrix
    glm::mat4 m(1.0f);

    //  See report for matrix details
    m[0][0] = 2.0f / (right - left);
    m[2][0] = 2.0f / (tan(glm::radians(theta)) * (right - left));
    m[3][0] = -(right + left) / (right - left);
    m[1][1] = 2.0f / (top - bottom);
    m[2][1] = 2.0f / (tan(glm::radians(phi)) * (top - bottom));
    m[3][1] = -(top +bottom) / (top - bottom);
    m[2][2] = 0.0f;

    return m;
}

void ObliqueProjection::print() {
    std::cout << "OBLIQUE PROJECTION\n";
}
