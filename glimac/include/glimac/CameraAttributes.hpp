#pragma once 
#include <glm/glm.hpp>
#include <vector>

class CameraAttributes {

public: 
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    float Yaw;
    float Pitch;


public:
    CameraAttributes(glm::vec3 Position,
                    glm::vec3 Front,
                    glm::vec3 Up,
                    glm::vec3 Right,
                    glm::vec3 WorldUp,
                    float Yaw,
                    float Pitch);
};

glm::vec3 Position2 = glm::vec3(-0.605, 14.440, 24.366);
glm::vec3 Front2 = glm::vec3(0.009, -0.225, -0.974);
glm::vec3 Up2 = glm::vec3(0.002, 0.974, -0.225);
glm::vec3 Right2 = glm::vec3(1.000, -0.000, 0.009);
glm::vec3 WorldUp2 = glm::vec3(0.000, 1.000, 0.000);
float Yaw2 = -89.5;
float Pitch2 = -13;