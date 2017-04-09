#version 330
//-- Uniform values
uniform sampler2D u_texture_sampler;
uniform sampler1D u_transfer_function;

//-- in values
in vec2 o_texture_coord;

//-- out values
out vec4 o_color;

void main(){
    float intensity = texture(u_texture_sampler, o_texture_coord).a;
    vec4 actual_color = texture(u_transfer_function, intensity);
    o_color.rgb = actual_color.rgb;
    o_color.a = actual_color.a;
    //o_color.a = texture(u_acum_texture, o_texture_coord).a;
    //texture(u_transfer_function, intensity).a;
}