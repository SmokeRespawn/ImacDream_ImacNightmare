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
    std::string LowPolyTreesPath = "assets/models/LowPolyTrees/LowPolyTrees.obj";               // 0
    std::string LowPolyTreesSolvedPath = "assets/models/LowPolyTrees/LowPolyTreesSolved.obj";   // 1
    std::string LowPolyForestPath = "assets/models/LowPolyForest/monde2.obj" ;                  // 2
    std::string LowPolyForestSolvedPath = "assets/models/LowPolyForest/monde2final.obj" ;       // 3
    std::string monde_3Path = "assets/models/monde_3/monde_3.obj";                              // 4
    std::string monde_3SolvedPath = "assets/models/monde_3/monde_3_portal.obj";                 // 5
    std::string start_endPath = "assets/models/start_end/Start_End.obj";                        // 6

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
    this->LowPolyForestSolvedPath = fullpath + this->LowPolyForestSolvedPath;
    this->monde_3Path = fullpath + this->monde_3Path;
    this->monde_3SolvedPath = fullpath + this->monde_3SolvedPath;
    this->start_endPath = fullpath + this->start_endPath;
    Model LowPolyTrees(LowPolyTreesPath);
    Model LowPolyTreesSolved(LowPolyTreesSolvedPath);
    Model LowPolyForest(LowPolyForestPath);
    Model LowPolyForestSolved(LowPolyForestSolvedPath);
    Model monde_3(monde_3Path);
    Model monde_3Solved(monde_3SolvedPath);
    Model start_end(start_endPath);
    this->models.push_back(LowPolyTrees);
    this->models.push_back(LowPolyTreesSolved);
    this->models.push_back(LowPolyForest);
    this->models.push_back(LowPolyForestSolved);
    this->models.push_back(monde_3);
    this->models.push_back(monde_3Solved);
    this->models.push_back(start_end);
}  

LoadModel::~LoadModel()
{
}
