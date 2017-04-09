#version 330

//-- Location values
in layout(location=0) vec3 i_position;
in layout(location=1) vec2 i_texture;

out vec2 o_texture_coord;

void main(){
    o_texture_coord = i_texture;
	gl_Position = vec4(i_position, 1.0);
}