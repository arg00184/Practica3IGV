#include <stdio.h>
#include <math.h>

#include "igvPunto3D.h"

igvPunto3D::igvPunto3D(const double &x, const double &y, const double &z) : c{x, y, z} {
}

igvPunto3D::igvPunto3D(const igvPunto3D &p) : c{p.c[X], p.c[Y], p.c[Z]} {
}

igvPunto3D &igvPunto3D::operator=(const igvPunto3D &p) {
    c[X] = p.c[X];
    c[Y] = p.c[Y];
    c[Z] = p.c[Z];
    return *this;
}

bool igvPunto3D::operator==(const igvPunto3D &p) {
    return ((fabs(c[X] - p[X]) < IGV_EPSILON)
            && (fabs(c[Y] - p[Y]) < IGV_EPSILON)
            && (fabs(c[Z] - p[Z]) < IGV_EPSILON)
    );
}

bool igvPunto3D::operator!=(const igvPunto3D &p) {
    return ((fabs(c[X] - p[X]) >= IGV_EPSILON)
            || (fabs(c[Y] - p[Y]) >= IGV_EPSILON)
            || (fabs(c[Z] - p[Z]) >= IGV_EPSILON)
    );
}

void igvPunto3D::set(const double &x, const double &y, const double &z) {
    c[X] = x;
    c[Y] = y;
    c[Z] = z;
}

/**
 * Reserva un bloque de memoria con las coordenadas en formato flotante y en
 * coordenadas homogéneas (es decir, con cuarta coordenada = 1)
 * @return La dirección de memoria del bloque reservado
 * @note El bloque debe ser liberado con delete[] en algún momento en el código
 */
float *igvPunto3D::cloneToFloatArray() const {
    float *res = new float[4] { (float) c[0], (float) c[1], (float) c[2], 1.0f };
    return res;
}
