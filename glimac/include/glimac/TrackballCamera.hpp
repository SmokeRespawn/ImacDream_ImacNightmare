#pragma once
#include "common.hpp"

namespace glimac {

// Gère la TrackBallCamera
class TrackballCamera {

public:
    // Constructeurs
    TrackballCamera():
    m_fDistance(5.0),m_fAngleX(0.0),m_fAngleY(0.0){}

    TrackballCamera(GLfloat fDistance, GLfloat fAngleX, GLfloat fAngleY):
        m_fDistance(fDistance),m_fAngleX(fAngleX),m_fAngleY(fAngleY) {}

   void moveFront(float delta){// permettant d'avancer / reculer la caméra. Lorsque delta est positif la caméra doit avancer, sinon elle doit reculer.
      this->m_fDistance += delta;
   }
   void rotateLeft(float degrees){// permettant de tourner latéralement autour du centre de vision.
     this->m_fAngleX += degrees;
   }
   void rotateUp(float degrees){//permettant de tourner verticalement autour du centre de vision.
     this->m_fAngleY += degrees;
   }

   glm::mat4 getViewMatrix() const{
     glm::mat4 viewMatrix = glm::translate(glm::mat4(),glm::vec3(0.,0.,-this->m_fDistance));
     viewMatrix = glm::rotate(viewMatrix,this->m_fAngleX,glm::vec3(1.,0.,0.));
     viewMatrix = glm::rotate(viewMatrix,this->m_fAngleY,glm::vec3(0.,1.,0.));
     return viewMatrix;
   }



private:
    GLfloat m_fDistance; //Distance from the center
    GLfloat m_fAngleX;
    GLfloat m_fAngleY;
};

}
