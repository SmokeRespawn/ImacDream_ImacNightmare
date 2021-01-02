#pragma once 
#include <ft2build.h>
#include FT_FREETYPE_H
#include <iostream>
#include <glimac/glm.hpp>
#include <map>
#include <GL/glew.h>

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>

using namespace glimac;

struct Character {
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};




class Font
{
private:
    FT_Library ft;
    std::string fullpath;
    FT_Face face;
    std::map<char, Character> Characters;
public:
    Font(std::string fullpath):fullpath(fullpath){}
    int fontInit();
    void RenderText(Program* program,unsigned int VAOtext, unsigned int VBOtext, std::string text, float x, float y, float scale, glm::vec3 color);
};

