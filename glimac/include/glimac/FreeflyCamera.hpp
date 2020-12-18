#pragma once
#include "common.hpp"

namespace glimac {

// Gère la FreeflyCamera
class FreeflyCamera {

public:
    // Constructeurs
    FreeflyCamera():
    m_Position(glm::vec3(0.,0.,0.)),m_fPhi(glm::pi<float>()),m_fTheta(0.0){
      computeDirectionVectors();
    }
    //~FreeflyCamera();

    void computeDirectionVectors(){
      this->m_FrontVector = glm::vec3(glm::cos(m_fTheta)*glm::sin(m_fPhi), glm::sin(m_fTheta), glm::cos(m_fTheta)*glm::cos(m_fPhi));//F⃗ =(cos(θ)sin(ϕ), sin(θ), cos(θ)cos(ϕ))
      this->m_LeftVector = glm::vec3(glm::sin(m_fPhi +m_fPhi/2), 0.0, glm::cos(m_fPhi +m_fPhi/2));//L⃗ =(sin(ϕ+π2), 0, cos(ϕ+π2))
      this->m_UpVector = glm::cross(m_FrontVector,m_LeftVector); //U⃗ =F⃗ ×L⃗
    }


   void moveLeft(float t){//déplacer un point P le long d'un vecteur V correspond à faire P += t*V
      this->m_Position += t*m_LeftVector;
   }
   void moveFront(float t){
      this->m_Position += t*m_FrontVector;
   }
   void rotateLeft(float degrees){//attention à convertir degrees en radians avant de faire l'addition avec les angles courants
    this->m_fPhi += glm::radians(degrees);
    computeDirectionVectors();
   }
   void rotateUp(float degrees){
     this->m_fTheta += glm::radians(degrees);
     computeDirectionVectors();
   }

   glm::mat4 getViewMatrix() const{
     glm::vec3 v = this->m_Position + this->m_FrontVector;
     return glm::lookAt(this->m_Position,v,this->m_UpVector);
   }



private:
    glm::vec3 m_Position;
    float m_fPhi;
    float m_fTheta;
    glm::vec3 m_FrontVector;
    glm::vec3 m_LeftVector;
    glm::vec3 m_UpVector;
};

}
