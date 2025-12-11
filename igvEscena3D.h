#ifndef __IGVESCENA3D
#define __IGVESCENA3D

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif

#include "igvModeloArticulado.h"
#include "igvMallaTriangulos.h"
#include "igvFuenteLuz.h"
#include "igvMaterial.h"
#include "igvTextura.h"


// Clase principal de la escena. Gestiona las fuentes de luz disponibles
// (puntual, direccional y spotlight), los materiales y texturas del suelo
// y las transformaciones globales que se aplican sobre los modelos.
class igvEscena3D {
public:
    igvEscena3D();

    ~igvEscena3D();

    void visualizar();

    bool get_ejes();

    void set_ejes(bool _ejes);

    igvFuenteLuz* getLuzPuntual() { return luzPuntual; }
    igvFuenteLuz* getLuzDireccional() { return luzDireccional; }
    igvFuenteLuz* getLuzSpotlight() { return luzSpotlight; }

    // Encendido y apagado de las tres fuentes de luz parametrizables.
    void activarLuzPuntual(bool encendida);
    void activarLuzDireccional(bool encendida);
    void activarLuzSpotlight(bool encendida);


    // Permite alternar entre los materiales disponibles para el suelo.
    void cambiarMaterial(int indice);
    igvMaterial* getMaterialActual() { return materiales[materialActual]; }
    igvMaterial* getMaterial() { return materiales[materialActual]; }

    // Activa o desactiva la textura del suelo y aplica los filtros seleccionados.
    void cambiarTextura(int indice);  // -1 para desactivar
    void setFiltroMag(GLenum filtro);
    void setFiltroMin(GLenum filtro);

    void setModoMovimientoLuz(int modo) { modoMovimientoLuz = modo; }
    int getModoMovimientoLuz() const { return modoMovimientoLuz; }

    void cambiarUsoNormales();

    void setUsoNormales(bool habilitar);

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

    igvFuenteLuz* luzPuntual;
    igvFuenteLuz* luzDireccional;
    igvFuenteLuz* luzSpotlight;

    igvMaterial* materiales[3];
    int materialActual = 0;

    igvTextura* texturas[3];
    int texturaActual = -1;        // -1 = sin textura
    bool texturaActiva = false;

    GLenum filtroMagActual = GL_LINEAR;
    GLenum filtroMinActual = GL_LINEAR;

    int modoMovimientoLuz = 0;     // 0=ninguno, 1=puntual, 2=spotlight


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


    void pintar_quad(float div_x, float div_z);

    void inicializarLuces();
    void inicializarMateriales();
    void inicializarTexturas();

public:
    igvModeloArticulado& getModelo() { return modelo; }

};

#endif