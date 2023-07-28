#ifndef QUATERNION_H
#define QUATERNION_H

#include <iostream>
#include <vector>

#include "Vector3D.h"

/// <summary>
/// Quaternion class for rotations
/// </summary>
class Quaternion {
    private:
        float w_, x_, y_, z_;

    public:
        /// <summary>
        /// Default constructor
        /// </summary>
        /// <param name="w"></param>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <param name="z"></param>
        /// <param name="shouldNormalize">if true the quaternion will be normalize at it initialization</param>
        Quaternion(float w=1, float x=0, float y=0, float z=0, bool shouldNormalize=true);

        /// <summary>
        /// Constructor of Quaternion by putting euler angles as arguments
        /// </summary>
        /// <param name="orientation"></param>
        Quaternion(const Vector3D &orientation);

        void normalize();

        /// <summary>
        /// Rotate the quaternion by the vector (Rotation the quaternion around the vector)
        /// </summary>
        /// <param name="vector"></param>
        void rotateByVector(const Vector3D &vector);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="vector"></param>
        /// <param name="duration"></param>
        void updateByAngularVelocity(const Vector3D &vector, float duration);

        std::vector<float> getContentAsStdVector() const;

        void operator=(const Quaternion &other);
        Quaternion operator*=(const Quaternion &other);

        friend Quaternion operator*(const Quaternion &q1, const Quaternion &q2);
        friend std::ostream &operator<<(std::ostream &out, const Quaternion &quaternion);
};

#endif
