/**********************************************
** Project: Math 3200 Project
** File: Camera.h
** Author: Luke Leontowich
** Date: September 10, 2021
** Description: Define the camera class
**********************************************/

#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
private:
    //  Position of the camera
    //  Initialize the original position
    glm::vec3 _pos = glm::vec3(0.0f, 2.5f, 0.0f);

    //  Up vector
    //  Describes the up direction of the camera
    //  Initialize the up vector to upright
    glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f);

    //  Direction vector
    //  Describes the direction that the camera is looking at
    //  Initialize the original position
    glm::vec3 _dir = glm::vec3(0.0f, 0.0f, -1.0f);

    //  The yaw is the angle defined in the xz plane
    //  Otherwise stated it is the degree of which you are looking left or right
    float _yaw = 0.0f;

    //  The pitch is the height that you are looking at
    float _pitch = 0.0f;
public:
    /**  Constructor  **/
    Camera();

    /**  Destructor  **/
    ~Camera();

    /** Update()
    ** @param none
    ** @return void
    ** Description: Updates the camera, expects for the pitch and yaw to have been updated
    **/
    void update();

    /** UpdatePos()
    ** @param glm::vec3
    ** @return void
    ** Description: Updates the position
    **/
    void updatePos(const glm::vec3& pos);

    /** UpdatePitch()
    ** @param float
    ** @return void
    ** Description: Updates the pitch
    **/
    void updatePitch(const float& pitch);

    /** UpdateYaw()
    ** @param float
    ** @return void
    ** Description: Updates the yaw
    **/
    void updateYaw(const float& yaw);

    /**  Setters and Getters  **/
    void setPitch(const float& pitch);
    void setYaw(const float& yaw);
    void setPos(const glm::vec3& pos);
    glm::vec3 pos();
    glm::vec3 up();
    glm::vec3 dir();
    float yaw();
    float pitch();
};


#endif // CAMERA_H
