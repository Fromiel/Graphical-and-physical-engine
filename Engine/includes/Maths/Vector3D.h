#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>

/// <summary>
/// Vector with 3 dimensions
/// </summary>
class Vector3D{

    private :
        float x_;
        float y_;
        float z_;

    public:
        /// <summary>
        /// Constructor returning by default the null vector
        /// </summary>
        Vector3D(float x=0, float y=0, float z=0);

        float get_x() const {return x_;}
        float get_y() const {return y_;}
        float get_z() const {return z_;}

        /// <summary>
        /// Maximum value of the vector
        /// </summary>
        /// <returns></returns>
        float maxValue() const;

        /// <summary>
        /// Norm of the vector
        /// </summary>
        /// <returns></returns>
        float norm() const;

        /// <summary>
        /// Norm of the vector squared
        /// </summary>
        /// <returns></returns>
        float norm_squared() const;

        /// <summary>
        /// Normalise the vector
        /// </summary>
        /// <returns> Return the normalize vector </returns>
        Vector3D normalized();

        Vector3D operator*=(const float &scalar);

        static float distance(const Vector3D& vect1, const Vector3D& vect2);
        static float scalar_product(const Vector3D& vect1, const Vector3D& vect2);
        static Vector3D vectorial_product(const Vector3D& vect1, const Vector3D& vect2);

        friend std::ostream& operator<<(std::ostream& out, const Vector3D& vect);
        friend Vector3D operator+(const Vector3D& vect1, const Vector3D& vect2);
        friend Vector3D operator-(const Vector3D& vect1, const Vector3D& vect2);
        friend Vector3D operator*(const Vector3D& vect1, const Vector3D& vect2);
        friend Vector3D operator*(const float d, const Vector3D& v);
        friend Vector3D operator*(const Vector3D& v, const float d);
        friend bool operator==(const Vector3D& v1, const Vector3D& v2);

};



#endif //VECTOR3D_H
