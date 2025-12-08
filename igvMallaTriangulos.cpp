#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <fstream>
#include <sstream>

#include "igvMallaTriangulos.h"


igvMallaTriangulos::igvMallaTriangulos(long int _num_vertices, float *_vertices
                                       , long int _num_triangulos
                                       , unsigned int *_triangulos) : num_vertices(_num_vertices)
                                                                      , num_triangulos(_num_triangulos) {
    num_vertices = _num_vertices;
    vertices = new float[num_vertices * 3];
    for (long int i = 0; i < (num_vertices * 3); ++i) {
        vertices[i] = _vertices[i];
    }

    normales = nullptr;

    num_triangulos = _num_triangulos;
    triangulos = new unsigned int[num_triangulos * 3];
    for (long int i = 0; i < (num_triangulos * 3); ++i) {
        triangulos[i] = _triangulos[i];
    }
}

igvMallaTriangulos::igvMallaTriangulos(const std::string &rutaOBJ) {
    cargarOBJ(rutaOBJ);
}

igvMallaTriangulos::~igvMallaTriangulos() {
    if (vertices) {
        delete []vertices;
        vertices = nullptr;
    }

    if (normales) {
        delete []normales;
        normales = nullptr;
    }

    if (triangulos) {
        delete []triangulos;
        triangulos = nullptr;
    }
}

void igvMallaTriangulos::visualizar() {
    if (!gouraud) {
        glShadeModel(GL_FLAT);
    } else {
        glShadeModel(GL_SMOOTH);
    }

    glEnable(GL_NORMALIZE);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    if (usarnormales) {
        if (!normales_calculadas) {
            calcularNormalesVertices();
        }
        glEnableClientState(GL_NORMAL_ARRAY);
        glNormalPointer(GL_FLOAT, 0, normales);
    }

    glDrawElements(GL_TRIANGLES, num_triangulos * 3, GL_UNSIGNED_INT, triangulos);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

void igvMallaTriangulos::calcularNormalesVertices() {
    if (!normales) {
        normales = new float[num_vertices * 3];
    }
    for (long int i = 0; i < num_vertices * 3; i++) {
        normales[i] = 0.0f;
    }
    for (long int t = 0; t < num_triangulos; t++) {
        unsigned int i0 = triangulos[t * 3 + 0];
        unsigned int i1 = triangulos[t * 3 + 1];
        unsigned int i2 = triangulos[t * 3 + 2];
        float v1x = vertices[i1 * 3 + 0] - vertices[i0 * 3 + 0];
        float v1y = vertices[i1 * 3 + 1] - vertices[i0 * 3 + 1];
        float v1z = vertices[i1 * 3 + 2] - vertices[i0 * 3 + 2];
        float v2x = vertices[i2 * 3 + 0] - vertices[i0 * 3 + 0];
        float v2y = vertices[i2 * 3 + 1] - vertices[i0 * 3 + 1];
        float v2z = vertices[i2 * 3 + 2] - vertices[i0 * 3 + 2];
        float nx = v1y * v2z - v1z * v2y;
        float ny = v1z * v2x - v1x * v2z;
        float nz = v1x * v2y - v1y * v2x;
        normales[i0 * 3 + 0] += nx;
        normales[i0 * 3 + 1] += ny;
        normales[i0 * 3 + 2] += nz;
        normales[i1 * 3 + 0] += nx;
        normales[i1 * 3 + 1] += ny;
        normales[i1 * 3 + 2] += nz;
        normales[i2 * 3 + 0] += nx;
        normales[i2 * 3 + 1] += ny;
        normales[i2 * 3 + 2] += nz;
    }
    for (long int v = 0; v < num_vertices; v++) {
        float nx = normales[v * 3 + 0];
        float ny = normales[v * 3 + 1];
        float nz = normales[v * 3 + 2];
        float longitud = std::sqrt(nx * nx + ny * ny + nz * nz);
        if (longitud > 0.0f) {
            normales[v * 3 + 0] = nx / longitud;
            normales[v * 3 + 1] = ny / longitud;
            normales[v * 3 + 2] = nz / longitud;
        }
    }
    normales_calculadas = true;
}

bool igvMallaTriangulos::cargarOBJ(const std::string &rutaOBJ) {
    std::ifstream archivo(rutaOBJ);
    if (!archivo.is_open()) {
        fprintf(stderr, "No se pudo abrir el archivo OBJ: %s\n", rutaOBJ.c_str());
        return false;
    }

    std::vector<float> v;
    std::vector<float> vn;
    std::vector<unsigned int> f_indices;
    std::vector<unsigned int> fn_indices;

    std::string linea;
    while (std::getline(archivo, linea)) {
        std::istringstream iss(linea);
        std::string tipo;
        iss >> tipo;
        if (tipo == "v") {
            float x, y, z;
            if (iss >> x >> y >> z) {
                v.push_back(x);
                v.push_back(y);
                v.push_back(z);
            }
        } else if (tipo == "vn") {
            float nx, ny, nz;
            if (iss >> nx >> ny >> nz) {
                vn.push_back(nx);
                vn.push_back(ny);
                vn.push_back(nz);
            }
        } else if (tipo == "f") {
            std::string vertice;
            std::vector<unsigned int> face_vertices;
            std::vector<unsigned int> face_normales;
            while (iss >> vertice) {
                size_t pos1 = vertice.find('/');
                size_t pos2 = vertice.find('/', pos1 == std::string::npos ? 0 : pos1 + 1);

                if (pos1 == std::string::npos) {
                    // Formato: v
                    face_vertices.push_back(static_cast<unsigned int>(std::stoul(vertice)) - 1);
                } else if (pos2 == std::string::npos) {
                    // Formato: v/vt
                    face_vertices.push_back(static_cast<unsigned int>(std::stoul(vertice.substr(0, pos1))) - 1);
                } else {
                    // Formato: v//vn o v/vt/vn
                    face_vertices.push_back(static_cast<unsigned int>(std::stoul(vertice.substr(0, pos1))) - 1);
                    std::string normal_part = vertice.substr(pos2 + 1);
                    if (!normal_part.empty()) {
                        face_normales.push_back(static_cast<unsigned int>(std::stoul(normal_part)) - 1);
                    }
                }
            }

            if (face_vertices.size() == 3) {
                f_indices.insert(f_indices.end(), face_vertices.begin(), face_vertices.end());
                if (face_normales.size() == 3) {
                    fn_indices.insert(fn_indices.end(), face_normales.begin(), face_normales.end());
                }
            }
        }
    }

    // Liberar datos anteriores si existían
    delete [] vertices; vertices = nullptr;
    delete [] triangulos; triangulos = nullptr;
    delete [] normales; normales = nullptr;

    num_vertices = static_cast<long int>(v.size() / 3);
    num_triangulos = static_cast<long int>(f_indices.size() / 3);

    if (num_vertices == 0 || num_triangulos == 0) {
        fprintf(stderr, "El archivo OBJ no contiene datos validos\n");
        return false;
    }

    vertices = new float[num_vertices * 3];
    for (long int i = 0; i < num_vertices * 3; ++i) {
        vertices[i] = v[static_cast<size_t>(i)];
    }

    triangulos = new unsigned int[num_triangulos * 3];
    for (long int i = 0; i < num_triangulos * 3; ++i) {
        triangulos[i] = f_indices[static_cast<size_t>(i)];
    }

    if (!fn_indices.empty() && fn_indices.size() == static_cast<size_t>(num_triangulos * 3)) {
        normales = new float[num_vertices * 3];
        for (long int i = 0; i < num_vertices * 3; ++i) {
            normales[i] = 0.0f;
        }
        for (long int f = 0; f < num_triangulos; ++f) {
            unsigned int v0 = f_indices[f * 3 + 0];
            unsigned int v1 = f_indices[f * 3 + 1];
            unsigned int v2 = f_indices[f * 3 + 2];
            unsigned int n0 = fn_indices[f * 3 + 0];
            unsigned int n1 = fn_indices[f * 3 + 1];
            unsigned int n2 = fn_indices[f * 3 + 2];
            if ((n0 * 3 + 2) < vn.size()) {
                normales[v0 * 3 + 0] = vn[n0 * 3 + 0];
                normales[v0 * 3 + 1] = vn[n0 * 3 + 1];
                normales[v0 * 3 + 2] = vn[n0 * 3 + 2];
            }
            if ((n1 * 3 + 2) < vn.size()) {
                normales[v1 * 3 + 0] = vn[n1 * 3 + 0];
                normales[v1 * 3 + 1] = vn[n1 * 3 + 1];
                normales[v1 * 3 + 2] = vn[n1 * 3 + 2];
            }
            if ((n2 * 3 + 2) < vn.size()) {
                normales[v2 * 3 + 0] = vn[n2 * 3 + 0];
                normales[v2 * 3 + 1] = vn[n2 * 3 + 1];
                normales[v2 * 3 + 2] = vn[n2 * 3 + 2];
            }
        }
        normales_calculadas = true;
    } else {
        normales_calculadas = false;
    }

    return true;
}
