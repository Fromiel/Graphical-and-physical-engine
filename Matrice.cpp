#include "matrix_full.h"
#include <cmath>


/* on écrit dans le tableau la matrice ligne par ligne*/
Matrix_Full::Matrix_Full(int nl, int nc) {
    if (nl <= 0)
        throw "nombre de lignes incorrect";
    if (nc <= 0)
        throw "nombre de colonnes incorrect";
    nl_ = nl;
    nc_ = nc;
    data_ = new double[nl * nc];
    for(int i = 0; i < nl * nc; i++) { /*on remplit la matrice par des 0*/
        data_[i] = 0;
    }
}


Matrix_Full::Matrix_Full(const Matrix_Full & m) : nl_(m.get_nl()), nc_(m.get_nc()){
    data_ = new double[nl_ * nc_];
    for(int i = 0; i < nl_; i++) { /*on copie dans la nouvelle matrice les valeurs de la matrice à copier*/
        for (int j = 0; j < nc_; j++) 
        {
            data_[i * nc_ + j] = m.data_[i * nc_ + j];
        }
    }
}

Matrix_Full::~Matrix_Full()
{
    delete[] data_;
}


Matrix_Full & Matrix_Full::operator=(const Matrix_Full m){
    if (&m != this) //si l'utilisateur fait m = m : on ne fait rien
    {
        Matrix_Full copie(m); //on copie m dans copie avec le constructeur de copie puis on échange les membres de copie avec ceux de l’objet courant
        double *tmp = data_;
        data_ = copie.data_;
        copie.data_ = tmp;

        nl_ = copie.get_nl();
        nc_ = copie.get_nc();
    }
    return *this; 
}


double Matrix_Full::operator()(int l, int c) const { //on récupère l'élément de la matrice d'indice (l,c)
    if (l < 0 || c < 0 || l >= nl_ || c >= nc_) {
        throw "indice incorrect";
    }
    return data_[l * nc_ + c];
}


double & Matrix_Full::operator()(int l, int c) { //on récupère l'élément de la matrice d'indice (l,c) pour pouvoir le modifier
    if (l < 0 || c < 0 || l >= nl_ || c >= nc_) {
        throw "indice incorrect";
    }
    return data_[l * nc_ + c];
}

Matrix_Full & Matrix_Full::operator+=(const Matrix_Full & m) {
    for (int i = 0; i < nl_; i++) {
        for (int j = 0; j < nc_; j++) {
            data_[i * nc_ + j] += m(i, j);
        }
    }
    return *this;
}


Matrix_Full & Matrix_Full::operator-=(const Matrix_Full & m) {
    for (int i = 0; i < nl_; i++) {
        for (int j = 0; j < nc_; j++) {
            data_[i * nc_ + j] -= m(i, j);
        }
    }
    return *this;
}

Matrix_Full Matrix_Full::transp() const {

    Matrix_Full transposee(nc_, nl_);
    for (int i = 0; i < nl_; i++) {
        for (int j = 0; j < nc_; j++) {
            transposee(j, i) = data_[i * nc_ + j];
        }
    }
    return transposee;
}


std::ostream & operator<<(std::ostream & out, const Matrix_Full & v) { //on affiche la matrice de la forme : | a b | (ici pour une matrice (2, 2))
    for (int i = 0; i < v.get_nl(); i ++) {                            //                                    | c d |
        out << "\n|";
        for (int j = 0; j < v.get_nc(); j++) {
            out << " "  << v(i, j) << " ";
        }
        out << "|";
    }
    return out;
}

Matrix_Full operator+(const Matrix_Full m1, const Matrix_Full m2) {
    int nl = m1.get_nl();
    int nc = m1.get_nc();

    if (nc != m2.get_nc() || nl != m2.get_nl())
        throw "matrices de tailles différentes";

    Matrix_Full add(m1);

    return add+=m2;
}




Matrix_Full operator-(const Matrix_Full m1, const Matrix_Full m2) {
    int nl = m1.get_nl();
    int nc = m1.get_nc();

    if (nc != m2.get_nc() && nl != m2.get_nl())
        throw "matrices de tailles différentes";

    Matrix_Full sub(m1);

    return sub-=m2;
}


Matrix_Full operator*(const Matrix_Full m1, const Matrix_Full m2) {
    int nc = m2.get_nc();
    int nl = m1.get_nl();
    int n = m1.get_nc();

    if (n != m2.get_nl())
        throw "matrices de tailles incorrectes";


    Matrix_Full mult(nl, nc);

    for (int i = 0; i < nl; i++) {
        for (int j = 0; j < nc; j++) {
            for (int k = 0; k < n; k++) {
                mult(i, j) += m1(i, k) * m2(k, j);
            }
        }
    }
    return mult;
}



Matrix_Full operator*(const Matrix_Full m, std::vector<double> & vect) { //on traite vect comme une matrice colonne
    int nc = m.get_nc();
    int nl = vect.size();
    if (nc != nl)
        throw "vecteur de taille incorrect";

    Matrix_Full mult(nl, 1);
    double s = 0;
    for (int k = 0; k < m.get_nl(); k++) {
        for (int i = 0; i < nl; i++) {
            s += m(k, i) * vect.at(i);   
        }
        mult(k, 0) = s;
        s = 0;
    }
    return mult;
}


Matrix_Full operator*(std::vector<double> & vect, const Matrix_Full m) { //on traite vect comme une matrice ligne
    int nl = m.get_nl();
    int nc = vect.size();
    if (nc != nl)
        throw "vecteur de taille incorrect";

    Matrix_Full mult(1, nc);
    double s = 0;
    for (int k = 0; k < m.get_nc(); k++) {
        for (int i = 0; i < nl; i++) {
            s += m(k, i) * vect.at(i);    
        }
        mult(0, k) = s;
        s = 0;
    }
    return mult;
}



Matrix_Full Matrix_Full::rotation_matrix_x(float theta)
{
    Matrix_Full r(4, 4);
    r(0, 0) = 1;
    r(0, 1) = 0;
    r(0, 2) = 0;
    r(1, 0) = 0;
    r(1, 1) = cos(theta);
    r(1, 2) = -sin(theta);
    r(2, 0) = 0;
    r(2, 1) = sin(theta);
    r(2, 2) = cos(theta);

    for(int k = 0; k < 3; k++) //on rajoute la 4e ligne et 4e colonne pour être en coordonnées homogènes
    {   
        r(k, 3) = 0;
        r(3, k) = 0;
    }
    r(3, 3) = 1;

    return r;
}

Matrix_Full Matrix_Full::rotation_matrix_y(float theta)
{
    Matrix_Full r(4, 4);
    r(0, 0) = cos(theta);
    r(0, 1) = 0;
    r(0, 2) = sin(theta);
    r(1, 0) = 0;
    r(1, 1) = 1;
    r(1, 2) = 0;
    r(2, 0) = -sin(theta);
    r(2, 1) = 0;
    r(2, 2) = cos(theta);

    for(int k = 0; k < 3; k++) //on rajoute la 4e ligne et 4e colonne pour être en coordonnées homogènes
    {   
        r(k, 3) = 0;
        r(3, k) = 0;
    }
    r(3, 3) = 1;

    return r;
}

Matrix_Full Matrix_Full::rotation_matrix_z(float theta)
{
    Matrix_Full r(4, 4);
    r(0, 0) = cos(theta);
    r(0, 1) = -sin(theta);
    r(0, 2) = 0;
    r(1, 0) = sin(theta);
    r(1, 1) = cos(theta);
    r(1, 2) = 0;
    r(2, 0) = 0;
    r(2, 1) = 0;
    r(2, 2) = 1;

    for(int k = 0; k < 3; k++) //on rajoute la 4e ligne et 4e colonne pour être en coordonnées homogènes
    {   
        r(k, 3) = 0;
        r(3, k) = 0;
    }
    r(3, 3) = 1;


    return r;
}

Matrix_Full Matrix_Full::get_translation_matrix(float x, float y, float z)
{
    Matrix_Full t(4, 4);

    for(int i = 0; i < 4; i++)
    {   
        for(int j = 0; j < 3; j++)
        {
            if (i == j)
                t(i, j) = 1;
            else
                t(i, j) = 0;
        }
    }
    t(3, 3) = 1;
    t(0, 3) = -x;
    t(1, 3) = -y;
    t(2, 3) = -z;

    return t;
}

Matrix_Full Matrix_Full::identity(int i)
{
    Matrix_Full id(i, i);
    for (int j = 0; j < i; j++)
    {
        for (int k = 0; k < i; k++)
        {
            if (j == k)
                id(j, k) = 1;
            else    
                id(j, k) = 0;
        }
    }
    return id;
}

const Matrix_Full Matrix_Full::id4 = Matrix_Full::identity(4);