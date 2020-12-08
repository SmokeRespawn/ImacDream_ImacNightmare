#include <iostream>

int main(){
    std::cout << "Phrase de test pour vous montrer les branches" << std::endl;
    std::cout <<"Phrase pour remercier Paul du fond du coeur " <<std::endl;
    int skills = 0;
    std::cout << "Skills de Clo avant le projet : "  << skills << std::endl;
    for(skills=0;skills<100;skills++){
      skills += 10;
      std::cout << "Et hop une nouvelle compétence ! Maintenant elle est à " << skills << std::endl;
    }
    std::cout << "Alo la plus belle" << std::endl;
return 0;
}
