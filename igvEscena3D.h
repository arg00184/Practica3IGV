#ifndef __IGVESCENA3D
#define __IGVESCENA3D
#include "igvFuenteLuz.h"
#include "igvMaterial.h"
#include "igvTextura.h"

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif

#include "igvModeloArticulado.h"
#include "igvMallaTriangulos.h"

class igvEscena3D {
public:
    igvEscena3D();

    ~igvEscena3D();

    void visualizar();

    bool get_ejes();

    void set_ejes(bool _ejes);

    igvFuenteLuz *getFoco() { return foco; }

    igvMaterial *getMaterial() { return material; };

    void cambiarModoSombreado();

    void cambiarUsoNormales();

    void rotarBaseLampara(float incremento);

    void rotarBrazo1Lampara(float incremento);

    void rotarBrazo2Lampara(float incremento);

    void rotarBrazo2LateralLampara(float incremento);

    void rotarPantallaLampara(float incremento);

    void rotarPantallaLateralLampara(float incremento);

    void resetearPoseLampara();

    void trasladarX(float incremento);

    void trasladarY(float incremento);

    void trasladarZ(float incremento);

    void rotarEscenaX(float incremento);

    void rotarEscenaY(float incremento);

    void rotarEscenaZ(float incremento);

    void escalarEscena(float factor);

    void activarModoSeleccion(bool activo) { modoSeleccion = activo; }
    bool getModoSeleccion() const { return modoSeleccion; }
    int getParteSeleccionada() const { return parteSeleccionada; }
    void setParteSeleccionada(int parte) { parteSeleccionada = parte; }

    void seleccionarParte(int x, int y, int alto_ventana);

private:
    bool ejes = true;
    igvModeloArticulado modelo;
    igvMallaTriangulos malla;
    igvFuenteLuz *bombilla, *foco;
    igvMaterial *material;
    igvTextura *textura;
    bool mallaCargada = false;
    bool modoSeleccion = false;
    int parteSeleccionada = -1; // -1: ninguna, 0: base, 1: brazo1, 2: brazo2, 3: pantalla
    float traslacionX = 0.0f;
    float traslacionY = 0.0f;
    float traslacionZ = 0.0f;
    float rotacionX = 0.0f;
    float rotacionY = 0.0f;
    float rotacionZ = 0.0f;
    float escala = 1.0f;

    void visualizarModoSeleccion();

    unsigned char *capturarBufferSeleccion(int x, int y);

    int identificarPartePorColor(unsigned char r, unsigned char g, unsigned char b);

    void pintar_ejes();

    void pintar_quad();

    void pintar_quad(float div_x, float div_z);

public:
    igvModeloArticulado& getModelo() { return modelo; }

};

#endif