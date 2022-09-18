#include "Sphere.h"


Sphere::Sphere(float radius, Vecteur3D center, unsigned int sectorCount, unsigned int stackCount) : radius_(radius), center_(center), sectorCount_(sectorCount), stackCount_(stackCount)
{
    float x, y, z, xy;                              // vertex position
    float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
    float s, t;                                     // vertex texCoord

    float sectorStep = 2 * M_PI / sectorCount_;
    float stackStep = M_PI / stackCount_;
    float sectorAngle, stackAngle;

    for (int i = 0; i <= stackCount_; ++i)
    {
        stackAngle = M_PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
        xy = radius_ * cosf(stackAngle);             // r * cos(u)
        z = radius_ * sinf(stackAngle);              // r * sin(u)

        // add (sectorCount+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coords
        for (int j = 0; j <= sectorCount_; ++j)
        {
            sectorAngle = j * sectorStep;           // starting from 0 to 2pi

            // vertex position (x, y, z)
            x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
            y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)

            // normalized vertex normal (nx, ny, nz)
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;
            vertices_.push_back({x, y, z, 0.5f, 0.5f, 0.5f, nx, ny, nz});

            /*
            // vertex tex coord (s, t) range between [0, 1]
            s = (float)j / sectorCount;
            t = (float)i / stackCount;
            texCoords.push_back(s);
            texCoords.push_back(t);
            */
        }
    }

    int k1, k2;
    for (int i = 0; i < stackCount_; ++i)
    {
        k1 = i * (sectorCount_ + 1);     // beginning of current stack
        k2 = k1 + sectorCount_ + 1;      // beginning of next stack

        for (int j = 0; j < sectorCount_; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding first and last stacks
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