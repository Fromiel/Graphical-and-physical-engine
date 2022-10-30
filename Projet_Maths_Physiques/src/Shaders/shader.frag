#version 330 core
uniform vec3 coulLumiere;
uniform vec3 coulObjet;
uniform vec3 specLumiere;
uniform vec3 specObjet;
uniform float alpha;
uniform vec3 diffuse;

in vec3 d;
in vec3 n;
in vec3 r;
in vec3 v;

void main()
{
    // ambient
    vec3 ambient = coulLumiere * coulObjet;
  	
    // diffuse 
    vec3 norm = normalize(n);
    vec3 lightDir = normalize(d);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = coulLumiere * (diff * diffuse);
    
    // specular
    vec3 viewDir = normalize(normalize(v));
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), alpha);
    vec3 specular = coulLumiere * (spec * specObjet);  
        
    vec3 result = ambient + diffuse + specular;
    gl_FragColor = vec4(result, 1.0);
   
};