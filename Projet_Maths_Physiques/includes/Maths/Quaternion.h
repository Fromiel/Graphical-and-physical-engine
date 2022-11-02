#ifndef QUATERNION_H
#define QUATERNION_H

class Quaternion {
    private:
        float a, b, c, d;

    public:
        Quaternion(float a, float b, float c, float d);
        ~Quaternion();
};

#endif
