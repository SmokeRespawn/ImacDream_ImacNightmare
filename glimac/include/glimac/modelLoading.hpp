#pragma once
#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/FreeflyCamera.hpp>

#include <glimac/glm.hpp>
#include <glimac/Model.hpp>

/*

Model loadModels(std::string userPath);

class LoadModel
{
private:
    std::string LowPolyTreesPath = userPath + "assets/models/LowPolyTrees/LowPolyTrees.obj";
    std::string monkeyPath = userPath + "assets/models/monkey.obj";
    std::string simpleBoxPath = userPath + "assets/models/simpleBox.obj";
    std::string gobPath = userPath + "assets/models/gob.obj";
public:
    LoadModel();
    ~LoadModel();
    
    void monkey(){
        monkey.DrawModel(program);
    }
};

LoadModel::LoadModel()
{
    Model LowPolyTrees(LowPolyTreesPath);
    Model monkey(monkeyPath);
    Model simpleBox(simpleBoxPath);
    Model gob(gobPath);
}

LoadModel::~LoadModel()
{
}
*/