#version 330 core
uniform vec3 coulLumiere;
uniform vec3 coulObjet;
uniform vec3 specLumiere;
uniform vec3 specObjet;
uniform float alpha;

in vec3 d;
in vec3 n;
in vec3 r;
in vec3 v;

void main()
{
    float valueC = dot(normalize(n), normalize(d));
    float valueR = dot(normalize(r), normalize(d));

    vec3 reflet = specObjet * specLumiere * pow(valueR, alpha);
    vec3 couleur = coulObjet * coulLumiere * valueC;

    gl_FragColor = vec4(couleur + reflet, 1.0);
};