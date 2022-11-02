#version 330 core
uniform vec3 coulLumiere;

void main()
{
    gl_FragColor = vec4(coulLumiere ,0.5); // set alle 4 vector values to 1.0
}