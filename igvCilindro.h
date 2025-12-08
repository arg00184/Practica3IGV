#ifndef __IGV_CILINDRO
#define __IGV_CILINDRO

#include "igvMallaTriangulos.h"

class igvCilindro : public igvMallaTriangulos {
public:
    igvCilindro();

    igvCilindro(float r, float a, int divU, int divV);

    ~igvCilindro();
};

#endif   // __IGV_CILINDRO
