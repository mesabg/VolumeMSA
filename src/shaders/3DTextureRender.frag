#version 330
//-- Uniform values
uniform sampler3D u_texture_sampler;

//-- in values
in vec3 o_texture_coord;

//-- out values
out vec4 o_color;

void main(){
    o_color = texture(u_texture_sampler, o_texture_coord);
}