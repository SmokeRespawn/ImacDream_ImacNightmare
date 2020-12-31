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
    std::string LowPolyTreesSolvedPath = "assets/models/LowPolyTrees/LowPolyTreesSolved.obj"; // 1
    std::string LowPolyForestPath = "assets/models/LowPolyForest/LowPolyForest.obj" ;// 2
    std::string monde_3Path = "assets/models/monde_3/monde_3.obj";                    // 3
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
    this->LowPolyForestPath = fullpath + this->LowPolyForestPath;
    this->monde_3Path = fullpath + this->monde_3Path;
    Model LowPolyTrees(LowPolyTreesPath);
    Model LowPolyTreesSolved(LowPolyTreesSolvedPath);
    Model LowPolyForest(LowPolyForestPath);
    //Model monde_3(monde_3Path);
    this->models.push_back(LowPolyTrees);
    this->models.push_back(LowPolyTreesSolved);
    this->models.push_back(LowPolyForest);
    //this->models.push_back(monde_3);
}  

LoadModel::~LoadModel()
{
}
