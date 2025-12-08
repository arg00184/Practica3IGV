#ifndef __IGV_ESFERA
#define __IGV_ESFERA

#include "igvMallaTriangulos.h"

/**
 * Los objetos de esta clase representan esferas en 3D
 */
class igvEsfera : public igvMallaTriangulos
{
public:
    // Constructores y destructor
    igvEsfera();
    igvEsfera(float radio, int meridianos, int paralelos);
    ~igvEsfera();
};

#endif   // __IGV_ESFERA
