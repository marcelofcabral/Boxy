#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

uniform mat4 uModelViewMatrix;
uniform mat4 uProjectionMatrix;

out vec4 outColor;

void main()
{
    gl_Position = uProjectionMatrix * uModelViewMatrix * vec4(aPos, 1.0);
    outColor = aColor;
}