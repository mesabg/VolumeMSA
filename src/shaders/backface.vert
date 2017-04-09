// for raycasting
#version 330

layout(location = 0) in vec3 VerPos;
layout(location = 1) in vec3 VerClr;

out vec3 Color;

uniform mat4 u_model_matrix;
uniform mat4 u_view_matrix;
uniform mat4 u_projection_matrix;

void main(){
    Color = VerClr;
    gl_Position = u_projection_matrix * u_view_matrix * u_model_matrix * vec4(VerPos, 1.0);
}
