## ImacDream_ImacNightmare
Repo pour le projet d'IMAC 2
--------------------------------------
# Librairies à installer (linux): 

 - glfw3 : _ télécharger la dernière version sur ce site : http://www.glfw.org/
           _ extraire l'archive, se placer dans le dossier et executer les commandes suivantes : dans le terminal __"cmake -G "Unix Makefiles""__ 
                                                                                                  puis __"sudo apt-get install cmake xorg-dev libglu1-mesa-dev"__
                                                                                                  et finalement __"sudo make" et "sudo make install"__
 - SDL : _ dans le terminal __"sudo apt-get install libsdl1.2-dev"__
 - SDL_mixer : _ dans le terminal __"sudo apt-get install libsdl-mixer1.2"__ et __"sudo apt-get install libsdl-mixer1.2-dev"__  
 - SDL_ttf : _ dans le terminal __"sudo apt-get install libsdl-ttf2.0-dev"__  
 - FreeType : _ dans le terminal __"sudo apt-get install libfreetype6-dev"__  
 - glew : _ dans le terminal __"sudo apt-get install libglew-dev"__  
 
 Une fois cloné le dossier du jeu doit bien s'appeler "project", l'arborescence doit ressembler à ça :  
 project  
    ├── assets  
    │   └── models  
    ├── Assimp  
    ├── CMake  
    ├── glimac  
    │   ├── include  
    │   │   └── glimac  
    │   └── src  
    ├── project  
    │   ├── assets  
    │   │   ├── models   
    │   │   └── musiques  
    │   └── shaders  
    └── third-party  
        └── include  
            └── glm  
--------------------------------------            
# Charger le jeu
se placer dans le dossier project et dans le terminal : 
__"cd .. && mkdir build && cd build && cmake ../project && make && ./project/project_main"__  

Sinon les commandes peuvent se faire une par une :   
créer un dossier build au même niveau que project :  
.  
├── build  
│  
└── project  
se placer dans le dossier build, ouvrir un terminal en faisant clic droit dans le dossier + ouvrir un terminal  
Et effectuer :  
__"cmake ../project"__ pour build le projet, puis __"make"__ pour compiler les librairies et créer l'éxécutable  
Et finalement __"./project/project_main"__ pour lancer le jeu  

