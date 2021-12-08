#include "PerspectiveOnePointFactory.h"

PerspectiveOnePointFactory::PerspectiveOnePointFactory
        (const float& fv, const float& asp, const float& n, const float& f) {
    fovy = fv;
    aspect = asp;
    near = n;
    far = f;
}

PerspectiveOnePointFactory::~PerspectiveOnePointFactory() {}

glm::mat4 PerspectiveOnePointFactory::createProjection() {
    glm::mat4 m(1.0f);

    float top = near * tan(glm::radians(fovy));
    float right = top * aspect;

    m[0][0] = near / right;
    m[1][1] = near / top;
    m[2][2] = -(far + near) / (far - near);
    m[3][3] = 0.0f;
    m[3][2] = -(2.0f * far * near) / (far - near);
    m[2][3] = -1.0f;

    return m;
}

void PerspectiveOnePointFactory::print() {
    std::cout << "PERSPECTIVE PROJECTION\n";
}
