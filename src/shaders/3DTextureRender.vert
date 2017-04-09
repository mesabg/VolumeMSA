#version 330

//-- Location values
in layout(location=0) vec3 i_position;
in layout(location=1) vec3 i_texture;

//-- Uniform values
uniform mat4 u_view_matrix;
uniform mat4 u_projection_matrix;
uniform mat4 u_model_matrix;

//-- Out values
out vec3 o_texture_coord;

void main(){
    vec4 worldPosition = u_model_matrix * vec4(i_position, 1.0);
    o_texture_coord = i_texture;

    //-- Final vertex position
	gl_Position = u_projection_matrix * u_view_matrix * worldPosition;
}