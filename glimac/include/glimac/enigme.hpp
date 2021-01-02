#pragma once 
#include <glimac/glm.hpp>
#include <vector>

std::vector<glm::vec3> cluePos1 = {
                                  glm::vec3(-1.73,-0.36,12), //poubelle verte
                                  glm::vec3(2.57,15.38,-11.07), //poubelle bleue
                                  glm::vec3(-9.57,6.31,-13.25)  //poubelle jaune
                                };

std::vector<glm::vec3> cluePos2 = {
                                  glm::vec3(2.347, 5.220, -2.685), //bouteille 1
                                  glm::vec3(-6.097, 5.695, -10.349), //bouteille 2 
                                  glm::vec3(-1.445, 0.473, 4.173)  //bouteille 3
                                };

std::vector<glm::vec3> cluePos3 = {
                                  glm::vec3(0.895, 0.693, -3.547), //ramasseur 1
                                  glm::vec3(-4.357, 1.226, -5.262), //ramasseur 2
                                  glm::vec3(2.997, -1.148, -5.618)  //ramasseur 3
                                };

class Enigme
{
public:
    std::vector<glm::vec3> cluePos;
    int clues[3];
    bool solved = false;
    bool telep = false;
    glm::vec3 portail;

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
