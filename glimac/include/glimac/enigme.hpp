#pragma once 
#include <glimac/glm.hpp>
#include <vector>

std::vector<glm::vec3> cluePos1 = {
                                  glm::vec3(-1.73,-0.36,12), //poubelle verte
                                  glm::vec3(2.57,15.38,-11.07), //poubelle bleue
                                  glm::vec3(-9.57,6.31,-13.25)  //poubelle jaune
                                };

class Enigme
{
public:
    std::vector<glm::vec3> cluePos;
    int clues[3];
    bool solved = false;

public:
    inline void setSolved(bool value){
        this->solved = value;
    }
    void setCluePositions(glm::vec3 pos){
        this->cluePos.push_back(pos);
    }
    void setCluePositions(std::vector<glm::vec3> posVec){
        for (int i = 0; i < posVec.size();i++){
            this->cluePos.push_back(posVec.at(i)); //utilisation de at pour gérer l'erreur
       }
    }
    void setClueValue(int i,int n){
        this->clues[i] = n;
    }
};
