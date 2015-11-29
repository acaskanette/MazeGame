#version 330 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec4 vColor;
layout(location = 2) in vec2 vUV;
layout(location = 3) in vec3 vNormal;

uniform mat4 TransformMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 CameraViewMatrix;

out vec4 Color;
out vec2 UV;

void main() {
	Color = vColor;
	UV = vec2(vUV.x, 1.0 - vUV.y); // Flip the UV because OpenGL does textures upside down
	gl_Position = ProjectionMatrix * CameraViewMatrix * TransformMatrix * vec4(vPosition, 1.0);
}