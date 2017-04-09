#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texture_coord; 

out vec2 textureCoord;

void main(){
    textureCoord = texture_coord;
    gl_Position = vec4(position.xy, 0, 1);
}