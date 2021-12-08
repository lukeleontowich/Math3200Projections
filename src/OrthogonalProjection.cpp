/*****************************************************
** Project: Math 3200 Project
** File: OrthogonalProjection.cpp
** Author: Luke Leontowich,
** Date: November 19, 2021
** Description: Concrete Projection factory class
*****************************************************/

#include "OrthogonalProjection.h"

OrthogonalProjection::OrthogonalProjection(const float& l, const float& r,
                                           const float& b, const float& t,
                                           const float& n, const float& f) {
    left = l;
    right = r;
    bottom = b;
    top = t;
    near = n;
    far = f;
}

OrthogonalProjection::~OrthogonalProjection()
{
    //dtor
}

glm::mat4 OrthogonalProjection::createProjection() {
    //  initialize matrix to identity matrix
    glm::mat4 m(1.0f);

    // explanation of matrix in report
    m[0][0] = 2 / (right - left);
    m[1][1] = 2 / (top - bottom);
    m[2][2] = 2 / (far - near);

    m[3][0] = -(right + left) / (right - left);
    m[3][1] = -(top + bottom) / (top - bottom);
    m[3][2] = (far + near) / (far - near);

    return m;
}

void OrthogonalProjection::print() {
    std::cout << "ORTHOGONAL PROJECTION\n";
}
