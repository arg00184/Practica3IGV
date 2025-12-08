#ifndef __IGV_MODELO_ARTICULADO_H
#define __IGV_MODELO_ARTICULADO_H

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif

#include "igvCilindro.h"
#include "igvDisco.h"
#include "igvEsfera.h"

class igvModeloArticulado {
private:
  // Ángulos de las articulaciones (grados de libertad)
  float anguloBase;           // Rotación de la base (eje Y)
  float anguloBrazoDerecho;   // Flexión del brazo derecho lateral
  float anguloBrazoIzquierdo; // Flexión del brazo izquierdo lateral
  float anguloBrazo1;         // Flexión del primer brazo principal
  float anguloBrazo2;         // Flexión del segundo brazo principal
  float anguloBrazo2Yaw;      // Giro lateral del segundo brazo principal
  float anguloPantalla;       // Inclinación de la pantalla
  float anguloPantallaYaw;    // Giro lateral de la pantalla

  // Modo de visualización
  bool sombreado_suave;
  bool usar_normales;

  // Primitivas personalizadas reutilizables
  igvCilindro *cilindroUnidad;
  igvDisco *discoUnidad;
  igvEsfera *esferaUnidad;

  // Métodos privados para dibujar cada parte
  void dibujarBase();
  void dibujarArticulacion();
  void dibujarBrazoLateral(float longitud, float radio);
  void dibujarBrazoPrincipal(float longitud, float radio);
  void dibujarPantalla();

  float velBase = 1.0f;
  float velBrazo1 = 0.5f;
  float velBrazo2 = 0.4f;
  float velBrazo2Y = 0.4f;
  float velPantalla = 0.5f;
  float velPantallaY = 0.3f;

public:
  igvModeloArticulado();
  ~igvModeloArticulado();

  // Método principal de visualización
  void visualizar();

  // Visualización simplificada por colores para el modo de selección
  void visualizarSeleccion();

  // Métodos para modificar grados de libertad
  void rotarBase(float incremento);
  void rotarBrazoDerecho(float incremento);
  void rotarBrazoIzquierdo(float incremento);
  void rotarBrazo1(float incremento);
  void rotarBrazo2(float incremento);
  void rotarBrazo2Lateral(float incremento);
  void rotarPantalla(float incremento);
  void rotarPantallaLateral(float incremento);

  void resetearPose();

  // Métodos para cambiar visualización
  void cambiarModoSombreado();
  void cambiarUsoNormales();

  void animarContinuo();
};

#endif