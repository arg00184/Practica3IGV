#include <cstdlib>
#include <stdio.h>
#include <exception>
#include <iostream>
#include "igvEscena3D.h"

#include "igvPunto3D.h"



igvEscena3D::igvEscena3D() {
    ejes = true;

    inicializarLuces();
    inicializarMateriales();
    inicializarTexturas();
}

igvEscena3D::~igvEscena3D() {
    delete luzPuntual;
    delete luzDireccional;
    delete luzSpotlight;

    for (int i = 0; i < 3; i++) {
        delete materiales[i];
        if (texturas[i]) delete texturas[i];
    }
}

void igvEscena3D::inicializarLuces() {
    // Luz puntual (GL_LIGHT0)
    luzPuntual = new igvFuenteLuz(
        GL_LIGHT0,
        igvPunto3D(2, 3, 2),           // Posición sobre la escena
        igvColor(0.1, 0.1, 0.1, 1),    // Ambiente
        igvColor(1, 1, 1, 1),          // Difuso
        igvColor(1, 1, 1, 1),          // Especular
        1, 0, 0                         // Atenuación
    );
    luzPuntual->encender();

    // Luz direccional (GL_LIGHT1) - simula el sol
    luzDireccional = new igvFuenteLuz(
        GL_LIGHT1,
        igvPunto3D(0, 1, 0),           // Dirección (w=0 para direccional)
        igvColor(0.2, 0.2, 0.2, 1),
        igvColor(0.8, 0.8, 0.7, 1),
        igvColor(0.5, 0.5, 0.5, 1),
        1, 0, 0,
        true
    );
    luzDireccional->encender();

    // Spotlight (GL_LIGHT2)
    luzSpotlight = new igvFuenteLuz(
        GL_LIGHT2,
        igvPunto3D(0, 2.25, 0),        // Posición centrada sobre el suelo
        igvColor(0, 0, 0, 1),
        igvColor(1, 1, 0.8, 1),        // Luz cálida
        igvColor(1, 1, 1, 1),
        1, 0, 0,
        igvPunto3D(0, -1, 0),          // Dirección: hacia abajo
        12,                             // Ángulo de apertura muy focalizado
        30                              // Exponente más alto para un cono definido
    );
    luzSpotlight->encender();
}

void igvEscena3D::activarLuzPuntual(bool encendida) {
    if (encendida) {
        luzPuntual->encender();
    } else {
        luzPuntual->apagar();
    }
}

void igvEscena3D::activarLuzDireccional(bool encendida) {
    if (encendida) {
        luzDireccional->encender();
    } else {
        luzDireccional->apagar();
    }
}

void igvEscena3D::activarLuzSpotlight(bool encendida) {
    if (encendida) {
        luzSpotlight->encender();
    } else {
        luzSpotlight->apagar();
    }
}

// ============ INICIALIZAR MATERIALES ============
void igvEscena3D::inicializarMateriales() {
    // Material 1: Rojo brillante
    materiales[0] = new igvMaterial(
        igvColor(0.15, 0.0, 0.0),      // Ka
        igvColor(0.6, 0.1, 0.1),       // Kd
        igvColor(0.8, 0.8, 0.8),       // Ks
        100                             // Ns
    );

    // Material 2: Azul mate
    materiales[1] = new igvMaterial(
        igvColor(0.0, 0.0, 0.15),
        igvColor(0.1, 0.1, 0.5),
        igvColor(0.2, 0.2, 0.3),
        20
    );

    // Material 3: Dorado
    materiales[2] = new igvMaterial(
        igvColor(0.24725, 0.1995, 0.0745),
        igvColor(0.75164, 0.60648, 0.22648),
        igvColor(0.628281, 0.555802, 0.366065),
        51.2
    );
}

// ============ INICIALIZAR TEXTURAS ============
void igvEscena3D::inicializarTexturas() {
    texturas[0] = nullptr;  // Se carga bajo demanda
    texturas[1] = nullptr;
    texturas[2] = nullptr;
}


void igvEscena3D::pintar_ejes() {
    GLfloat rojo[] = {1, 0, 0, 1.0};
    GLfloat verde[] = {0, 1, 0, 1.0};
    GLfloat azul[] = {0, 0, 1, 1.0};

    glMaterialfv(GL_FRONT, GL_EMISSION, rojo);
    glBegin(GL_LINES);
    glVertex3f(1000, 0, 0);
    glVertex3f(-1000, 0, 0);
    glEnd();

    glMaterialfv(GL_FRONT, GL_EMISSION, verde);
    glBegin(GL_LINES);
    glVertex3f(0, 1000, 0);
    glVertex3f(0, -1000, 0);
    glEnd();

    glMaterialfv(GL_FRONT, GL_EMISSION, azul);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 1000);
    glVertex3f(0, 0, -1000);
    glEnd();
}



void igvEscena3D::pintar_quad(float div_x, float div_z) {
    float ini_x = -2.5f;  // Centrado en origen
    float ini_z = -2.5f;
    float tam_x = 5.0f;
    float tam_z = 5.0f;

    float longX = tam_x / div_x;
    float longZ = tam_z / div_z;

    glNormal3f(0, 1, 0);

    for (int i = 0; i < div_x; i++) {
        for (int j = 0; j < div_z; j++) {
            glBegin(GL_QUADS);

            float x0 = ini_x + i * longX;
            float z0 = ini_z + j * longZ;
            float x1 = ini_x + (i + 1) * longX;
            float z1 = ini_z + (j + 1) * longZ;

            // Coordenadas de textura normalizadas [0,1]
            float s0 = (float)i / div_x;
            float t0 = (float)j / div_z;
            float s1 = (float)(i + 1) / div_x;
            float t1 = (float)(j + 1) / div_z;

            glTexCoord2f(s0, t0); glVertex3f(x0, 0.0f, z0);
            glTexCoord2f(s0, t1); glVertex3f(x0, 0.0f, z1);
            glTexCoord2f(s1, t1); glVertex3f(x1, 0.0f, z1);
            glTexCoord2f(s1, t0); glVertex3f(x1, 0.0f, z0);

            glEnd();
        }
    }
}

void igvEscena3D::visualizar() {

    glPushMatrix();

    if (ejes) {
        pintar_ejes();
    }

    luzPuntual->aplicar();
    luzDireccional->aplicar();
    luzSpotlight->aplicar();


    glPushMatrix();
    glTranslatef(0, -0.5f, 0);

    // Aplicar material del suelo
    materiales[materialActual]->aplicar();

    // Aplicar textura si está activa
    if (texturaActiva && texturas[texturaActual] != nullptr) {
        glEnable(GL_TEXTURE_2D);
        texturas[texturaActual]->aplicar();
    } else {
        glDisable(GL_TEXTURE_2D);
    }

    pintar_quad(50, 50);

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

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

void igvEscena3D::cambiarMaterial(int indice) {
    if (indice >= 0 && indice < 3) {
        materialActual = indice;
    }
}

void igvEscena3D::cambiarTextura(int indice) {
    if (indice < 0) {
        texturaActiva = false;
        texturaActual = -1;
    } else if (indice < 3) {
        if (texturas[indice] == nullptr) {
            try {
                switch(indice) {
                    case 0:
                        texturas[0] = new igvTextura("texturas/textura_plastico.png");
                        break;
                    case 1:
                        texturas[1] = new igvTextura("texturas/textura_rugosa.png");
                        break;
                    case 2:
                        texturas[2] = igvTextura::crearTableroAjedrez(256, 8);
                        break;
                }
                texturas[indice]->setFiltroMag(filtroMagActual);
                texturas[indice]->setFiltroMin(filtroMinActual);
            } catch (const std::exception& e) {
                std::cerr << "No se pudo cargar la textura: " << e.what() << "\n";
                return;
            }
        }
        texturaActual = indice;
        texturaActiva = true;
    }
}


void igvEscena3D::setFiltroMag(GLenum filtro) {
    filtroMagActual = filtro;
    for (int i = 0; i < 3; i++) {
        if (texturas[i] != nullptr) {
            texturas[i]->setFiltroMag(filtro);
        }
    }
}

void igvEscena3D::setFiltroMin(GLenum filtro) {
    filtroMinActual = filtro;
    for (int i = 0; i < 3; i++) {
        if (texturas[i] != nullptr) {
            texturas[i]->setFiltroMin(filtro);
        }
    }
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

void igvEscena3D::setModoSombreadoSuave(bool habilitar) {
    modelo.setModoSombreadoSuave(habilitar);
    if (mallaCargada) {
        malla.setGouraud(habilitar);
    }
}

void igvEscena3D::setUsoNormales(bool habilitar) {
    modelo.setUsoNormales(habilitar);
    if (mallaCargada) {
        malla.setUsoNormales(habilitar);
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