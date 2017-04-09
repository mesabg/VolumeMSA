#version 330


layout (location = 0) in vec3 VerPos;
// have to use this variable!!!, or it will be very hard to debug for AMD video card
layout (location = 1) in vec3 VerClr;  


out vec3 EntryPoint;
out vec4 ExitPointCoord;

uniform mat4 u_model_matrix;
uniform mat4 u_view_matrix;
uniform mat4 u_projection_matrix;

void main(){
    EntryPoint = VerClr;
    gl_Position =  u_projection_matrix * u_view_matrix * u_model_matrix * vec4(VerPos,1.0);
    ExitPointCoord = gl_Position;
}
