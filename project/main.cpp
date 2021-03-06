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
void game(GLFWwindow *window,LoadModel* LoadModel,Enigme* enigme1,Enigme* enigme2, Enigme* enigme3,Program* program,Font* font,Camera* camera);
void write(Font* font, Program* textProgram,GLuint VAOtext,GLuint VBOtext, std::string text);
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

bool start = false;
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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "ECOLOJEU", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); //Changer NORMAL en disabled pour avoir une souris invisible, mais caméra fonctionne mieux en NORMAL
    
    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    //initialisation de SDL_Mixer
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
        std::cout << Mix_GetError() << std::endl;
    }
    Mix_Music *musique;

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

    

    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 100.f);
    glm::mat4 MVMatrix = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5));
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));


 

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    //On charge le chemin actuel 
    std::string fullpath = actualPath(argv[0]);
    
    //On donne les chemins de chaque .obj nécessaires
    LoadModel LoadModel(fullpath);

    
    
    std::string chemin = fullpath+"/assets/musiques/music.mp3";
    musique = Mix_LoadMUS(chemin.c_str());
    Mix_PlayMusic(musique, -1); //Joue infiniment la musique
    
    //On charge les enigmes
    Enigme enigme1;
    Enigme enigme2;
    Enigme enigme3;
    enigme1.setCluePositions(cluePos1); //cluePos1 déclaré dans enigme
    enigme2.setCluePositions(cluePos2); //cluePos2 déclaré dans enigme
    enigme3.setCluePositions(cluePos3); //a faire
    enigme3.setCluePositions(cluePos2); //a faire

    //On initialise Font 
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

    program.use();
    // Application loop:
    glEnable(GL_DEPTH_TEST);
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
        if (!start){
            camera.setAttributes(Position4,Front4,Up4,Right4,WorldUp4,Yaw4,Pitch4);
            LoadModel.models[6].DrawModel(program);
            write(&font,&textProgram,VAOtext,VBOtext,"Bienvenue, appuyez sur espace pour commencer et P pour utiliser regarder autour de vous.");
            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
                start = true;
                camera.setAttributes(Position1,Front1,Up1,Right1,WorldUp1,Yaw1,Pitch1);
            }
                
        }
        else {
            game(window,&LoadModel,&enigme1,&enigme2,&enigme3,&program,&font,&camera);
            write(&font,&textProgram,VAOtext,VBOtext,font.textToPrint);
        }
        
        program.use();

        
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

void enigme(GLFWwindow *window,LoadModel* LoadModel, Enigme* enigme,Font* font){
    if (glm::distance(camera.Position,enigme->cluePos[0]) < 2.0){
        if (font->textToPrint != "Indice 1 : ok !"){
            font->textToPrint = "Appuyez sur E pour valider l'indice 1";
        }
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
            enigme->clues[0] = 1;
            font->textToPrint = "Indice 1 : ok !";
        }
    }
    if (glm::distance(camera.Position,enigme->cluePos[1]) < 2.0){
        if (font->textToPrint != "Indice 2 : ok !"){
            font->textToPrint = "Appuyez sur E pour valider l'indice 2";
        }
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
            enigme->clues[1] = 2;
            font->textToPrint = "Indice 2 : ok !";
        }
    }
    if (glm::distance(camera.Position,enigme->cluePos[2]) < 2.0){
        if (font->textToPrint != "Indice 3 : ok !"){
            font->textToPrint = "Appuyez sur E pour valider l'indice 3";
        }
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
            enigme->clues[2] = 3;
            font->textToPrint = "Indice 3 : ok !";
        }
    }
    if (enigme->clues[0] == 1 && enigme->clues[1] == 2 && enigme->clues[2] == 3){
        font->textToPrint = "Bravo ! Allez sur la plateforme pour changer de monde !";
        enigme->solved = true;
    }
}


void game(GLFWwindow *window,LoadModel* LoadModel,Enigme* enigme1,Enigme* enigme2, Enigme* enigme3,Program* program,Font* font,Camera* camera){
    
    enigme1->portail = glm::vec3(3.702, 12.891, -4.451);
    enigme2->portail = glm::vec3(1.119, 0.709, 6.519);
    enigme3->portail = glm::vec3(-15.997, 0.422, -5.708);

    if(!enigme1->solved && !enigme1->telep){
        LoadModel->models[0].DrawModel(*program);
        LoadModel->models[7].DrawModel(*program);
        enigme(window,LoadModel,enigme1,font);
    }
    if(enigme1->solved && !enigme1->telep){
        LoadModel->models[1].DrawModel(*program);
        LoadModel->models[7].DrawModel(*program);
        enigme(window,LoadModel,enigme1,font);
        if(glm::distance(camera->Position, enigme1->portail) < 3.0) {
            enigme1->telep = true;
            font->textToPrint = "Bienvenue dans le monde 2 !";
            camera->setAttributes(Position2,Front2,Up2,Right2,WorldUp2,Yaw2,Pitch2);
        } else {
            enigme1->telep = false;
        }
    }
    if(enigme1->solved && enigme1->telep && !enigme2->solved && !enigme2->telep){
        enigme(window,LoadModel,enigme2,font);
        LoadModel->models[2].DrawModel(*program);
        LoadModel->models[8].DrawModel(*program);
    }
    if(enigme1->solved && enigme1->telep && enigme2->solved && !enigme2->telep){
        enigme(window,LoadModel,enigme2,font);
        LoadModel->models[3].DrawModel(*program);
        LoadModel->models[8].DrawModel(*program);
        if(glm::distance(camera->Position, enigme2->portail) < 3.0) {
            enigme2->telep = true;
            font->textToPrint = "Si rapide ?? Bienvenue dans le monde 3 !";
            camera->setAttributes(Position3,Front3,Up3,Right3,WorldUp3,Yaw3,Pitch3);
        } else {
            enigme2->telep = false;
        }
    }
    if(enigme1->solved && enigme1->telep && enigme2->solved && enigme2->telep && !enigme3->solved && !enigme3->telep){
        enigme(window,LoadModel,enigme3,font);
        LoadModel->models[4].DrawModel(*program);
        LoadModel->models[9].DrawModel(*program);
    }
    if(enigme1->solved && enigme1->telep && enigme2->solved && enigme2->telep && enigme3->solved && !enigme3->telep){
        enigme(window,LoadModel,enigme3,font);
        LoadModel->models[5].DrawModel(*program);
        LoadModel->models[9].DrawModel(*program);
        if(glm::distance(camera->Position, enigme3->portail) < 3.0) {
            enigme3->telep = true;
            font->textToPrint = "Bravo !";
            camera->setAttributes(Position5,Front5,Up5,Right5,WorldUp5,Yaw5,Pitch5);
        } else {
            enigme3->telep = false;
        }
    }
    if(enigme1->solved && enigme1->telep && enigme2->solved && enigme2->telep && enigme3->solved && enigme3->telep){
        LoadModel->models[6].DrawModel(*program);
        LoadModel->models[10].DrawModel(*program);
    }
        
}

void write(Font* font, Program* textProgram,GLuint VAOtext,GLuint VBOtext, std::string text){
    textProgram->use();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glm::mat4 projection = glm::ortho(0.0f, 1080.0f, 0.0f, 720.0f);
    glUniformMatrix4fv(glGetUniformLocation(textProgram->getGLId(),"projection"),1,GL_FALSE,glm::value_ptr(projection));
    
    font->RenderText(textProgram,VAOtext,VBOtext, text, 5.f, 680.f, 0.4f, glm::vec3(1.f, 1.f, 1.f));
}