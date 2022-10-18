
# version 330 core
uniform  float  time;
uniform mat4 MV;
uniform mat4 D;
uniform mat4 P;


layout(location =0) in vec3  Position;
layout(location =1) in vec3  Normal;
layout(location =2) in vec2  TexCoord;

out  vec3 interpolatedNormal;
out  vec2 st;
out vec3 transformedLight;

void main () {
transformedLight = mat3(D) * vec3(0.0, 1.0, 0.0);
//gl_Position = scalemat*D* vec4(Position ,1);
//gl_Position = vec4 ( Position , sin(time)+2) ;
// And somewhere in its main () function , add this :
vec3  transformedNormal =  Normal;
interpolatedNormal = normalize(transformedNormal);
transformedLight= normalize(transformedLight);


//interpolatedColor = Color ; // Pass interpolated color to fragment shader
gl_Position = P*MV*D*vec4(Position , 1.0f); // Special , required  output


st = TexCoord; // Will  also be  interpolated  across  the  triangle
}
