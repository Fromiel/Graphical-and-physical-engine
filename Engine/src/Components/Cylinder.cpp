#include "Components/Cylinder.h"

Cylinder::Cylinder(unsigned int sectorCount) : sectorCount_(sectorCount)
{
    objectType_ = CylinderMesh;

    radius_ = 1;
    height_ = 1;
    sectorCount_ = sectorCount;

    // generate unit circle vertices first
    buildUnitCircleVertices();

    buildCylinder();
}


void Cylinder::buildCylinder()
{
    float x, y, z;                                  // vertex position
    float s, t;                                     // texCoord

    // get normals for cylinder sides
    std::vector<float> sideNormals = getSideNormals();

    // put vertices of side cylinder to array by scaling unit circle
    for (int i = 0; i <= 1; ++i)
    {
        z = -(height_ * 0.5f) + (float)i * height_;      // vertex position z
        float t = 1.0f - (float)i;   // top-to-bottom

        for (int j = 0, k = 0; j <= sectorCount_; ++j, k += 3)
        {
            x = unitCircleVertices_[k] * radius_;
            y = unitCircleVertices_[k + 1] * radius_;
            vertices_.push_back({x, y, z, sideNormals[k], sideNormals[k + 1], sideNormals[k + 2], (float)j / sectorCount_, t});

        }
    }

    // remember where the base.top vertices start
    unsigned int baseVertexIndex = (unsigned int)vertices_.size();

    // put vertices of base of cylinder
    z = -height_ * 0.5f;
    vertices_.push_back({0, 0, z, 0, 0, -1, 0.5f, 0.5f});
    for (int i = 0, j = 0; i < sectorCount_; ++i, j += 3)
    {
        x = unitCircleVertices_[j] * radius_;
        y = unitCircleVertices_[j + 1] * radius_;
        vertices_.push_back({ x, y, z, 0, 0, -1, -x * 0.5f + 0.5f, -y * 0.5f + 0.5f });
    }

    // remember where the base vertices start
    unsigned int topVertexIndex = (unsigned int)vertices_.size();

    // put vertices of top of cylinder
    z = height_ * 0.5f;
    vertices_.push_back({ 0, 0, z, 0, 0, 1, 0.5f, 0.5f });
    for (int i = 0, j = 0; i < sectorCount_; ++i, j += 3)
    {
        x = unitCircleVertices_[j] * radius_;
        y = unitCircleVertices_[j + 1] * radius_;
        vertices_.push_back({ x, y, z, 0, 0, 1, x * 0.5f + 0.5f, -y * 0.5f + 0.5f });
    }

    // put indices for sides
    unsigned int k1, k2;
    for (int i = 0; i < 1; ++i)
    {
        k1 = i * (sectorCount_ + 1);     // bebinning of current stack
        k2 = k1 + sectorCount_ + 1;      // beginning of next stack

        for (int j = 0; j < sectorCount_; ++j, ++k1, ++k2)
        {
            indices_.push_back(k1);
            indices_.push_back(k1 + 1);
            indices_.push_back(k2);

            indices_.push_back(k2);
            indices_.push_back(k1 + 1);
            indices_.push_back(k2 + 1);


        }
    }

    // remember where the base indices start
    unsigned int baseIndex = (unsigned int)indices_.size();

    // put indices for base
    for (int i = 0, k = baseVertexIndex + 1; i < sectorCount_; ++i, ++k)
    {
        if (i < (sectorCount_ - 1))
        {
            indices_.push_back(baseVertexIndex);
            indices_.push_back(k + 1);
            indices_.push_back(k);
        }
        else
        {
            indices_.push_back(baseVertexIndex);
            indices_.push_back(baseVertexIndex + 1);
            indices_.push_back(k);
        }// last triangle
    }

    // remember where the base indices start
    unsigned int topIndex = (unsigned int)indices_.size();

    for (int i = 0, k = topVertexIndex + 1; i < sectorCount_; ++i, ++k)
    {
        if (i < (sectorCount_ - 1))
        {
            indices_.push_back(topVertexIndex);
            indices_.push_back(k);
            indices_.push_back(k + 1);
        }
        else
        {
            indices_.push_back(topVertexIndex);
            indices_.push_back(k);
            indices_.push_back(topVertexIndex + 1);
        }
    }
}



void Cylinder::buildUnitCircleVertices()
{
    const float PI = acos(-1);
    float sectorStep = 2 * PI / sectorCount_;
    float sectorAngle;  // radian

    for (int i = 0; i <= sectorCount_; ++i)
    {
        sectorAngle = i * sectorStep;
        unitCircleVertices_.push_back(cos(sectorAngle)); // x
        unitCircleVertices_.push_back(sin(sectorAngle)); // y
        unitCircleVertices_.push_back(0);                // z
    }
}



std::vector<float> Cylinder::getSideNormals()
{
    const float PI = acos(-1);
    float sectorStep = 2 * PI / sectorCount_;
    float sectorAngle;  // radian

    // compute the normal vector at 0 degree first
    float x0 = 1;     // nx
    float y0 = 0;     // ny
    float z0 = 0;     // nz

    // rotate (x0,y0,z0) per sector angle
    std::vector<float> normals;
    for (int i = 0; i <= sectorCount_; ++i)
    {
        sectorAngle = i * sectorStep;
        normals.push_back(cos(sectorAngle) * x0 - sin(sectorAngle) * y0);   // nx
        normals.push_back(sin(sectorAngle) * x0 + cos(sectorAngle) * y0);   // ny
        normals.push_back(z0);  // nz

    }

    return normals;
}



std::vector<float> Cylinder::computeFaceNormal(float x1, float y1, float z1,  // v1
    float x2, float y2, float z2,  // v2
    float x3, float y3, float z3)  // v3
{
    const float EPSILON = 0.000001f;

    std::vector<float> normal(3, 0.0f);     // default return value (0,0,0)
    float nx, ny, nz;

    // find 2 edge vectors: v1-v2, v1-v3
    float ex1 = x2 - x1;
    float ey1 = y2 - y1;
    float ez1 = z2 - z1;
    float ex2 = x3 - x1;
    float ey2 = y3 - y1;
    float ez2 = z3 - z1;

    // cross product: e1 x e2
    nx = ey1 * ez2 - ez1 * ey2;
    ny = ez1 * ex2 - ex1 * ez2;
    nz = ex1 * ey2 - ey1 * ex2;

    // normalize only if the length is > 0
    float length = sqrtf(nx * nx + ny * ny + nz * nz);
    if (length > EPSILON)
    {
        // normalize
        float lengthInv = 1.0f / length;
        normal[0] = nx * lengthInv;
        normal[1] = ny * lengthInv;
        normal[2] = nz * lengthInv;
    }

    return normal;
}