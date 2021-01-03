#pragma once

#include <string>
#include <iostream>
#include "stdlib.h"
std::string actualPath(const char* argv){
    #ifdef _WIN32
      char ownPth[256]; 

      // When NULL is passed to GetModuleHandle, the handle of the exe itself is returned
      HMODULE hModule = GetModuleHandle(NULL);
      if (hModule != NULL)
      {
          // Use GetModuleFileName() with module handle to get the path
          GetModuleFileName(hModule, ownPth, (sizeof(ownPth))); 
          std::cout << ownPth << endl ;
          system("PAUSE");
          return ownPth;
          return 0;
      }
      else
      {
          std::cout << "Module handle is NULL" << endl ;
          system("PAUSE");
          return 0;
      }

    #else
      char buffer[256];
      realpath(argv, buffer);
      std::string fullpath = buffer;
      fullpath = std::string(fullpath, 0, fullpath.rfind("/"));
      fullpath = std::string(fullpath, 0, fullpath.rfind("b"));
      fullpath += "project/project/";
      return fullpath;
      std::cout << fullpath << std::endl;

    #endif
}
