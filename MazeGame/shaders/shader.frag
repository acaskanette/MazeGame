#version 330 core

in vec4 Color;
in vec2 UV;

uniform sampler2D Texture;

out vec4 fColor;

void main() {
	fColor = Color * texture(Texture, UV);
}