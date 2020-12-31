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

class LoadModel
{
public:
    std::string LowPolyTreesPath = "assets/models/LowPolyTrees/LowPolyTrees.obj"; // 0
    std::string monkeyPath = "assets/models/monkey.obj";                          // 1
    std::string simpleBoxPath = "assets/models/simpleBox.obj";                    // 2
    std::string LowPolyForestPath = "assets/models/LowPolyForest/LowPolyForest.obj" ;// 3
    std::string LowPolyTreesSolvedPath = "assets/models/LowPolyTrees/LowPolyTreesSolved.obj"; // 4
    std::vector<Model> models;
public:
    LoadModel();
    LoadModel(std::string fullpath);
    ~LoadModel();
};

LoadModel::LoadModel(std::string fullpath)
{
    this->LowPolyTreesPath = fullpath + this->LowPolyTreesPath;
    this->LowPolyTreesSolvedPath = fullpath + this->LowPolyTreesSolvedPath;
    this->monkeyPath = fullpath + this->monkeyPath;
    this->simpleBoxPath = fullpath + this->simpleBoxPath;
    this->LowPolyForestPath = fullpath + this->LowPolyForestPath;
    Model LowPolyTrees(LowPolyTreesPath);
    Model monkey(monkeyPath);
    Model simpleBox(simpleBoxPath);
    Model LowPolyForest(LowPolyForestPath);
    Model LowPolyTreesSolved(LowPolyTreesSolvedPath);
    this->models.push_back(LowPolyTrees);
    this->models.push_back(monkey);
    this->models.push_back(simpleBox);
    this->models.push_back(LowPolyForest);
    this->models.push_back(LowPolyTreesSolved);

    

}   

LoadModel::~LoadModel()
{
}
