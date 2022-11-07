#ifndef MATRIX34_H
#define MATRIX34_H

#include <iostream>
#include <vector>

class Matrix34 {
    private:
        std::vector<double> content;

    public:
        static const int lineCount = 3;
        static const int columnCount = 4;

        Matrix34();
        Matrix34(const std::vector<double> &content);
        Matrix34(const Matrix34 &other);
        ~Matrix34();

        friend std::ostream &operator<<(std::ostream &out, const Matrix34 &matrix);
};

#endif
