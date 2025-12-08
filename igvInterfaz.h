#ifndef __IGVINTERFAZ
#define __IGVINTERFAZ

#if defined(__APPLE__) && defined(__MACH__)

#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#else
#include <GL/glut.h>
#endif   // defined(__APPLE__) && defined(__MACH__)

#include <string>
#include "igvEscena3D.h"
#include "igvCamara.h"

class igvInterfaz {
public:
    static igvInterfaz &getInstancia();

    ~igvInterfaz() = default;

    static void keyboardFunc(unsigned char key, int x, int y);

    static void specialFunc(int key, int x, int y);

    static void reshapeFunc(int w, int h);

    static void timerFunc(int value);

    static void displayFunc();

    static void mouseFunc(int button, int state, int x, int y);

    static void motionFunc(int x, int y);

    void configura_entorno(int argc, char **argv
                           , int _ancho_ventana, int _alto_ventana
                           , int _pos_X, int _pos_Y
                           , std::string _titulo
    );

    void create_menu();

    void inicializa_callbacks();

    void inicia_bucle_visualizacion();

    int get_ancho_ventana();

    int get_alto_ventana();

    void set_ancho_ventana(int _ancho_ventana);

    void set_alto_ventana(int _alto_ventana);

    bool getModoMultiViewport() const { return modoMultiViewport; }

    void cambiaModoMultiViewPort() { modoMultiViewport = !modoMultiViewport; }

    void cambiarModoInteraccion();

    bool getModoSeleccion() const { return modoSeleccion; }

    void mostrarAyudaInicial() const;

    void aplicarIncrementoSeleccionadoHorizontal(float incremento);

    void aplicarIncrementoSeleccionadoVertical(float incremento);

    void aplicarMovimientoRaton(int dx, int dy);


private:
    int ancho_ventana = 0;
    int alto_ventana = 0;
    igvCamara camara;
    bool modoMultiViewport = false;
    bool animacionModeloActiva = false;
    bool orbitaAutomaticaActiva = false;
    int timerAnimacion = 16;
    bool modoSeleccion = false;
    bool modoTransformacionGlobal = false;
    igvEscena3D escena;
    static igvInterfaz *_instancia;

    bool arrastrando = false;
    int ultimoX = 0;
    int ultimoY = 0;

    igvInterfaz();
};

#endif   // __IGVINTERFAZ