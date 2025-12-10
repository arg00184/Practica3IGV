#include <cstdlib>
#include <stdio.h>
#include "igvEscena3D.h"

#include "igvPunto3D.h"


igvEscena3D::igvEscena3D() {
    ejes = true;
    bombilla = new igvFuenteLuz(
         GL_LIGHT0,
         igvPunto3D(1, 1, 1),
         igvColor(0, 0, 0, 1),
         igvColor(1, 1, 1, 1),
         igvColor(1, 1, 1, 1),
         1, 0, 0
 );
    bombilla->encender();

    foco = new igvFuenteLuz(
            GL_LIGHT1,
            igvPunto3D(3, 1, 1),
            igvColor(0, 0, 0, 1),
            igvColor(1, 1, 1, 1),
            igvColor(1, 1, 1, 1),
            1, 0, 0,
            igvPunto3D(0, -1, 0),
            45,
            0
    );
    foco->encender();

    material = new igvMaterial(
            igvColor(0.15, 0, 0),
            igvColor(0.5, 0, 0),
            igvColor(0.5, 0, 0),
            120
    );
    textura = nullptr;
}

igvEscena3D::~igvEscena3D() {
    delete bombilla;
    delete foco;
    delete material;
    delete textura;
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

void igvEscena3D::pintar_quad() {
    float ini_x = 0.0;
    float ini_z = 0.0;
    float tam_x = 5.0;
    float tam_z = 5.0;

    glNormal3f(0, 1, 0);
    glBegin(GL_QUADS);
    glVertex3f(ini_x, 0.0, ini_z);
    glVertex3f(ini_x, 0.0, ini_z + tam_z);
    glVertex3f(ini_x + tam_x, 0.0, ini_z + tam_z);
    glVertex3f(ini_x + tam_x, 0.0, ini_z);
    glEnd();
}

void igvEscena3D::pintar_quad(float div_x, float div_z) {
    float ini_x = 0.0;
    float ini_z = 0.0;
    float tam_x = 5.0;
    float tam_z = 5.0;

    float longX = tam_x / div_x;
    float longZ = tam_z / div_z;

    glNormal3f(0, 1, 0);
    for (int i = 0; i < div_x; i++) {
        for (int j = 0; j < div_z; j++) {
            glBegin(GL_QUADS);
            glTexCoord2f((ini_x + i * longX) / tam_x, (ini_z + j * longZ) / tam_z);
            glVertex3f(ini_x + i * longX, 0.0f, ini_z + j * longZ);

            glTexCoord2f((ini_x + i * longX) / tam_x, (ini_z + (j + 1) * longZ) / tam_z);
            glVertex3f(ini_x + i * longX, 0.0f, ini_z + (j + 1) * longZ);

            glTexCoord2f((ini_x + (i + 1) * longX) / tam_x, (ini_z + (j + 1) * longZ) / tam_z);
            glVertex3f(ini_x + (i + 1) * longX, 0.0f, ini_z + (j + 1) * longZ);

            glTexCoord2f((ini_x + (i + 1) * longX) / tam_x, (ini_z + j * longZ) / tam_z);
            glVertex3f(ini_x + (i + 1) * longX, 0.0f, ini_z + j * longZ);
            glEnd();
        }
    }
}

void igvEscena3D::visualizar() {

    glPushMatrix();

    if (ejes) {
        pintar_ejes();
    }

    // luces se aplican antes de las transformaciones a la escena para que permanezcan fijas

    // TODO: APARTADO A: Define y aplica la luz puntual especificada en el gui�n de pr�cticas
    bombilla->aplicar(); //Creo las luces, materiales y textura en el constructor para no generarlas con cada actualización de la ventana

    // TODO: APARTADO E: Define y aplica la luz tipo foco especificada en el gui�n de pr�cticas
    foco->aplicar();

    /* TODO: Apartado B: definir y aplicar las propiedades de material indicadas en el gui�n de pr�cticas */
    material->aplicar();

    /* TODO: Apartado D: sustituir los valores correspondientes a la componente R del coeficiende difuso,
                   la componente R del coeficiente especular y el exponente de Phong, por el valor
                          del atributo correspondiente de la clase igvEscena */
    //Teclas

    /* TODO: Apartado F: A�ade aqu� la creaci�n del objeto textura y su aplicaci�n */
    if(textura==nullptr){
        textura = new igvTextura((char *) "../mapa.png"); //Solo la cargo la 1 vez
    }
    textura->aplicar();
    pintar_quad(50, 50);

    //pintar_quad ();


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