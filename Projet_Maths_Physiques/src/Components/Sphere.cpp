#include "Components/Sphere.h"


Sphere::Sphere(float radius, unsigned int sectorCount, unsigned int stackCount): radius_(radius), sectorCount_(sectorCount), stackCount_(stackCount)
{
    float x, y, z, xy;                              // vertex position
    float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normale
    float s, t;                                     // vertex texCoord

    float sectorStep = 2 * M_PI / sectorCount_;
    float stackStep = M_PI / stackCount_;
    float sectorAngle, stackAngle;

    for (int i = 0; i <= stackCount_; ++i)
    {
        stackAngle = M_PI / 2 - i * stackStep;        // commence de pi/2 à -pi/2
        xy = radius_ * cosf(stackAngle);             // r * cos(u)
        z = radius_ * sinf(stackAngle);              // r * sin(u)

        // ajoute (sectorCount+1) vertices par latitude
        //les premier et dernier vertices ont la meme position et normale, mais des différentes coordonnées de texture
        for (int j = 0; j <= sectorCount_; ++j)
        {
            sectorAngle = j * sectorStep;           // on commence de 0 à 2pi

            // vertex position (x, y, z)
            x = xy * cosf(sectorAngle);           // r * cos(u) * cos(v)
            y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)

            // normale au vertex normalisée (nx, ny, nz)
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;

            // coordonnée de texture du vertex (s, t) entre [0, 1]
            s = (float)j / sectorCount;
            t = (float)i / stackCount;


            vertices_.push_back({x, y, z, 0.5f, 0.5f, 0.5f, nx, ny, nz, s, t});

       
            
        }
    }

    int k1, k2;
    for (int i = 0; i < stackCount_; ++i)
    {
        k1 = i * (sectorCount_ + 1);     // début de la latitude actuelle
        k2 = k1 + sectorCount_ + 1;      // début de la latitude suivante

        for (int j = 0; j < sectorCount_; ++j, ++k1, ++k2)
        {
            // 2 triangles par longitude en excluant la première et dernière latitude
            // k1 => k2 => k1+1
            if (i != 0)
            {
                indices_.push_back(k1);
                indices_.push_back(k2);
                indices_.push_back(k1 + 1);
            }

            // k1+1 => k2 => k2+1
            if (i != (stackCount - 1))
            {
                indices_.push_back(k1 + 1);
                indices_.push_back(k2);
                indices_.push_back(k2 + 1);
            }
        }
    }
}