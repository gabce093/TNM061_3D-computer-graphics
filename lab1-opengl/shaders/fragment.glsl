
# version 330 core
uniform  float  time;
uniform  mat4 T;
// --- Add this to the declarations in the fragment shader
//in vec3 interpolatedColor ;

in vec3 interpolatedNormal;
in vec2 st;
in vec3 transformedLight;

out vec4 finalcolor ;
void main () {
    // vec3 L is the  light  direction
// vec3 V is the  view  direction  - (0,0,1) in view  space
// vec3 N is the  normal
// vec3 R is the  computed  reflection  direction
//  float n is the "shininess" parameter
// vec3 ka is the  ambient  reflection  color
// vec3 Ia is the  ambient  illumination  color
// vec3 kd is the  diffuse  surface  reflection  color
// vec3 Id is the  diffuse  illumination  color
// vec3 ks is the  specular  surface  reflection  color
// vec3 Is is the  specular  illumination  color
// This  assumes  that N, L and V are  normalized.
/*
vec3 R = 2.0* dot(interpolatedNormal,transformedLight)*interpolatedNormal - transformedLight; //  Could  also  have  used  the  function  reflect ()
float  dotNL = max(dot(interpolatedNormal,transformedLight), 0.0); // If negative , set to zero
float  dotRV = max(dot(R,vec3(0.0,0.0,1.0)), 0.0);
if (dotNL  == 0.0)
    dotRV = 0.0; // Do not  show  highlight  on the  dark  side
vec3  shadedcolor = vec3(0.4,0.2,0.0)*vec3(0.4,0.2,0.0) + vec3(1.0,0.6,0.0)*vec3(1.0,0.6,0.0)*dotNL + vec3(1.0,1.0,0.8)*vec3(1.0,1.0,0.8)*pow(dotRV , 18.0);
finalcolor = vec4(shadedcolor , 1.0);
*/

   // And in its main () function , set the output color like this :
vec3  lightDirection = vec3 (0.0f, 0.0f, 1.0f);
float  shading = dot(interpolatedNormal , lightDirection);
shading = max(0.0,  shading); //  Clamp  negative  values  to 0.0
finalcolor = vec4(vec3(shading), 1.0);

}
