/*****************************************************
** Project: Math 3200 Project
** File: PerspectiveProjection.cpp
** Author: Luke Leontowich,
** Date: November 19, 2021
** Description: Concrete Projection factory class
*****************************************************/

#include "PerspectiveProjection.h"

PerspectiveProjection::PerspectiveProjection(const float& l, const float& r,
                                             const float& b, const float& t,
                                             const float& n, const float& f,
                                             const float& fovy_p,
                                             const float& aspect_p) {

    fovy = fovy_p;
    aspect = aspect_p;

    near = n;
    far = f;

    top = near * tan(glm::radians(fovy));
    right = top * aspect;

    left = -right;
    bottom = -top;
}

PerspectiveProjection::~PerspectiveProjection() {}

glm::mat4 PerspectiveProjection::createProjection() {
    //  Initialize matrix to identity matrix
    glm::mat4 m(1.0f);

    m[0][0] = (2.0f * near) / (right - left);
    m[2][0] = (right + left) / (right - left);
    m[1][1] = (2.0f * near) / (top - bottom);
    m[2][1] = (top + bottom) / (top -bottom);
    m[2][2] = (far + near) / (near - far);
    m[3][2] = (2.0f * far * near) / (near - far);
    m[2][3] = -1.0f;

    return m;
}

void PerspectiveProjection::print() {
    std::cout << "PERSPECTIVE PROJECTION\n";
}
