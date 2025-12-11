#include "igvTextura.h"
#include "lodepng.h"

#include <vector>
#include <stdexcept>
#include <iostream>
#include <fstream>

// Métodos constructores y destructor

/**
 * Constructor parametrizado. Carga una textura de archivo
 * @param fichero
 */
static std::string localizar_textura(const std::string& fichero) {
    std::string nombre = fichero;
    size_t pos = fichero.find_last_of("/\\");
    if (pos != std::string::npos) {
        nombre = fichero.substr(pos + 1);
    }

    std::vector<std::string> candidatos = {
        fichero,
        "../" + fichero,
        nombre,
        "../" + nombre
    };

    std::string probados;
    for (const auto& ruta : candidatos) {
        if (!probados.empty()) {
            probados += ", ";
        }
        probados += ruta;

        std::ifstream test(ruta, std::ios::binary);
        if (test.good()) {
            return ruta;
        }
    }

    throw std::runtime_error("Archivo no encontrado. Probado en: " + probados);
}

igvTextura::igvTextura(std::string fichero) {
    glEnable(GL_TEXTURE_2D);
    std::string ruta = localizar_textura(fichero);
    if (!glIsTexture(idTextura)) {
        std::vector<unsigned char> texeles;
        unsigned int error = lodepng::decode(texeles, ancho, alto, ruta);
        if (error) {
            throw std::runtime_error("Error leyendo archivo " + ruta);
        }
        glGenTextures(1, &idTextura);
        glBindTexture(GL_TEXTURE_2D, idTextura);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ancho, alto, 0,
                     GL_RGBA, GL_UNSIGNED_BYTE, texeles.data());
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }
}

/**
 * Destructor. Elimina la textura OpenGL relacionada
 */
igvTextura::~igvTextura ()
{  glDeleteTextures ( 1, &idTextura );
}

/**
 * Activa la textura OpenGL relacionada
 */
void igvTextura::aplicar ()
{  glBindTexture ( GL_TEXTURE_2D, idTextura );
}

/**
 * Cambia el identificador de la textura OpenGL relacionada
 * @param id Nuevo identificador de texturas
 * @pre Se asume que el parámetro es válido
 * @post El identificador de la textura OpenGL cambia
 */
void igvTextura::setIdTextura ( unsigned int id )
{  this->idTextura = id;
}

/**
 * Consulta del identificador de la textura OpenGL
 * @return El identificador de la textura OpenGL relacionada
 */
unsigned int igvTextura::getIdTextura ()
{  return this->idTextura;
}

void igvTextura::desactivar() {
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

void igvTextura::setFiltroMag(GLenum filtro) {
    filtroMag = filtro;
    glBindTexture(GL_TEXTURE_2D, idTextura);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtro);
}

void igvTextura::setFiltroMin(GLenum filtro) {
    filtroMin = filtro;
    glBindTexture(GL_TEXTURE_2D, idTextura);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtro);
}

igvTextura* igvTextura::crearTableroAjedrez(int tamano, int numCuadros) {
    igvTextura* tex = new igvTextura();
    std::vector<unsigned char> imagen(tamano * tamano * 4);
    int tamCuadro = tamano / numCuadros;

    for (int y = 0; y < tamano; y++) {
        for (int x = 0; x < tamano; x++) {
            int cuadroX = x / tamCuadro;
            int cuadroY = y / tamCuadro;
            bool blanco = (cuadroX + cuadroY) % 2 == 0;

            int idx = (y * tamano + x) * 4;
            unsigned char color = blanco ? 255 : 0;
            imagen[idx] = imagen[idx+1] = imagen[idx+2] = color;
            imagen[idx+3] = 255;
        }
    }

    tex->ancho = tamano;
    tex->alto = tamano;
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &tex->idTextura);
    glBindTexture(GL_TEXTURE_2D, tex->idTextura);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tamano, tamano, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, imagen.data());
    // Para esta textura queremos respetar los colores blanco y negro del tablero
    // sin que el material de la superficie los tiña, por lo que sustituimos el
    // color resultante en lugar de modularlo con el material.
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    return tex;
}

igvTextura* igvTextura::crearRayas(int tamano, int numRayas,
                                   unsigned char r1, unsigned char g1, unsigned char b1,
                                   unsigned char r2, unsigned char g2, unsigned char b2,
                                   bool vertical) {
    igvTextura* tex = new igvTextura();
    std::vector<unsigned char> imagen(tamano * tamano * 4);
    int tamRaya = tamano / numRayas;

    for (int y = 0; y < tamano; y++) {
        for (int x = 0; x < tamano; x++) {
            bool rayaPrincipal = vertical ? ((x / tamRaya) % 2 == 0) : ((y / tamRaya) % 2 == 0);
            unsigned char r = rayaPrincipal ? r1 : r2;
            unsigned char g = rayaPrincipal ? g1 : g2;
            unsigned char b = rayaPrincipal ? b1 : b2;

            int idx = (y * tamano + x) * 4;
            imagen[idx] = r;
            imagen[idx + 1] = g;
            imagen[idx + 2] = b;
            imagen[idx + 3] = 255;
        }
    }

    tex->ancho = tamano;
    tex->alto = tamano;
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &tex->idTextura);
    glBindTexture(GL_TEXTURE_2D, tex->idTextura);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tamano, tamano, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, imagen.data());
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    return tex;
}
