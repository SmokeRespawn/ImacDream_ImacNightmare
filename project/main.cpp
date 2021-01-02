#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glimac/SDLWindowManager.hpp>
#include <time.h>

#include <SDL/SDL_mixer.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <iostream>

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <glimac/camera.hpp>
#include <glimac/CameraAttributes.hpp>

#include <glimac/glm.hpp>
#include <glimac/Model.hpp>
#include <glimac/actualPath.hpp>
#include <glimac/camera.hpp>
#include <glimac/modelLoading.hpp>
#include <glimac/enigme.hpp>
#include <glimac/font.hpp>


using namespace glimac;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
void enigme(GLFWwindow *window,LoadModel* LoadModel, Enigme* enigme);
void printVec3(glm::vec3 vec);
void game(GLFWwindow *window,LoadModel* LoadModel,Enigme* enigme1,Enigme* enigme2, Enigme* enigme3,Program* program);

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

long t = time(0);
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
    
    Program textProgram = loadProgram(
                                applicationPath.dirPath() + "shaders/text.vs.glsl",
                                applicationPath.dirPath() + "shaders/text.fs.glsl"
                                );

    

    //location variables uniformes
    const GLuint idProg = program.getGLId();
    GLint locationMVPMatrix = glGetUniformLocation(idProg, "uMVPMatrix");
    GLint locationMVMatrix = glGetUniformLocation(idProg, "uMVMatrix");
    GLint locationNormal = glGetUniformLocation(idProg, "uNormalMatrix");

    //On récupère les lumières
    GLint uLightDir = glGetUniformLocation(idProg, "light.direction");
    GLint uLightAmbient = glGetUniformLocation(idProg, "light.ambient");
    GLint uLightDiffuse = glGetUniformLocation(idProg, "light.diffuse");
    GLint uLightSpecular = glGetUniformLocation(idProg, "light.specular");

    //On récupère les matériaux
    GLint uMatDiffuse = glGetUniformLocation(idProg, "material.diffuse");
    GLint uMatSpecular = glGetUniformLocation(idProg, "material.specular");
    GLint uMatShininess = glGetUniformLocation(idProg, "material.shininess");

    GLint uViewPos = glGetUniformLocation(idProg, "material.viewPos");

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
    
    std::string chemin = fullpath+"/assets/musiques/music2.mp3";
    //const char *music1 = fullpath.c_str() + "/assets/musiques/music1.mp3".c_str();
    musique = Mix_LoadMUS(chemin.c_str());
    Mix_PlayMusic(musique, -1); //Joue infiniment la musique
    
    //On charge les enigmes
    Enigme enigme1;
    Enigme enigme2;
    Enigme enigme3;
    enigme1.setCluePositions(cluePos1); //cluePos1 déclaré dans enigme
    enigme2.setCluePositions(cluePos2); //cluePos2 déclaré dans enigme
    enigme3.setCluePositions(cluePos2); //a faire
    Font font(fullpath);
    font.fontInit();
    float vertices[] = {-100.f,-100.f,0.,1.,
                        100.f,-100.f,1.,1.,
                        100.f,100.f, 0.5,0.,
                        -100.f,100.f,0.,0.};
    textProgram.use();
    GLuint VAOtext,VBOtext;
    glGenVertexArrays(1, &VAOtext);
    glGenBuffers(1, &VBOtext);
    glBindVertexArray(VAOtext);
    glBindBuffer(GL_ARRAY_BUFFER, VBOtext);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, vertices, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(7);
    glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    printVec3(enigme1.cluePos[0]);
    program.use();
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

        glm::vec4 LightDir(1.0f, 1.0f, 1.0f, 0.0f);
        LightDir = LightDir*ViewMatrix;
        glUniform3f(uLightDir, LightDir.x, LightDir.y, LightDir.z);
        glUniform3f(uViewPos, camera.Position.x, camera.Position.y, camera.Position.z);

        glUniform3f(uLightAmbient, 0.5f, 0.5f, 0.5f);
        glUniform3f(uLightDiffuse, 1.2f, 1.2f, 1.2f);
        glUniform3f(uLightSpecular, 1.2f, 1.2f, 1.2f);

        glUniform3f(uMatSpecular, 0.5f, 0.5f, 0.5f);
        glUniform1f(uMatShininess, 15.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUniformMatrix4fv(locationMVPMatrix,1,GL_FALSE,glm::value_ptr(ProjMatrix * MVMatrix));

        glUniformMatrix4fv(locationMVMatrix,1,GL_FALSE,glm::value_ptr(MVMatrix));

        glUniformMatrix4fv(locationNormal,1,GL_FALSE,glm::value_ptr(NormalMatrix));
        /* Lancement du jeu */
        program.use();
        game(window,&LoadModel,&enigme1,&enigme2,&enigme3,&program);
        textProgram.use();
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glm::mat4 projection = glm::ortho(0.0f, 1080.0f, 0.0f, 720.0f);
        glUniformMatrix4fv(glGetUniformLocation(textProgram.getGLId(),"projection"),1,GL_FALSE,glm::value_ptr(projection));
        
        font.RenderText(&textProgram,VAOtext,VBOtext, "This is sample text", 25.f, 25.f, 5.f, glm::vec3(1.f, 0.f, 0.f));
        //program.use();

        
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    //on libère la musique
    Mix_FreeMusic(musique);
    //on ferme SDL_mixer
    Mix_CloseAudio();
    //font.killFont();

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
    if (glm::distance(camera.Position,glm::vec3(-2.3f, 10.f, 28.f)) < 1.0){
        //std::cout << "A distance d'activer" << std::endl;
        std::cout << Mix_GetError() << std::endl;
        if (glfwGetKey(window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS)
            camera.Position = glm::vec3(-2.3f, 10.f, 28.f);
    }
    
    //affichage des coordonnées de la caméra
    camera.PrintCameraPosition(camera.Position, camera.Front, camera.Up, camera.Right, camera.WorldUp, camera.Yaw, camera.Pitch);


/*  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            camera.moveUP(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_CTRL) == GLFW_PRESS)
// acceleration camera 
        camera.MoveUp(DOWN, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SHIFT) == GLFW_PRESS)
        camera.Accelerer(SPEEDUP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_CTRL+SHIFT) == GLFW_PRESS)
        camera.Accelerer(SLOWDOWN, deltaTime);    
    */
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

void enigme(GLFWwindow *window,LoadModel* LoadModel, Enigme* enigme){
    if (glm::distance(camera.Position,enigme->cluePos[0]) < 2.0){
        std::cout << "Appuyez sur E pour valider l'indice 1" << std::endl;
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
            enigme->clues[0] = 1;
            std::cout << "Indice 1 validé !" << std::endl;
        }
    }
    if (glm::distance(camera.Position,enigme->cluePos[1]) < 2.0){
        std::cout << "Appuyez sur E pour valider l'indice 2" << std::endl;
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
            enigme->clues[1] = 2;
            std::cout << "Indice 2 validé !" << std::endl;
        }
    }
    if (glm::distance(camera.Position,enigme->cluePos[2]) < 2.0){
        std::cout << "Appuyez sur E pour valider l'indice 3" << std::endl;
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
            enigme->clues[2] = 3;
            std::cout << "Indice 3 validé !" << std::endl;
        }
    }
    if (enigme->clues[0] == 1 && enigme->clues[1] == 2 && enigme->clues[2] == 3){
        std::cout << "Bravo vous avez terminé ce monde, allez sur la plateforme de téléportation devant la maison et appuyez sur T pour vous téléporter vers le monde suivant !" << std::endl;
        enigme->solved = true;
        std::cout << to_string(enigme->solved);
        //juste à mettre la téléportation vers le monde 2
    }
}


void game(GLFWwindow *window,LoadModel* LoadModel,Enigme* enigme1,Enigme* enigme2, Enigme* enigme3,Program* program){
    
    enigme1->portail = glm::vec3(3.702, 12.891, -4.451);
    enigme2->portail = glm::vec3(1.119, 0.709, 6.519);
    enigme3->portail = glm::vec3(3.702, 12.891, -4.451);

    std::cout << " 1 : " << enigme1->clues[0] << " | 2 : " << enigme1->clues[1] << " | 3 : " << enigme1->clues[2] << std::endl;
    std::cout << " 1 : " << enigme2->clues[0] << " | 2 : " << enigme2->clues[1] << " | 3 : " << enigme3->clues[2] << std::endl;
    std::cout << " 1 : " << enigme2->clues[0] << " | 2 : " << enigme2->clues[1] << " | 3 : " << enigme3->clues[2] << std::endl;

    if(!enigme1->solved && !enigme1->telep){
        LoadModel->models[0].DrawModel(*program);
        enigme(window,LoadModel,enigme1);
    }
    if(enigme1->solved && !enigme1->telep){
        LoadModel->models[1].DrawModel(*program);
        enigme(window,LoadModel,enigme1);
        std::cout << "solved" << std::endl;
        if(glm::distance(camera.Position, enigme1->portail) < 3.0) {
            enigme1->telep = true;
        } else {
            enigme1->telep = false;
        }
    }
    if(enigme1->solved && enigme1->telep && !enigme2->solved && !enigme2->telep){
        enigme(window,LoadModel,enigme2);
        LoadModel->models[2].DrawModel(*program);
    }
    if(enigme1->solved && enigme1->telep && enigme2->solved && !enigme2->telep){
        enigme(window,LoadModel,enigme2);
        LoadModel->models[3].DrawModel(*program);
        std::cout << "solved" << std::endl;
        if(glm::distance(camera.Position, enigme2->portail) < 3.0) {
            enigme2->telep = true;
        } else {
            enigme2->telep = false;
        }
    }
    if(enigme1->solved && enigme1->telep && enigme2->solved && enigme2->telep && !enigme3->solved && !enigme3->telep){
        enigme(window,LoadModel,enigme3);
        LoadModel->models[4].DrawModel(*program);
    }
    if(enigme1->solved && enigme1->telep && enigme2->solved && enigme2->telep && enigme3->solved && !enigme3->telep){
        enigme(window,LoadModel,enigme3);
        LoadModel->models[5].DrawModel(*program);
        std::cout << "solved" << std::endl;
        if(glm::distance(camera.Position, enigme3->portail) < 3.0) {
            enigme3->telep = true;
        } else {
            enigme3->telep = false;
        }
    }
        
}
