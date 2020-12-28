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
    std::string LowPolyTreesPath = "assets/models/LowPolyTrees/LowPolyTrees.obj"; // 0
    std::string monkeyPath = "assets/models/monkey.obj";                          // 1
    std::string simpleBoxPath = "assets/models/simpleBox.obj";                    // 2
    std::string LowPolyForestPath = "assets/models/LowPolyForest/LowPolyForest.obj"; //3
    std::vector<Model> models;
public:
    LoadModel();
    ~LoadModel();
    
    void monkey(){
        monkey.DrawModel(program);
    }
};

LoadModel::LoadModel()
{
    this->LowPolyTreesPath = fullpath + this->LowPolyTreesPath;
    this->monkeyPath = fullpath + this->monkeyPath;
    this->simpleBoxPath = fullpath + this->simpleBoxPath;
    this->LowPolyForestPath = fullpath + this->LowPolyForestPath;
    Model LowPolyTrees(LowPolyTreesPath);
    Model monkey(monkeyPath);
    Model simpleBox(simpleBoxPath);
    Model LowPolyForest(LowPolyForestPath);
    this->models.push_back(LowPolyTrees);
    this->models.push_back(monkey);
    this->models.push_back(simpleBox);
    this->models.push_back(LowPolyForest);
}

LoadModel::~LoadModel()
{
}
*/