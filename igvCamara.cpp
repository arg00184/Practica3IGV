#include <math.h>

#include "igvCamara.h"


igvCamara::igvCamara(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r
                     , igvPunto3D _V) : P0(_P0), r(_r), V(_V)
                                        , tipo(_tipo) {
}

void igvCamara::set(igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V) {
    P0 = _P0;
    r = _r;
    V = _V;
}

void igvCamara::set(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r
                    , igvPunto3D _V, double _xwmin, double _xwmax, double _ywmin
                    , double _ywmax, double _znear, double _zfar) {
    tipo = _tipo;

    P0 = _P0;
    r = _r;
    V = _V;

    xwmin = _xwmin;
    xwmax = _xwmax;
    ywmin = _ywmin;
    ywmax = _ywmax;
    znear = _znear;
    zfar = _zfar;
}

void igvCamara::set(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r
                    , igvPunto3D _V, double _angulo, double _raspecto
                    , double _znear, double _zfar) {
    tipo = _tipo;

    P0 = _P0;
    r = _r;
    V = _V;

    angulo = _angulo;
    raspecto = _raspecto;
    znear = _znear;
    zfar = _zfar;
}

void igvCamara::set(tipoCamara _tipo) {
    tipo = _tipo;
}


void igvCamara::aplicar() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (tipo == IGV_PARALELA) {
        glOrtho(xwmin, xwmax, ywmin, ywmax, znear, zfar);
    }
    if (tipo == IGV_FRUSTUM) {
        glFrustum(xwmin, xwmax, ywmin, ywmax, znear, zfar);
    }
    if (tipo == IGV_PERSPECTIVA) {
        gluPerspective(angulo, raspecto, znear, zfar);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(P0[X], P0[Y], P0[Z], r[X], r[Y], r[Z], V[X], V[Y], V[Z]);
}

void igvCamara::zoom(double factor) {
    if (tipo == IGV_PARALELA || tipo == IGV_FRUSTUM) {
        double factor_escala = 1.0 - (factor / 100.0);
        xwmin *= factor_escala;
        xwmax *= factor_escala;
        ywmin *= factor_escala;
        ywmax *= factor_escala;
    } else if (tipo == IGV_PERSPECTIVA) {
    double factor_escala = 1.0 - (factor / 100.0);
    angulo *= factor_escala;
    if (angulo < 10.0) angulo = 10.0;
    if (angulo > 120.0) angulo = 120.0;
    }
}

void igvCamara::activarMovimiento() {
    modoMovimientoCamara = !modoMovimientoCamara;
}

void igvCamara::desactivarMovimiento() {
    modoMovimientoCamara = false;
}

bool igvCamara::getMovimientoActivo() const {
    return modoMovimientoCamara;
}

tipoCamara igvCamara::getTipo() const {
    return tipo;
}

void igvCamara::moverPlanoDelantero(double incremento) {
    znear += incremento;
    if (znear < 0.1) {
        znear = 0.1;
    }
    if (znear >= zfar - 0.5) {
        znear = zfar - 0.5;
    }
}

void igvCamara::moverPlanoTrasero(double incremento) {
    zfar += incremento;
    if (zfar <= znear + 0.5) {
        zfar = znear + 0.5;
    }
    if (zfar < 1.0) {
        zfar = 1.0;
    }
}

void igvCamara::setAspecto(double aspecto) {
    if (aspecto <= 0.0) return;
    raspecto = aspecto;
}

void igvCamara::orbita(double incremento) {
    double dx = P0[X] - r[X];
    double dz = P0[Z] - r[Z];

    double angulo_rad = incremento * M_PI / 180.0;

    double nuevo_dx = dx * cos(angulo_rad) - dz * sin(angulo_rad);
    double nuevo_dz = dx * sin(angulo_rad) + dz * cos(angulo_rad);

    P0[X] = r[X] + nuevo_dx;
    P0[Z] = r[Z] + nuevo_dz;
}

void igvCamara::cabeceo(double incremento) {
    double dx = P0[X] - r[X];
    double dy = P0[Y] - r[Y];
    double dz = P0[Z] - r[Z];

    double dist_xz = sqrt(dx * dx + dz * dz);

    double angulo_rad = incremento * M_PI / 180.0;

    double nuevo_dy = dy * cos(angulo_rad) - dist_xz * sin(angulo_rad);
    double nueva_dist_xz = dy * sin(angulo_rad) + dist_xz * cos(angulo_rad);

    double factor = nueva_dist_xz / dist_xz;

    P0[X] = r[X] + dx * factor;
    P0[Y] = r[Y] + nuevo_dy;
    P0[Z] = r[Z] + dz * factor;
}

void igvCamara::rotacionEjeY(double incremento) {
    double vx = r[X] - P0[X];
    double vz = r[Z] - P0[Z];

    double angulo_rad = incremento * M_PI / 180.0;

    double nuevo_vx = vx * cos(angulo_rad) - vz * sin(angulo_rad);
    double nuevo_vz = vx * sin(angulo_rad) + vz * cos(angulo_rad);

    r[X] = P0[X] + nuevo_vx;
    r[Z] = P0[Z] + nuevo_vz;
}

void igvCamara::desplazarAdelante(double incremento) {
    double vx = r[X] - P0[X];
    double vy = r[Y] - P0[Y];
    double vz = r[Z] - P0[Z];

    double longitud = sqrt(vx * vx + vy * vy + vz * vz);

    vx /= longitud;
    vy /= longitud;
    vz /= longitud;

    P0[X] += vx * incremento;
    P0[Y] += vy * incremento;
    P0[Z] += vz * incremento;
}

void igvCamara::aplicarViewport(int viewport_id, int ancho_ventana, int alto_ventana) {
    int mitad_ancho = ancho_ventana / 2;
    int mitad_alto = alto_ventana / 2;

    switch(viewport_id) {
        case 0:
            glViewport(0, mitad_alto, mitad_ancho, mitad_alto);
            break;
        case 1:
            glViewport(mitad_ancho, mitad_alto, mitad_ancho, mitad_alto);
            break;
        case 2:
            glViewport(0, 0, mitad_ancho, mitad_alto);
            break;
        case 3:
            glViewport(mitad_ancho, 0, mitad_ancho, mitad_alto);
            break;
    }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (tipo == IGV_PARALELA) {
        glOrtho(xwmin, xwmax, ywmin, ywmax, znear, zfar);
    }
    else if (tipo == IGV_FRUSTUM) {
        glFrustum(xwmin, xwmax, ywmin, ywmax, znear, zfar);
    }
    else if (tipo == IGV_PERSPECTIVA) {
        double aspecto_viewport = (double)mitad_ancho / (double)mitad_alto;
        gluPerspective(angulo, aspecto_viewport, znear, zfar);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    igvPunto3D pos_camara, punto_ref, vector_up;

    switch(viewport_id) {
        case 0:
            pos_camara = igvPunto3D(r[X], r[Y], r[Z] + 6.0);
            punto_ref = r;
            vector_up = igvPunto3D(0.0, 1.0, 0.0);
            break;
        case 1:
            pos_camara = igvPunto3D(r[X], r[Y] + 6.0, r[Z]);
            punto_ref = r;
            vector_up = igvPunto3D(0.0, 0.0, -1.0);
            break;
        case 2:
            pos_camara = igvPunto3D(r[X] + 6.0, r[Y], r[Z]);
            punto_ref = r;
            vector_up = igvPunto3D(0.0, 1.0, 0.0);
            break;
        case 3:
            pos_camara = P0;
            punto_ref = r;
            vector_up = V;
            break;
    }

    gluLookAt(pos_camara[X], pos_camara[Y], pos_camara[Z],
              punto_ref[X], punto_ref[Y], punto_ref[Z],
              vector_up[X], vector_up[Y], vector_up[Z]);
}

void igvCamara::siguienteVista() {
    vistaActual = (vistaActual + 1) % 4;
    aplicarVistaActual();
}

void igvCamara::aplicarVistaActual() {
    switch (vistaActual) {
        case 0: // Panoramica
            P0 = igvPunto3D(3.5, 4.0, 10.0);
            r = igvPunto3D(0.0, 0.0, 0.0);
            V = igvPunto3D(0.0, 1.0, 0.0);
            break;
        case 1: // Planta
            P0 = igvPunto3D(0.0, 8.0, 0.0);
            r = igvPunto3D(0.0, 0.0, 0.0);
            V = igvPunto3D(0.0, 0.0, -1.0);
            break;
        case 2: // Perfil
            P0 = igvPunto3D(8.0, 0.0, 0.0);
            r = igvPunto3D(0.0, 0.0, 0.0);
            V = igvPunto3D(0.0, 1.0, 0.0);
            break;
        case 3: // Alzado
            P0 = igvPunto3D(0.0, 0.0, 8.0);
            r = igvPunto3D(0.0, 0.0, 0.0);
            V = igvPunto3D(0.0, 1.0, 0.0);
            break;
    }
}
