# ImacDream_ImacNightmare
Repo pour le projet d'IMAC 2

Librairies à installer (linux): 

 - glfw3 : _ télécharger la dernière version sur ce site : http://www.glfw.org/
           _ extraire l'archive, se placer dans le dossier et executer les commandes suivantes : dans le terminal "cmake -G "Unix Makefiles" 
                                                                                                  puis "sudo apt-get install cmake xorg-dev libglu1-mesa-dev"
                                                                                                  et finalement "sudo make" et "sudo make install"
 - SDL : _ dans le terminal "sudo apt-get install libsdl1.2-dev
 - SDL_mixer : _ dans le terminal "sudo apt-get install libsdl-mixer1.2" et "sudo apt-get install libsdl-mixer1.2-dev"
 - SDL_ttf : _ dans le terminal "sudo apt-get install libsdl-ttf2.0-dev"
 - FreeType : _ dans le terminal "sudo apt-get install libfreetype6-dev"
 - glew : _ dans le terminal "sudo apt-get install libglew-dev"
 
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
    │   │   │   ├── LowPolyForest
    │   │   │   ├── LowPolyTrees
    │   │   │   └── monde_3
    │   │   └── musiques
    │   └── shaders
    └── third-party
        └── include
            └── glm
                ├── detail
                ├── gtc
                └── gtx
Pour charger le jeu : 
se placer dans le dossier project et dans le terminal : 
"cd .. && mkdir build && cd build && cmake ../project && make && ./project/project_main"

Sinon les commandes peuvent se faire une par une : 
créer un dossier build au même niveau que project :
.
├── build
│
└── project
se placer dans le dossier build, ouvrir un terminal en faisant clic droit dans le dossier + ouvrir un terminal\n
Et effectuer :\n
"cmake ../project" pour build le projet, puis "make" pour compiler les librairies et créer l'éxécutable\n 
Et finalement "./project/project_main" pour lancer le jeu\n

