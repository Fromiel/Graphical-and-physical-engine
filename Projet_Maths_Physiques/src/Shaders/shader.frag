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
     float ambientStrength = 0.1;
     vec3 ambient = ambientStrength * coulLumiere;

     float valueC = max(dot(normalize(n), normalize(d)), 0);
     float valueR = max(dot(normalize(r), normalize(v)), 0.0f);

     vec3 reflet = 0.5 * coulLumiere * pow(valueR, 32);
     vec3 couleur = coulLumiere * valueC;

     gl_FragColor = vec4(ambient + couleur + reflet /*+ vec3(0.1, 0.25, 0.05)*/, 1.0);
   
};