#version 330 core
uniform vec3 posLumiere;
uniform vec3 posCamera;
uniform mat4 MVP;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;

attribute vec3 normal;
attribute vec3 vPos;
attribute vec3 vCol;

out vec3 d;
out vec3 n;
out vec3 r;
out vec3 v;

void main()
{
    vec4 pos = modelMatrix * vec4(vPos, 1.0);
    gl_Position = MVP * vec4(vPos, 1.0);
    d = posLumiere - pos.xyz / pos.w;
    n = normalMatrix * normal;
    v = posCamera - pos.xyz / pos.w;
    r = reflect(-d, n);
};