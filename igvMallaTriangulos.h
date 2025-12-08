#ifndef __IGVMALLATRIANGULOS
#define __IGVMALLATRIANGULOS

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glut.h>

#endif   // defined(__APPLE__) && defined(__MACH__)

#include <string>
#include <vector>

class igvMallaTriangulos {
protected:
    long int num_vertices = 0;
    float *vertices = nullptr;
    float *normales = nullptr;

    long int num_triangulos = 0;
    unsigned int *triangulos = nullptr;
    bool usarnormales = true;
    bool gouraud = true;
    bool normales_calculadas = false;
    void calcularNormalesVertices();

public:
    igvMallaTriangulos() = default;

    igvMallaTriangulos(long int _num_vertices, float *_vertices
                       , long int _num_triangulos, unsigned int *_triangulos);

    explicit igvMallaTriangulos(const std::string &rutaOBJ);

    ~igvMallaTriangulos();

    bool cargarOBJ(const std::string &rutaOBJ);

    void visualizar();

    void cambiarnormales() { usarnormales = !usarnormales; }
    void cambiarvis() { gouraud = !gouraud; }
};

#endif   // __IGVMALLATRIANGULOS
