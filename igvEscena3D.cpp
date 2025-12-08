#include <cstdlib>
#include <stdio.h>
#include "igvEscena3D.h"

igvEscena3D::igvEscena3D() {
    ejes = false;
    mallaCargada = malla.cargarOBJ("airplane_triangles.obj");
}

igvEscena3D::~igvEscena3D() {
}

void igvEscena3D::pintar_ejes() {
    GLfloat rojo[] = {1, 0, 0, 1.0};
    GLfloat verde[] = {0, 1, 0, 1.0};
    GLfloat azul[] = {0, 0, 1, 1.0};

    glBegin(GL_LINES);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rojo);
    glVertex3f(1000, 0, 0);
    glVertex3f(-1000, 0, 0);

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, verde);
    glVertex3f(0, 1000, 0);
    glVertex3f(0, -1000, 0);

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, azul);
    glVertex3f(0, 0, 1000);
    glVertex3f(0, 0, -1000);
    glEnd();
}

void igvEscena3D::visualizar() {
    GLfloat light0[] = {10, 8, 9, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, light0);
    glEnable(GL_LIGHT0);

    glPushMatrix();

    if (ejes) {
        pintar_ejes();
    }

    glPushMatrix();
    glTranslatef(traslacionX, traslacionY, traslacionZ);
    glRotatef(rotacionX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotacionY, 0.0f, 1.0f, 0.0f);
    glRotatef(rotacionZ, 0.0f, 0.0f, 1.0f);
    glScalef(escala, escala, escala);

    if (mallaCargada) {
        GLfloat color_malla[] = {0.6f, 0.6f, 0.8f, 1.0f};
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color_malla);
        glPushMatrix();
        glTranslatef(-1.5f, 0.0f, -1.0f);
        glScalef(0.5f, 0.5f, 0.5f);
        malla.visualizar();
        glPopMatrix();
    }

    modelo.visualizar();

    glPopMatrix();

    glPopMatrix();
}

bool igvEscena3D::get_ejes() {
    return ejes;
}

void igvEscena3D::set_ejes(bool _ejes) {
    ejes = _ejes;
}

void igvEscena3D::cambiarModoSombreado() {
    modelo.cambiarModoSombreado();
    if (mallaCargada) {
        malla.cambiarvis();
    }
}

void igvEscena3D::cambiarUsoNormales() {
    modelo.cambiarUsoNormales();
    if (mallaCargada) {
        malla.cambiarnormales();
    }
}

void igvEscena3D::rotarBaseLampara(float incremento) {
    modelo.rotarBase(incremento);
}

void igvEscena3D::rotarBrazo1Lampara(float incremento) {
    modelo.rotarBrazo1(incremento);
}

void igvEscena3D::rotarBrazo2Lampara(float incremento) {
    modelo.rotarBrazo2(incremento);
}

void igvEscena3D::rotarBrazo2LateralLampara(float incremento) {
    modelo.rotarBrazo2Lateral(incremento);
}

void igvEscena3D::rotarPantallaLampara(float incremento) {
    modelo.rotarPantalla(incremento);
}

void igvEscena3D::rotarPantallaLateralLampara(float incremento) {
    modelo.rotarPantallaLateral(incremento);
}

void igvEscena3D::resetearPoseLampara() {
    modelo.resetearPose();
}

void igvEscena3D::visualizarModoSeleccion() {
    glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_DITHER);

    glPushMatrix();
    glTranslatef(traslacionX, traslacionY, traslacionZ);
    glRotatef(rotacionX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotacionY, 0.0f, 1.0f, 0.0f);
    glRotatef(rotacionZ, 0.0f, 0.0f, 1.0f);
    glScalef(escala, escala, escala);
    modelo.visualizarSeleccion();
    glPopMatrix();

    glPopAttrib();
}

unsigned char* igvEscena3D::capturarBufferSeleccion(int x, int y) {
    static unsigned char pixel[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
    return pixel;
}

int igvEscena3D::identificarPartePorColor(unsigned char r, unsigned char g, unsigned char b) {
    if (r == 255 && g == 0 && b == 0) return 0; // Base
    if (r == 0 && g == 255 && b == 0) return 1; // Brazo1
    if (r == 0 && g == 0 && b == 255) return 2; // Brazo2
    if (r == 255 && g == 255 && b == 0) return 3; // Pantalla
    return -1;
}

void igvEscena3D::seleccionarParte(int x, int y, int alto_ventana) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    visualizarModoSeleccion();
    glFlush();
    glFinish();
    unsigned char* pixel = capturarBufferSeleccion(x, alto_ventana - y);
    parteSeleccionada = identificarPartePorColor(pixel[0], pixel[1], pixel[2]);
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

void igvEscena3D::trasladarX(float incremento) {
    traslacionX += incremento;
}

void igvEscena3D::trasladarY(float incremento) {
    traslacionY += incremento;
}

void igvEscena3D::trasladarZ(float incremento) {
    traslacionZ += incremento;
}

void igvEscena3D::rotarEscenaX(float incremento) {
    rotacionX += incremento;
}

void igvEscena3D::rotarEscenaY(float incremento) {
    rotacionY += incremento;
}

void igvEscena3D::rotarEscenaZ(float incremento) {
    rotacionZ += incremento;
}

void igvEscena3D::escalarEscena(float factor) {
    escala += factor;
    if (escala < 0.1f) {
        escala = 0.1f;
    }
}