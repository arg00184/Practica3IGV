#ifndef __IGVPUNTO3D
#define __IGVPUNTO3D

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glut.h>

#endif   // defined(__APPLE__) && defined(__MACH__)


#define IGV_EPSILON 0.000001

#ifndef __ENUM_XYZ
#define __ENUM_XYZ

enum Coordenadas {
    X, Y, Z
};
#endif   // __ENUM_XYZ

class igvPunto3D {
private:
    double c[3] = {0, 0, 0};

public:
    igvPunto3D() = default;

    igvPunto3D(const double &x, const double &y, const double &z);

    igvPunto3D(const igvPunto3D &p);

    igvPunto3D &operator=(const igvPunto3D &p);

    ~igvPunto3D() = default;

    double &operator[](const unsigned char idx);

    double operator[](const unsigned char idx) const;

    bool operator==(const igvPunto3D &p);

    bool operator!=(const igvPunto3D &p);

    void set(const double &x, const double &y, const double &z);

    float *cloneToFloatArray() const; // Devuelve el punto en un array de float


};

inline double &igvPunto3D::operator[](const unsigned char idx) {
    return c[idx];
}

inline double igvPunto3D::operator[](const unsigned char idx) const {
    return c[idx];
}

#endif   // __IGVPUNTO3D
