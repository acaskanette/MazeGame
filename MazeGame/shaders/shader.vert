#version 330 core
layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vUV;

out vec3 fPosition;
out vec3 fNormal;
out vec2 fUV;

uniform mat4 transformMatrix;
uniform mat4 projectionMatrix;
uniform mat4 cameraViewMatrix;

void main() {
    gl_Position = projectionMatrix * cameraViewMatrix * transformMatrix * vec4(vPosition, 1.0f);
    fPosition = vec3(transformMatrix * vec4(vPosition, 1.0f));
    fNormal = mat3(transpose(inverse(transformMatrix))) * vNormal;
    fUV = vUV;
}