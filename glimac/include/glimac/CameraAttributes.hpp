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

glm::vec3 Position1 = glm::vec3(-2.845,    8.877,   21.219);
glm::vec3 Front1 = glm::vec3(0.122,   -0.017,   -0.992);
glm::vec3 Up1 = glm::vec3(0.002,    1.000,   -0.017);
glm::vec3 Right1 = glm::vec3(0.993,   -0.000,    0.122);
glm::vec3 WorldUp1 = glm::vec3(0.000, 1.000, 0.000);
float Yaw1 = -83;
float Pitch1 = -1;

glm::vec3 Position2 = glm::vec3(-0.605, 14.440, 24.366);
glm::vec3 Front2 = glm::vec3(0.009, -0.225, -0.974);
glm::vec3 Up2 = glm::vec3(0.002, 0.974, -0.225);
glm::vec3 Right2 = glm::vec3(1.000, -0.000, 0.009);
glm::vec3 WorldUp2 = glm::vec3(0.000, 1.000, 0.000);
float Yaw2 = -89.5;
float Pitch2 = -13;

glm::vec3 Position3 = glm::vec3(-3.308,    3.369,   18.829);
glm::vec3 Front3 = glm::vec3(0.077,   -0.165,   -0.983);
glm::vec3 Up3 = glm::vec3(0.013,    0.986,   -0.165);
glm::vec3 Right3 = glm::vec3(0.997,   -0.000,    0.078);
glm::vec3 WorldUp3 = glm::vec3(0.000, 1.000, 0.000);
float Yaw3 = -85.5;
float Pitch3 = -9.5;

glm::vec3 Position4 = glm::vec3(28.965,    0.033,   -3.919);
glm::vec3 Front4 = glm::vec3(-0.993,    0.113,   -0.035);
glm::vec3 Up4 = glm::vec3(0.113,    0.994,    0.004);
glm::vec3 Right4 = glm::vec3(0.035,    0.000,   -0.999);
glm::vec3 WorldUp4 = glm::vec3(0.000,    1.000,    0.000);
float Yaw4 = -178.0;
float Pitch4 = 6.5;

glm::vec3 Position5 = glm::vec3(-30.751,   -2.435,   -3.458);
glm::vec3 Front5 = glm::vec3(0.987,    0.156,   -0.034);
glm::vec3 Up5 = glm::vec3(-0.156,    0.988,    0.005);
glm::vec3 Right5 = glm::vec3(0.035,   -0.000,    0.999);
glm::vec3 WorldUp5 = glm::vec3(0.000,    1.000,    0.000);
float Yaw5 = -2.0;
float Pitch5 = 9.0;

