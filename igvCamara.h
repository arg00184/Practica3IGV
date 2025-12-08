#ifndef __IGVCAMARA
#define __IGVCAMARA

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glut.h>

#endif   // defined(__APPLE__) && defined(__MACH__)

#include "igvPunto3D.h"

enum tipoCamara {
    IGV_PARALELA, IGV_FRUSTUM, IGV_PERSPECTIVA
};

class igvCamara {
private:
    tipoCamara tipo = IGV_PARALELA;

    GLdouble xwmin = -3
            , xwmax = 3
            , ywmin = -3
            , ywmax = 3;
    GLdouble angulo = 60
            , raspecto = 1;

    GLdouble znear = 1
            , zfar = 200;

    igvPunto3D P0 = {3, 2, 4};

    igvPunto3D r = {0, 0, 0};

    igvPunto3D V = {0, 1, 0};
    bool modoMovimientoCamara = false;
    int vistaActual = 0;

public:
    igvCamara() = default;

    ~igvCamara() = default;

    igvCamara(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V);

    void set(igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V);

    void set(tipoCamara _tipo);

    void set(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V
             , double _xwmin, double _xwmax, double _ywmin
             , double _ywmax, double _znear, double _zfar);

    void set(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V
             , double _angulo, double _raspecto, double _znear, double _zfar);

    void aplicar(void);

    void zoom(double factor);

    void activarMovimiento();

    void desactivarMovimiento();

    bool getMovimientoActivo() const;

    tipoCamara getTipo() const;

    void orbita(double incremento);

    void cabeceo(double incremento);

    void rotacionEjeY(double incremento);

    void desplazarAdelante(double incremento);

    void aplicarViewport(int viewport_id, int ancho_ventana, int alto_ventana);

    void moverPlanoDelantero(double incremento);

    void moverPlanoTrasero(double incremento);

    void setAspecto(double aspecto);

    void siguienteVista();

    void aplicarVistaActual();
};

#endif   // __IGVCAMARA