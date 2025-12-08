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
