#include "igvEsfera.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

igvEsfera::igvEsfera() : igvMallaTriangulos()
{
}

igvEsfera::igvEsfera(float radio, int meridianos, int paralelos)
{
    if (meridianos < 3) meridianos = 3;
    if (paralelos < 2) paralelos = 2;

    num_vertices = 2 + meridianos * (paralelos - 1);
    vertices = new float[num_vertices * 3];
    normales = new float[num_vertices * 3];
    
    int idx = 0;
    vertices[idx * 3 + 0] = 0.0f;
    vertices[idx * 3 + 1] = radio;
    vertices[idx * 3 + 2] = 0.0f;
    idx++;
    for (int j = 1; j < paralelos; ++j)
    {
        float phi = (j / (float)paralelos) * (float)M_PI;
        float y = radio * std::cos(phi);
        float r_anillo = radio * std::sin(phi);
        for (int i = 0; i < meridianos; ++i)
        {
            float theta = (i / (float)meridianos) * 2.0f * (float)M_PI;
            float x = r_anillo * std::cos(theta);
            float z = r_anillo * std::sin(theta);
            vertices[idx * 3 + 0] = x;
            vertices[idx * 3 + 1] = y;
            vertices[idx * 3 + 2] = z;
            
            idx++;
        }
    }

    vertices[idx * 3 + 0] = 0.0f;
    vertices[idx * 3 + 1] = -radio;
    vertices[idx * 3 + 2] = 0.0f;
    num_triangulos = meridianos + meridianos * (paralelos - 2) * 2 + meridianos;
    triangulos = new unsigned int[num_triangulos * 3];
    
    int t = 0;

    for (int i = 0; i < meridianos; ++i)
    {
        triangulos[t++] = 0;
        triangulos[t++] = 1 + i;
        triangulos[t++] = 1 + ((i + 1) % meridianos);
    }

    for (int j = 0; j < paralelos - 2; ++j)
    {
        for (int i = 0; i < meridianos; ++i)
        {
            unsigned int i0 = 1 + j * meridianos + i;
            unsigned int i1 = 1 + j * meridianos + ((i + 1) % meridianos);
            unsigned int i2 = 1 + (j + 1) * meridianos + ((i + 1) % meridianos);
            unsigned int i3 = 1 + (j + 1) * meridianos + i;
            triangulos[t++] = i0;
            triangulos[t++] = i1;
            triangulos[t++] = i3;
            triangulos[t++] = i1;
            triangulos[t++] = i2;
            triangulos[t++] = i3;
        }
    }

    unsigned int polo_sur = num_vertices - 1;
    unsigned int primera_fila_sur = 1 + (paralelos - 2) * meridianos;
    
    for (int i = 0; i < meridianos; ++i)
    {
        triangulos[t++] = primera_fila_sur + i;
        triangulos[t++] = polo_sur;
        triangulos[t++] = primera_fila_sur + ((i + 1) % meridianos);
    }
    calcularNormalesVertices();
}

igvEsfera::~igvEsfera()
{
}
