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
#include <glimac/actualPath.hpp>
#include <glimac/camera.hpp>
//#include <glimac/modelLoading.hpp>

using namespace glimac;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;


int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    //Load shaders
      FilePath applicationPath(argv[0]);
        Program program = loadProgram(
        applicationPath.dirPath() + "shaders/3D.vs.glsl",
        applicationPath.dirPath() + "shaders/normals.fs.glsl"
    );
    program.use();

    //location variables uniformes
    const GLuint idProg = program.getGLId();
    GLint locationMVPMatrix = glGetUniformLocation(idProg, "uMVPMatrix");
    GLint locationMVMatrix = glGetUniformLocation(idProg, "uMVMatrix");
    GLint locationNormal = glGetUniformLocation(idProg, "uNormalMatrix");

    glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_ALWAYS);

    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 100.f);
    glm::mat4 MVMatrix = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5));
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));


    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    //On charge le chemin actuel 
    std::string fullpath = actualPath(argv[0]);
    
    //On donne les chemins de chaque .obj nécessaires
    std::string LowPolyTreesPath = fullpath + "assets/models/LowPolyTrees/LowPolyTrees.obj";
    std::string monkeyPath = fullpath +  "assets/models/monkey.obj";
    std::string simpleBoxPath = fullpath + "assets/models/simpleBox.obj";
    std::string gobPath = fullpath + "assets/models/gob.obj";
    

    //On charge les modèles avec ASSIMP
    //Model LowPolyTrees(LowPolyTreesPath);
    Model monkey(monkeyPath);
    // Model simpleBox(simpleBoxPath);
    // Model gob(gobPath);

     //création de la caméra
     //FreeflyCamera camera;
     Camera camera;
    bool drawQ = false;
    glm::ivec2 mousePosition = windowManager.getMousePosition();//Get actual mouse position
    // Application loop:
    bool done = false;
    while(!done) {
        float currentFrame = windowManager.getTime();

        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
            if(windowManager.isKeyPressed(SDLK_z))camera.ProcessKeyboard(FORWARD, deltaTime);
            if(windowManager.isKeyPressed(SDLK_s))camera.ProcessKeyboard(BACKWARD, deltaTime);
            if(windowManager.isKeyPressed(SDLK_q))camera.ProcessKeyboard(LEFT, deltaTime);
            if(windowManager.isKeyPressed(SDLK_d))camera.ProcessKeyboard(RIGHT, deltaTime);
            if(windowManager.isKeyPressed(SDLK_SPACE))drawQ = true;

            if(windowManager.isMouseButtonPressed(SDL_BUTTON_RIGHT)){
              //Ici on récupère les positions de la souris
              glm::vec2 mousePos = windowManager.getMousePosition();
              /*float mousePosX = mousePos.x/800.0f - 0.5;
              float mousePosY = mousePos.y/600.0f - 0.5;

              camera.rotateLeft(-2*mousePosX);
              camera.rotateUp(-2*mousePosY);*/
              /*if (firstMouse)
              {
                  lastX = mousePos.x;
                  lastY = mousePos.y;
                  firstMouse = false;
              }*/

              float xoffset = mousePos.x - lastX;
              float yoffset = lastY - mousePos.y; // reversed since y-coordinates go from bottom to top

              lastX = mousePos.x;
              lastY = mousePos.y;

              camera.ProcessMouseMovement(xoffset, yoffset);
                        }
        }

        glm::mat4 ViewMatrix = camera.GetViewMatrix();

        ProjMatrix =  glm::perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 100.f);
        MVMatrix = ViewMatrix * glm::translate(glm::mat4(1), glm::vec3(0, 0, -5));
        MVMatrix = glm::scale(MVMatrix, glm::vec3(0.2f,0.2f,0.2f));
        NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUniformMatrix4fv(
          locationMVPMatrix,
  	      1,
  	      GL_FALSE,
  	      glm::value_ptr(ProjMatrix * MVMatrix));

        glUniformMatrix4fv(
          locationMVMatrix,
          1,
          GL_FALSE,
          glm::value_ptr(MVMatrix));

        glUniformMatrix4fv(
          locationNormal,
          1,
          GL_FALSE,
          glm::value_ptr(NormalMatrix));

        monkey.DrawModel(program);
        //LowPolyTrees.DrawModel(program);
        //simpleBox.DrawModel(program);
        
        //if (drawQ)monkey.DrawModel(program);

        // Update the display
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}