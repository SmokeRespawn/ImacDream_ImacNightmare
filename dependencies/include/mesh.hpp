#ifndef MESH_HPP
#define MESH_HPP

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>
#include <vector>
#include "dependencies/include/shader.hpp"

struct Vertex { //On définit une structure qui contient les informations de nos vertexs
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
};

struct Texture { //On définit une structure qui contient nos informations de texture
    unsigned int id;
    std::string type; //Texture "Diffuse" ou "Spéculaire" (Diffuse or Specular)
    std::string path;
};

class Mesh {
    public:
        // informations du mesh à rendre
        std::vector<Vertex>       vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture>      textures;

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures){
            this->vertices = vertices;
            this->indices = indices;
            this->textures = textures;

            setupMesh();
        }

        void Draw(Shader &shader) {
            unsigned int diffuseNr = 1;
            unsigned int specularNr = 1;
            for(unsigned int i = 0; i < textures.size(); i++)
            {
                glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
                // retrieve texture number (the N in diffuse_textureN)
                std::string number;
                std::string name = textures[i].type;
                if(name == "texture_diffuse")
                    number = std::to_string(diffuseNr++);
                else if(name == "texture_specular")
                    number = std::to_string(specularNr++);

                shader.setFloat(("material." + name + number).c_str(), i);
                glBindTexture(GL_TEXTURE_2D, textures[i].id);
            }
            glActiveTexture(GL_TEXTURE0);

            // draw mesh
            glBindVertexArray(vao);
            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }  
    private:
        //  informations pour le rendu
        unsigned int vao,vbo,ebo;

        void setupMesh(){ //Initialise un mesh 
            glGenVertexArrays(1, &vao);
            glGenBuffers(1, &vbo);
            glGenBuffers(1, &ebo); //On génère les 3 buffers
        
            glBindVertexArray(vao);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);

            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW); //On remplit les données avec les informations du mesh

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), 
                        &indices[0], GL_STATIC_DRAW);

            // vertex positions
            glEnableVertexAttribArray(0);	
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
            // vertex normals
            glEnableVertexAttribArray(1);	
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
            // vertex texture coords
            glEnableVertexAttribArray(2);	
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

            glBindVertexArray(0); //On pense a debind à la fin
        }  
};  

#endif
