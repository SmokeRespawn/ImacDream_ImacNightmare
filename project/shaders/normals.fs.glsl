#version 300 es
precision mediump float;

// Sorties du vertex shader
in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
in vec2 vTexCoords; // Coordonnées de texture du sommet

//variable uniforme pour la texture
uniform sampler2D uTexture;

//structure pour le reflet sur la texture
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

//structure qui gère l'émission de la lumière
struct Light {
  vec3 direction; 
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

//sortie du shader
out vec4 fFragColor;


void main() {
  //fFragColor = texture(uTexture, vTexCoords).xyz;

  //calcul de l'ambient avec la texture
  vec3 ambient = light.ambient * vec3(texture(material.diffuse, vTexCoords).xyz);

  //calcul de la diffuse 
  vec3 Norm = normalize(vNormal_vs);
  vec3 LightDirection = normalize(-light.direction);
  float LightDot = max(dot(Norm,LightDirection), 0.0);
  vec3 Diffuse =  light.diffuse * LightDot * texture(material.diffuse, vTexCoords).xyz;

  //calcul de la specular
  vec3 View = normalize(viewPos - vPosition_vs);
  vec3 ReflectDirection = reflect(-LightDirection, Norm);
  float Spect = max(dot(ReflectDirection, View), 0.0);
  vec3 Specular = light.specular*(Spect * texture(material.specular, vTexCoords).xyz);

  vec3 result = ambient + Diffuse + Specular;   
  fFragColor =  vec4(result, 1.0);
}
