/*****************************************************
** Project: Cube Builder Game
** File: Cube.cpp
** Author: Luke Leontowich
** Date: September 10, 2021
** Description: This file implements Cube.h, Does nothing
** really
*****************************************************/

#include "Cube.h"

Cube::Cube() {}

Cube::~Cube() {}

void Cube::init() {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

