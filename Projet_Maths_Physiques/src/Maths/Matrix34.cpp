#include "Maths/Matrix34.h"

std::ostream &operator<<(std::ostream &out, const Matrix34 &matrix) {
    for (int i=0; i<matrix.content.size()-1; ++i) out << matrix.content[i] << ", ";
    out << matrix.content[matrix.content.size()-1];
    return out;
}