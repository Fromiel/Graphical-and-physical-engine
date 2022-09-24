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
    float valueC = -dot(normalize(n), normalize(d));
    float valueR = max(dot(normalize(r), normalize(v)), 0.0f);

    vec3 reflet = specObjet * specLumiere * pow(valueR, 10);
    vec3 couleur = coulObjet * coulLumiere * valueC;

    gl_FragColor = vec4(couleur + reflet, 1.0);
};