#version 330

in vec2 textureCoord;

uniform sampler2D alpha_selector_texture;

out vec4 finalColor;

void main(){
    finalColor = texture(alpha_selector_texture, textureCoord);
}