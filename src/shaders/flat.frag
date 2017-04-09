#version 330
//-- Uniform values
uniform sampler2D texture_sampler;

//-- in values
in vec2 o_texture_coord;

//-- out values
out vec4 o_color;

void main(){
    o_color = texture(texture_sampler, o_texture_coord);
}