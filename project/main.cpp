#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glimac/SDLWindowManager.hpp>

#include <SDL/SDL_mixer.h>

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
#include <glimac/modelLoading.hpp>



using namespace glimac;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
void printVec3(glm::vec3 vec);

// settings
const unsigned int SCR_WIDTH = 1080;
const unsigned int SCR_HEIGHT = 720;

// camera
Camera camera(glm::vec3(-2.3f, 10.f, 28.f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;


int main(int argc, char** argv) {

  // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif




    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "IMACGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); //Changer NORMAL en disabled pour avoir une souris invisible, mais caméra fonctionne mieux en NORMAL
    // Initialize SDL and open a window
    //SDLWindowManager windowManager(800, 600, "GLImac");

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
    LoadModel LoadModel(fullpath);

    //initialisation de SDL_Mixer, attention == ça renvoie 0 si c bon et -1 si y'a une erreur, d'où le Mix_GetError
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
        std::cout << Mix_GetError() << std::endl;
    }
    Mix_Music *musique;
    
    std::string chemin = fullpath+"/assets/musiques/7rings-ariana.mp3";
    //const char *music1 = fullpath.c_str() + "/assets/musiques/music1.mp3".c_str();
    musique = Mix_LoadMUS(chemin.c_str());
    Mix_PlayMusic(musique, -1); //Joue infiniment la musique


    //On charge les modèles avec ASSIMP

    // Application loop:
    bool done = false;
    while(!glfwWindowShouldClose(window)) {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;


        // input
        // -----
        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
            glfwSetCursorPosCallback(window, mouse_callback);//On place la souris au centre de l'écran et on appuie sur P
        processInput(window);

        glm::mat4 ViewMatrix = camera.GetViewMatrix();
        glm::mat4 ProjMatrix = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //ProjMatrix =  glm::perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 100.f);
        MVMatrix = ViewMatrix * glm::translate(glm::mat4(1), glm::vec3(0, 0, -5));
        MVMatrix = glm::scale(MVMatrix, glm::vec3(0.5f,0.5f,0.5f));
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
        LoadModel.models[0].DrawModel(program);
        //LoadModel.models[4].DrawModel(program);
        printVec3(camera.Position);
        //LoadModel.drawModelLoaded(LoadModel.models["LowPolyTrees"]);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

<<<<<<< HEAD

    //on libère la musique
    Mix_FreeMusic(musique);
    //on ferme SDL_mixer
    Mix_CloseAudio();


=======
>>>>>>> Alo_camera_mouv
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
<<<<<<< HEAD
    if (glm::distance(camera.Position,glm::vec3(-2.3f, 10.f, 28.f)) < 1.0){
        std::cout << "A distance d'activer" << std::endl;
        std::cout << Mix_GetError() << std::endl;
        if (glfwGetKey(window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS)
            camera.Position = glm::vec3(-2.3f, 10.f, 28.f);
    }
    
=======
/*  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            camera.moveUP(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_CTRL) == GLFW_PRESS)
        camera.MoveUp(DOWN, deltaTime);
// acceleration camera 
    if (glfwGetKey(window, GLFW_KEY_SHIFT) == GLFW_PRESS)
        camera.Accelerer(SPEEDUP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_CTRL+SHIFT) == GLFW_PRESS)
        camera.Accelerer(SLOWDOWN, deltaTime);    
    */
>>>>>>> Alo_camera_mouv
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

void printVec3(glm::vec3 vec){
    std::cout << "x : " << vec.x << " | y : " << vec.y << " | z : " << vec.z << std::endl;
    // printAttributes(camera);
}