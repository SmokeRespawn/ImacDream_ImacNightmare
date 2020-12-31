#version 300 es
precision mediump float;

// Sorties du shader
in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
in vec2 vTexCoords; // Coordonnées de texture du sommet

out vec3 fFragColor;


//Représenter le matériau de l'objet en cours de dessin
uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

//passer info de lumières au shader
uniform vec3 uLightDir_vs;      //vs => on travaille dans le view space (multiplier direction par VM avant envoi au shader)
uniform vec3 uLightIntensity;

vec3 BlinnPhong(vec3 position_vs, vec3 normal_vs){
    vec3 w_zero = normalize(-position_vs);
	vec3 w_i = normalize(-uLightDir_vs);
	vec3 vector;
    vector = (w_zero + w_i);
    vec3 halfVector = 0.5 * vector;


	return uLightIntensity * ( uKd * ( dot(w_i, normal_vs ) ) + uKs * ( pow( dot(halfVector, normal_vs), uShininess ) ) );
}


void main() {
  fFragColor = BlinnPhong(vPosition_vs, normalize(vNormal_vs));
}
