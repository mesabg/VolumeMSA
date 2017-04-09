#version 330
//-- Uniform values
uniform sampler2D u_actual_texture;
uniform sampler2D u_acum_texture;
uniform sampler1D u_transfer_function; 
uniform float u_interval;

//-- in values
in vec2 o_texture_coord;

//-- out values
out layout(location = 0) vec4 o_color;

void main(){
    float intensity = texture(u_actual_texture, o_texture_coord).x;
    vec4 actual_color = texture(u_transfer_function, intensity);
    vec4 acum_color = texture(u_acum_texture, o_texture_coord);

    if (actual_color.a > 0.0){
        actual_color.a = 1.0 - pow(1.0 - actual_color.a, u_interval*200.0f);
        acum_color.rgb += (1.0 - acum_color.a) * actual_color.rgb * actual_color.a;
        acum_color.a += (1.0 - acum_color.a) * actual_color.a;
    }
    if (acum_color.a > 1.0) acum_color.a = 1.0;
    o_color = acum_color;
}