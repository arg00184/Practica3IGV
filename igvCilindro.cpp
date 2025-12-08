#include "igvCilindro.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

igvCilindro::igvCilindro() : igvMallaTriangulos() {
}

igvCilindro::igvCilindro(float r, float a, int divU, int divV) {
    if (divU < 3) divU = 3;
    if (divV < 1) divV = 1;

    num_vertices = divU * (divV + 1);
    vertices = new float[num_vertices * 3];

    num_triangulos = divU * divV * 2;
    triangulos = new unsigned int[num_triangulos * 3];

    // -------- Anillo base
    for (int i = 0; i < divU; ++i) {
        float angle = (i / (float) divU) * 2.0f * (float) M_PI;
        float cx = std::cos(angle);
        float sx = std::sin(angle);

        vertices[i * 3 + 0] = r * cx;
        vertices[i * 3 + 1] = 0.0f;
        vertices[i * 3 + 2] = r * sx;

    }

    for (int j = 0; j < divV; ++j) {
        float y = (j + 1) * (a / (float) divV);

        for (int i = 0; i < divU; ++i) {
            int base0 = i * 3;
            int baseJ = ((j + 1) * divU + i) * 3;
            vertices[baseJ + 0] = vertices[base0 + 0];
            vertices[baseJ + 1] = y;
            vertices[baseJ + 2] = vertices[base0 + 2];
        }
    }

    int t = 0;
    for (int j = 0; j < divV; ++j) {
        for (int i = 0; i < divU; ++i) {
            unsigned int i0 = j * divU + i;
            unsigned int i1 = j * divU + ((i + 1) % divU);
            unsigned int i2 = (j + 1) * divU + ((i + 1) % divU);
            unsigned int i3 = (j + 1) * divU + i;

            triangulos[t++] = i0;
            triangulos[t++] = i1;
            triangulos[t++] = i3;
            triangulos[t++] = i1;
            triangulos[t++] = i2;
            triangulos[t++] = i3;
        }
    }
    calcularNormalesVertices();
}

igvCilindro::~igvCilindro() {
}

