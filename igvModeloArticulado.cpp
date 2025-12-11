#include "igvModeloArticulado.h"
#include "igvModeloArticulado.h"
#include "igvCilindro.h"
#include "igvDisco.h"
#include <algorithm>

/**
 * Constructor por defecto
 */
igvModeloArticulado::igvModeloArticulado() {
    // Pose inicial de la lámpara estilo Pixar
    anguloBase = 0.0f;
    anguloBrazoDerecho = 30.0f;
    anguloBrazoIzquierdo = 30.0f;
    anguloBrazo1 = 45.0f;
    anguloBrazo2 = -30.0f;
    anguloBrazo2Yaw = 0.0f;
    anguloPantalla = -45.0f;
    anguloPantallaYaw = 0.0f;
    usar_normales = true;

    cilindroUnidad = nullptr;
    discoUnidad = nullptr;
    esferaUnidad = nullptr;


}

/**
 * Destructor
 */
igvModeloArticulado::~igvModeloArticulado() {
}

/**
 * Dibuja la base de la lámpara con más detalle
 */
void igvModeloArticulado::dibujarBase() {
    GLfloat color_base[] = {0.15f, 0.15f, 0.15f, 1.0f};
    GLfloat color_plataforma[] = {0.25f, 0.25f, 0.25f, 1.0f};

    static igvCilindro cilindroUnidad(1.0f, 1.0f, 30, 1);
    static igvDisco discoUnidad(1.0f, 30);

    // Base principal (disco grande y bajo)
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color_base);
    glPushMatrix();
    glScalef(0.5f, 0.05f, 0.5f);
    cilindroUnidad.visualizar();
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5f, 0.5f, 0.5f);
    discoUnidad.visualizar();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0.05f, 0);
    glScalef(0.5f, 0.5f, 0.5f);
    discoUnidad.visualizar();
    glPopMatrix();

    // Plataforma central elevada (donde van los brazos)
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color_plataforma);
    glPushMatrix();
    glTranslatef(0, 0.05f, 0);
    glScalef(0.15f, 0.1f, 0.15f);
    cilindroUnidad.visualizar();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0.15f, 0);
    glScalef(0.12f, 0.12f, 0.12f);
    discoUnidad.visualizar();
    glPopMatrix();
}


/**
 * Dibuja una articulación (esfera pequeña)
 */
void igvModeloArticulado::dibujarArticulacion() {
    GLfloat color_articulacion[] = {0.35f, 0.35f, 0.35f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color_articulacion);

    GLUquadric* quad = gluNewQuadric();
    gluQuadricNormals(quad, GLU_SMOOTH);
    gluSphere(quad, 0.09, 15, 15);
    gluDeleteQuadric(quad);
}

/**
 * Dibuja un brazo lateral mejorado con más detalle
 */
void igvModeloArticulado::dibujarBrazoLateral(float longitud, float radio) {
    GLfloat color_brazo_lateral[] = {0.25f, 0.25f, 0.25f, 1.0f};
    GLfloat color_detalle[] = {0.4f, 0.4f, 0.4f, 1.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color_brazo_lateral);

    GLUquadric* quad = gluNewQuadric();
    gluQuadricNormals(quad, GLU_SMOOTH);

    // Cilindro principal más largo y elegante
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    gluCylinder(quad, radio, radio * 0.7, longitud, 16, 1);
    glPopMatrix();

    // Anillo decorativo en el medio
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color_detalle);
    glPushMatrix();
    glTranslatef(0, longitud * 0.5, 0);
    glRotatef(-90, 1, 0, 0);
    gluCylinder(quad, radio * 1.15, radio * 1.15, 0.02, 16, 1);
    glPopMatrix();

    // Esfera al final del brazo
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color_brazo_lateral);
    glPushMatrix();
    glTranslatef(0, longitud, 0);
    gluSphere(quad, radio * 0.9, 12, 12);
    glPopMatrix();

    gluDeleteQuadric(quad);
}

/**
 * Dibuja un brazo principal mejorado de la lámpara
 */
void igvModeloArticulado::dibujarBrazoPrincipal(float longitud, float radio) {
    GLfloat color_brazo[] = {0.65f, 0.15f, 0.15f, 1.0f};
    GLfloat color_anillo[] = {0.3f, 0.3f, 0.3f, 1.0f};

    GLUquadric* quad = gluNewQuadric();
    gluQuadricNormals(quad, GLU_SMOOTH);

    // Brazo principal con ligera conicidad
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color_brazo);
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    gluCylinder(quad, radio, radio * 0.8, longitud, 24, 1);
    glPopMatrix();

    // Anillos decorativos (3 en vez de 2)
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color_anillo);

    // Anillo inferior
    glPushMatrix();
    glTranslatef(0, longitud * 0.15, 0);
    glRotatef(-90, 1, 0, 0);
    gluCylinder(quad, radio * 1.12, radio * 1.12, 0.025, 24, 1);
    glPopMatrix();

    // Anillo medio
    glPushMatrix();
    glTranslatef(0, longitud * 0.5, 0);
    glRotatef(-90, 1, 0, 0);
    gluCylinder(quad, radio * 1.05, radio * 1.05, 0.025, 24, 1);
    glPopMatrix();

    // Anillo superior
    glPushMatrix();
    glTranslatef(0, longitud * 0.85, 0);
    glRotatef(-90, 1, 0, 0);
    gluCylinder(quad, radio * 0.9, radio * 0.9, 0.025, 24, 1);
    glPopMatrix();

    gluDeleteQuadric(quad);
}

/**
 * Dibuja la pantalla de la lámpara estilo Pixar con luz interior
 */
void igvModeloArticulado::dibujarPantalla() {
    GLfloat color_pantalla[] = {0.85f, 0.85f, 0.15f, 1.0f};
    GLfloat color_interior[] = {0.95f, 0.95f, 0.95f, 1.0f};
    GLfloat color_bombilla[] = {1.0f, 0.95f, 0.7f, 1.0f};

    GLUquadric* quad = gluNewQuadric();
    gluQuadricNormals(quad, GLU_SMOOTH);

    glPushMatrix();
    // Eje del cono alineado con el brazo
    glRotatef(-90, 1, 0, 0);

    // Cono exterior
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color_pantalla);
    gluCylinder(quad, 0.12, 0.28, 0.35, 25, 1);

    // Borde del cono
    glPushMatrix();
    glTranslatef(0, 0, 0.35);
    gluDisk(quad, 0.28, 0.30, 25, 1);
    glPopMatrix();

    // Disco interior cerca del brazo
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color_interior);
    glPushMatrix();
    gluDisk(quad, 0.0, 0.12, 25, 1);
    glPopMatrix();

    // Bombilla con emisión de luz dentro del cono
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color_bombilla);
    GLfloat emision_luz[] = {0.6f, 0.6f, 0.3f, 1.0f};
    glMaterialfv(GL_FRONT, GL_EMISSION, emision_luz);

    glPushMatrix();
    glTranslatef(0, 0, 0.10f);
    gluSphere(quad, 0.08, 15, 15);
    glPopMatrix();

    GLfloat sin_emision[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_EMISSION, sin_emision);
    glPopMatrix();

    gluDeleteQuadric(quad);
}

/**
 * Visualiza el modelo articulado completo usando el grafo de escena
 */
void igvModeloArticulado::visualizar() {
    glShadeModel(GL_SMOOTH);

    if (usar_normales) {
        glEnable(GL_NORMALIZE);
    } else {
        glDisable(GL_NORMALIZE);
    }

    glPushMatrix();

    // NIVEL 1: Base completa
    dibujarBase();
    glTranslatef(0, 0.15, 0);

    // Rotación de la base (Grado de libertad 1)
    glRotatef(anguloBase, 0, 1, 0);

    // Articulación central
    dibujarArticulacion();

    // NIVEL 2: Primer brazo principal (más largo)
    glRotatef(anguloBrazo1, 1, 0, 0);
    dibujarBrazoPrincipal(1.0, 0.06);  // Aumentado de 0.7 a 1.0
    glTranslatef(0, 1.0, 0);

    // Segunda articulación
    dibujarArticulacion();

    // NIVEL 3: Segundo brazo principal (más largo)
    glRotatef(anguloBrazo2Yaw, 0, 1, 0);
    glRotatef(anguloBrazo2, 1, 0, 0);

    // Brazos laterales unidos al brazo superior (más largos)
    glPushMatrix();
    glTranslatef(0.0f, 0.4f, 0.0f);  // Ajustado para el brazo más largo

    // Brazo lateral derecho
    glPushMatrix();
    glRotatef(-90.0f, 0, 0, 1);
    dibujarBrazoLateral(0.35f, 0.035f);  // Aumentado de 0.25 a 0.35
    glPopMatrix();

    // Brazo lateral izquierdo
    glPushMatrix();
    glRotatef(90.0f, 0, 0, 1);
    dibujarBrazoLateral(0.35f, 0.035f);  // Aumentado de 0.25 a 0.35
    glPopMatrix();
    glPopMatrix();

    // Dibuja el segundo brazo principal (más largo)
    dibujarBrazoPrincipal(0.8f, 0.05f);  // Aumentado de 0.55 a 0.8
    glTranslatef(0, 0.8f, 0);

    // Tercera articulación
    dibujarArticulacion();

    // NIVEL 4: Pantalla
    glRotatef(anguloPantallaYaw, 0, 1, 0);
    glRotatef(anguloPantalla, 1, 0, 0);
    dibujarPantalla();

    glPopMatrix();
}

/**
 * Visualiza el modelo con colores sólidos para el buffer de selección
 */
void igvModeloArticulado::visualizarSeleccion() {
    glDisable(GL_LIGHTING);
    glDisable(GL_NORMALIZE);

    glPushMatrix();

    // NIVEL 1: Base completa
    glColor3ub(255, 0, 0); // Base en rojo
    dibujarBase();
    glTranslatef(0, 0.15, 0);

    // Rotación de la base (Grado de libertad 1)
    glRotatef(anguloBase, 0, 1, 0);

    // Articulación central
    dibujarArticulacion();

    // NIVEL 2: Primer brazo principal
    glRotatef(anguloBrazo1, 1, 0, 0);
    glColor3ub(0, 255, 0); // Brazo 1 en verde
    dibujarBrazoPrincipal(1.0, 0.06);
    glTranslatef(0, 1.0, 0);

    // Segunda articulación
    dibujarArticulacion();

    // NIVEL 3: Segundo brazo principal (incluye brazos laterales)
    glRotatef(anguloBrazo2Yaw, 0, 1, 0);
    glRotatef(anguloBrazo2, 1, 0, 0);

    glPushMatrix();
    glTranslatef(0.0f, 0.4f, 0.0f);
    glColor3ub(0, 0, 255); // Brazo 2 y laterales en azul

    glPushMatrix();
    glRotatef(-90.0f, 0, 0, 1);
    dibujarBrazoLateral(0.35f, 0.035f);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90.0f, 0, 0, 1);
    dibujarBrazoLateral(0.35f, 0.035f);
    glPopMatrix();
    glPopMatrix();

    glColor3ub(0, 0, 255); // Continuación del brazo 2
    dibujarBrazoPrincipal(0.8f, 0.05f);
    glTranslatef(0, 0.8f, 0);

    // Tercera articulación
    dibujarArticulacion();

    // NIVEL 4: Pantalla
    glRotatef(anguloPantallaYaw, 0, 1, 0);
    glRotatef(anguloPantalla, 1, 0, 0);
    glColor3ub(255, 255, 0); // Pantalla en amarillo
    dibujarPantalla();

    glPopMatrix();

    glEnable(GL_LIGHTING);
    if (usar_normales) {
        glEnable(GL_NORMALIZE);
    }
}

/**
 * Rota la base de la lámpara
 */
void igvModeloArticulado::rotarBase(float incremento) {
    anguloBase += incremento;
}

/**
 * Rota el brazo derecho lateral con límites realistas
 */
void igvModeloArticulado::rotarBrazoDerecho(float incremento) {
    anguloBrazoDerecho += incremento;
    anguloBrazoDerecho = std::max(-60.0f, std::min(60.0f, anguloBrazoDerecho));
}

/**
 * Rota el brazo izquierdo lateral con límites realistas
 */
void igvModeloArticulado::rotarBrazoIzquierdo(float incremento) {
    anguloBrazoIzquierdo += incremento;
    anguloBrazoIzquierdo = std::max(-60.0f, std::min(60.0f, anguloBrazoIzquierdo));
}

/**
 * Rota el primer brazo principal con límites realistas
 */
void igvModeloArticulado::rotarBrazo1(float incremento) {
    anguloBrazo1 += incremento;
    anguloBrazo1 = std::max(-90.0f, std::min(90.0f, anguloBrazo1));
}

/**
 * Rota el segundo brazo principal con límites realistas
 */
void igvModeloArticulado::rotarBrazo2(float incremento) {
    anguloBrazo2 += incremento;
    anguloBrazo2 = std::max(-120.0f, std::min(10.0f, anguloBrazo2));
}

/**
 * Giro lateral del segundo brazo principal
 */
void igvModeloArticulado::rotarBrazo2Lateral(float incremento) {
    anguloBrazo2Yaw += incremento;
    anguloBrazo2Yaw = std::max(-70.0f, std::min(70.0f, anguloBrazo2Yaw));
}

/**
 * Rota la pantalla con límites realistas
 */
void igvModeloArticulado::rotarPantalla(float incremento) {
    anguloPantalla += incremento;
    anguloPantalla = std::max(-90.0f, std::min(45.0f, anguloPantalla));
}

/**
 * Giro lateral de la pantalla con límites realistas
 */
void igvModeloArticulado::rotarPantallaLateral(float incremento) {
    anguloPantallaYaw += incremento;
    anguloPantallaYaw = std::max(-90.0f, std::min(90.0f, anguloPantallaYaw));
}

/**
 * Resetea la lámpara a su pose inicial
 */
void igvModeloArticulado::resetearPose() {
    anguloBase = 0.0f;
    anguloBrazoDerecho = 30.0f;
    anguloBrazoIzquierdo = 30.0f;
    anguloBrazo1 = 45.0f;
    anguloBrazo2 = -30.0f;
    anguloBrazo2Yaw = 0.0f;
    anguloPantalla = -45.0f;
    anguloPantallaYaw = 0.0f;
}

/**
 * Activa/desactiva el uso de normales
 */
void igvModeloArticulado::cambiarUsoNormales() {
    usar_normales = !usar_normales;
}

void igvModeloArticulado::setUsoNormales(bool habilitar) {
    usar_normales = habilitar;
}

void igvModeloArticulado::animarContinuo() {
    // Base (giro infinito, sin límites)
    anguloBase += velBase;

    // Brazo 1 — vaivén con rebote
    anguloBrazo1 += velBrazo1;
    if (anguloBrazo1 > 90 || anguloBrazo1 < -90)
        velBrazo1 = -velBrazo1;

    // Brazo 2 — vaivén vertical
    anguloBrazo2 += velBrazo2;
    if (anguloBrazo2 > 10 || anguloBrazo2 < -120)
        velBrazo2 = -velBrazo2;

    // Brazo 2 — vaivén lateral
    anguloBrazo2Yaw += velBrazo2Y;
    if (anguloBrazo2Yaw > 70 || anguloBrazo2Yaw < -70)
        velBrazo2Y = -velBrazo2Y;

    // Pantalla — vaivén vertical
    anguloPantalla += velPantalla;
    if (anguloPantalla > 45 || anguloPantalla < -90)
        velPantalla = -velPantalla;

    // Pantalla — vaivén lateral
    anguloPantallaYaw += velPantallaY;
    if (anguloPantallaYaw > 90 || anguloPantallaYaw < -90)
        velPantallaY = -velPantallaY;
}
