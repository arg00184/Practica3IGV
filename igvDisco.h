#ifndef __IGV_DISCO
#define __IGV_DISCO

#include "igvMallaTriangulos.h"

/**
 * Los objetos de esta clase representan discos en 3D (círculo relleno)
 */
class igvDisco : public igvMallaTriangulos
{
public:
    // Constructores y destructor
    igvDisco();
    igvDisco(float radio, int divisiones);
    ~igvDisco();
};

#endif   // __IGV_DISCO
