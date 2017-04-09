#version 330

//-- Location values
in layout(location=0) vec3 i_position;

void main(){
	gl_Position = vec4(i_position, 1.0);
}