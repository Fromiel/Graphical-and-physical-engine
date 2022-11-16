#ifndef QUATERNION_H
#define QUATERNION_H

#include <iostream>
#include <cmath>
#include <vector>

#include "Vecteur3D.h"

class Quaternion {
    private:
        float w, x, y, z;

    public:
        Quaternion(float w=1, float x=0, float y=0, float z=0, bool shouldNormalize=true);
        Quaternion(const Quaternion &other);
        ~Quaternion();

        void normalize();

        void rotateByVector(const Vecteur3D &vector);
        void updateByAngularVelocity(const Vecteur3D &vector, float duration);

        std::vector<float> getContentAsStdVector() const;

        void operator=(const Quaternion &other);
        void operator*=(const Quaternion &other);

        friend Quaternion operator*(const Quaternion &q1, const Quaternion &q2);
        friend std::ostream &operator<<(std::ostream &out, const Quaternion &quaternion);
};

#endif
