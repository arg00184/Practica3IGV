#ifndef __IGVTEXTURA
#define __IGVTEXTURA

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glut.h>

#endif   // defined(__APPLE__) && defined(__MACH__)

#include <string>

/**
 * Los objetos de esta clase representan texturas OpenGL
 */
class igvTextura {
private:
    unsigned int idTextura = 0;
    unsigned int alto = 0, ancho = 0;

    GLenum filtroMag = GL_LINEAR;
    GLenum filtroMin = GL_LINEAR;

public:
    igvTextura () = default;
    igvTextura ( std::string fichero );
    ~igvTextura ();

    void aplicar ();
    void desactivar();

    void setIdTextura ( unsigned int id );
    unsigned int getIdTextura ();

    void setFiltroMag(GLenum filtro);
    void setFiltroMin(GLenum filtro);

    static igvTextura* crearTableroAjedrez(int tamano, int numCuadros);
};

#endif   // __IGVTEXTURA

