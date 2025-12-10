#include <cstdlib>

#include "igvInterfaz.h"

enum MenuOpciones {
    IGV_MENU_MODO_TECLADO = 1,
    IGV_MENU_MODO_RATON,
    IGV_MENU_SOMBREADO_PLANO,
    IGV_MENU_SOMBREADO_SUAVE,
    IGV_MENU_ANIMAR_BRAZO,
    IGV_MENU_ANIMAR_CAMARA,
    IGV_MENU_DETENER_TODO,
    IGV_MENU_SUELO_MATERIAL_1,
    IGV_MENU_SUELO_MATERIAL_2,
    IGV_MENU_SUELO_MATERIAL_3,
    IGV_MENU_SUELO_SIN_TEXTURA,
    IGV_MENU_SUELO_TEXTURA_1,
    IGV_MENU_SUELO_TEXTURA_2,
    IGV_MENU_SUELO_TEXTURA_3,
    IGV_MENU_SALIR
};

igvInterfaz *igvInterfaz::_instancia = nullptr;

igvInterfaz::igvInterfaz() {
    camara.set(igvPunto3D(3.5, 4.0, 10.0),
               igvPunto3D(0.0, 0.0, 0.0),
               igvPunto3D(0.0, 1.0, 0.0));
    modoSeleccion = true;
    escena.activarModoSeleccion(true);
}

igvInterfaz &igvInterfaz::getInstancia() {
    if (!_instancia) {
        _instancia = new igvInterfaz;
    }

    return *_instancia;
}

void igvInterfaz::menuFunc(int option) {
    switch (option) {
        case IGV_MENU_MODO_TECLADO:
            _instancia->modoTransformacionGlobal = false;
            _instancia->modoSeleccion = true;
            _instancia->escena.activarModoSeleccion(true);
            _instancia->arrastrando = false;
            _instancia->camara.desactivarMovimiento();
            printf("Control por teclado activado. Usa las teclas indicadas en la ayuda inicial.\n");
            break;
        case IGV_MENU_MODO_RATON:
            _instancia->modoTransformacionGlobal = false;
            _instancia->modoSeleccion = true;
            _instancia->escena.activarModoSeleccion(true);
            printf("Control por raton activado. Pulsa y arrastra con el boton izquierdo para manipular.\n");
            break;
        case IGV_MENU_SOMBREADO_PLANO:
            _instancia->escena.setModoSombreadoSuave(false);
            printf("Sombreado plano activado.\n");
            break;
        case IGV_MENU_SOMBREADO_SUAVE:
            _instancia->escena.setModoSombreadoSuave(true);
            printf("Sombreado suave (Gouraud) activado.\n");
            break;
        case IGV_MENU_ANIMAR_BRAZO:
            _instancia->animacionModeloActiva = true;
            printf("Animacion del modelo activada.\n");
            break;
        case IGV_MENU_ANIMAR_CAMARA:
            _instancia->orbitaAutomaticaActiva = true;
            printf("Animacion de orbita de la camara activada.\n");
            break;
        case IGV_MENU_DETENER_TODO:
            _instancia->animacionModeloActiva = false;
            _instancia->orbitaAutomaticaActiva = false;
            printf("Animaciones detenidas.\n");
            break;
        case IGV_MENU_SUELO_MATERIAL_1:
            _instancia->escena.cambiarMaterial(0);
            printf("Material 1 aplicado al suelo.\n");
            break;
        case IGV_MENU_SUELO_MATERIAL_2:
            _instancia->escena.cambiarMaterial(1);
            printf("Material 2 aplicado al suelo.\n");
            break;
        case IGV_MENU_SUELO_MATERIAL_3:
            _instancia->escena.cambiarMaterial(2);
            printf("Material 3 aplicado al suelo.\n");
            break;
        case IGV_MENU_SUELO_SIN_TEXTURA:
            _instancia->escena.cambiarTextura(-1);
            printf("Textura del suelo desactivada.\n");
            break;
        case IGV_MENU_SUELO_TEXTURA_1:
            _instancia->escena.cambiarTextura(0);
            printf("Textura 1 aplicada al suelo.\n");
            break;
        case IGV_MENU_SUELO_TEXTURA_2:
            _instancia->escena.cambiarTextura(1);
            printf("Textura 2 aplicada al suelo.\n");
            break;
        case IGV_MENU_SUELO_TEXTURA_3:
            _instancia->escena.cambiarTextura(2);
            printf("Textura ajedrez aplicada al suelo.\n");
            break;
        case IGV_MENU_SALIR:
            exit(0);
    }

    glutPostRedisplay();
}

void igvInterfaz::create_menu() {
    int submenu_control = glutCreateMenu(menuFunc);
    glutAddMenuEntry("Control por Teclado", IGV_MENU_MODO_TECLADO);
    glutAddMenuEntry("Control por Raton", IGV_MENU_MODO_RATON);

    int submenu_sombreado = glutCreateMenu(menuFunc);
    glutAddMenuEntry("Sombreado Plano", IGV_MENU_SOMBREADO_PLANO);
    glutAddMenuEntry("Sombreado Suave (Gouraud)", IGV_MENU_SOMBREADO_SUAVE);

    int submenu_animacion = glutCreateMenu(menuFunc);
    glutAddMenuEntry("Animar Modelo", IGV_MENU_ANIMAR_BRAZO);
    glutAddMenuEntry("Animar Camara", IGV_MENU_ANIMAR_CAMARA);
    glutAddMenuEntry("Detener Todo", IGV_MENU_DETENER_TODO);

    int submenu_material_suelo = glutCreateMenu(menuFunc);
    glutAddMenuEntry("Material 1", IGV_MENU_SUELO_MATERIAL_1);
    glutAddMenuEntry("Material 2", IGV_MENU_SUELO_MATERIAL_2);
    glutAddMenuEntry("Material 3", IGV_MENU_SUELO_MATERIAL_3);

    int submenu_textura_suelo = glutCreateMenu(menuFunc);
    glutAddMenuEntry("Sin textura", IGV_MENU_SUELO_SIN_TEXTURA);
    glutAddMenuEntry("Textura 1", IGV_MENU_SUELO_TEXTURA_1);
    glutAddMenuEntry("Textura 2", IGV_MENU_SUELO_TEXTURA_2);
    glutAddMenuEntry("Tablero de ajedrez", IGV_MENU_SUELO_TEXTURA_3);

    int menu_principal = glutCreateMenu(menuFunc);
    glutAddSubMenu("Modo de control", submenu_control);
    glutAddSubMenu("Sombreado", submenu_sombreado);
    glutAddSubMenu("Animacion", submenu_animacion);
    glutAddSubMenu("Material suelo", submenu_material_suelo);
    glutAddSubMenu("Textura suelo", submenu_textura_suelo);
    glutAddMenuEntry("Salir", IGV_MENU_SALIR);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void igvInterfaz::configura_entorno(int argc, char **argv
                                    , int _ancho_ventana, int _alto_ventana
                                    , int _pos_X, int _pos_Y
                                    , std::string _titulo) {
    ancho_ventana = _ancho_ventana;
    alto_ventana = _alto_ventana;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(_ancho_ventana, _alto_ventana);
    glutInitWindowPosition(_pos_X, _pos_Y);
    glutCreateWindow(_titulo.c_str());


    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0, 1.0, 1.0, 0.0);

    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);

    create_menu();

    mostrarAyudaInicial();
}


void igvInterfaz::inicia_bucle_visualizacion() {
    glutMainLoop();
}

void igvInterfaz::cambiarModoInteraccion() {
    modoTransformacionGlobal = !modoTransformacionGlobal;

    if (modoTransformacionGlobal) {
        printf("Modo transformaciones globales activado: mueve toda la escena con las teclas\n");
        printf("Flechas y U/u para trasladar, X/Y/Z para rotar, S para escalar\n");
        modoSeleccion = false;
        escena.setParteSeleccionada(-1);
        escena.activarModoSeleccion(false);
        arrastrando = false;
        if (camara.getMovimientoActivo()) {
            camara.desactivarMovimiento();
            printf("Modo camara desactivado para permitir las flechas en transformaciones\n");
        }
    } else {
        printf("Modo seleccion activado: elige partes con 1-4 o clic y usa flechas\n");
        modoSeleccion = true;
        escena.activarModoSeleccion(true);
        arrastrando = false;
        if (camara.getMovimientoActivo()) {
            camara.desactivarMovimiento();
            printf("Modo camara desactivado: ahora las flechas actuan sobre la seleccion\n");
        }
    }
}

void igvInterfaz::mostrarAyudaInicial() const {
    printf("====================== INSTRUCCIONES ======================\n");
    printf("M alterna entre modo global y modo de seleccion individual\n");
    printf("Modo global: flechas/U/u trasladan, X/Y/Z rotan, S escala toda la escena\n");
    printf("Modo seleccion: pulsa 1-4 o clic y mueve con flechas o arrastrando\n");
    printf("Camara: C activa control. Flechas orbitan/cabecean, y/Y gira eje propio\n");
    printf("Camara: f/F plano delantero, b/B plano trasero, +/- zoom, p/P proyeccion\n");
    printf("Vistas: v/V cambia panoramica/planta/perfil/alzado. 4 viewports en modo camara\n");
    printf("Ejes: E. Iluminacion y normales: H. Animaciones: A modelo, G orbita camara\n");
    printf("Reset pose lampara: R. Salir: ESC. \n");
    printf("============================================================\n");
}

void igvInterfaz::aplicarIncrementoSeleccionadoHorizontal(float incremento) {
    switch (escena.getParteSeleccionada()) {
        case 0:
            escena.rotarBaseLampara(incremento);
            break;
        case 1:
            escena.rotarBrazo1Lampara(incremento);
            break;
        case 2:
            escena.rotarBrazo2LateralLampara(incremento);
            break;
        case 3:
            escena.rotarPantallaLateralLampara(incremento);
            break;
        default:
            break;
    }
}

void igvInterfaz::aplicarIncrementoSeleccionadoVertical(float incremento) {
    switch (escena.getParteSeleccionada()) {
        case 0:
            escena.rotarBaseLampara(incremento);
            break;
        case 1:
            escena.rotarBrazo1Lampara(incremento);
            break;
        case 2:
            escena.rotarBrazo2Lampara(incremento);
            break;
        case 3:
            escena.rotarPantallaLampara(incremento);
            break;
        default:
            break;
    }
}

void igvInterfaz::aplicarMovimientoRaton(int dx, int dy) {
    if (escena.getParteSeleccionada() == -1) return;

    const float factor = 0.25f;
    switch (escena.getParteSeleccionada()) {
        case 0:
            escena.rotarBaseLampara(dx * factor);
            break;
        case 1:
            escena.rotarBrazo1Lampara(-dy * factor);
            break;
        case 2:
            escena.rotarBrazo2LateralLampara(dx * factor);
            escena.rotarBrazo2Lampara(-dy * factor);
            break;
        case 3:
            escena.rotarPantallaLateralLampara(dx * factor);
            escena.rotarPantallaLampara(-dy * factor);
            break;
        default:
            break;
    }
}

void igvInterfaz::keyboardFunc(unsigned char key, int x, int y) {
    switch (key) {
        case 'e':
        case 'E':
            _instancia->escena.set_ejes(!_instancia->escena.get_ejes());
            break;
        case 'c':
        case 'C':
            _instancia->camara.activarMovimiento();
            if (_instancia->camara.getMovimientoActivo()) {
                printf("Modo camara activado. Usa flechas, y/Y, f/F, b/B, +/-\n");
            } else {
                printf("Modo camara desactivado\n");
            }
            break;
        case 'f':
        case 'F':
            if (_instancia->camara.getMovimientoActivo()) {
                double delta = (key == 'f') ? 0.2 : -0.2;
                _instancia->camara.moverPlanoDelantero(delta);
            }
            break;
        case 'b':
        case 'B':
            if (_instancia->camara.getMovimientoActivo()) {
                double delta = (key == 'b') ? 0.5 : -0.5;
                _instancia->camara.moverPlanoTrasero(delta);
            }
            break;
        case '+':
            if (_instancia->camara.getMovimientoActivo()) {
                _instancia->camara.zoom(10.0);
            } else {
                printf("Activa el modo camara con C para usar el zoom\n");
            }
            break;
        case '-':
            if (_instancia->camara.getMovimientoActivo()) {
                _instancia->camara.zoom(-10.0);
            } else {
                printf("Activa el modo camara con C para usar el zoom\n");
            }
            break;
        case 'p':
        case 'P':
            if (_instancia->camara.getTipo() == IGV_PARALELA)
                _instancia->camara.set(IGV_PERSPECTIVA);
            else _instancia->camara.set(IGV_PARALELA);
            break;
        case 'v':
        case 'V':
            _instancia->camara.siguienteVista();
            break;
        case '4':
            if (_instancia->camara.getMovimientoActivo()) {
                _instancia->cambiaModoMultiViewPort();
                if (_instancia->getModoMultiViewport()) {
                    printf("Viewports activados: panoramica, planta, perfil y alzado\n");
                } else {
                    printf("Viewports desactivados: vuelve a la vista principal\n");
                }
            } else if (!_instancia->modoTransformacionGlobal) {
                _instancia->escena.setParteSeleccionada(3);
                printf("Pantalla seleccionada - Izq/Der giran la pantalla, Arr/Ab inclinan\n");
            }
            break;
        case 'h':
        case 'H':
            _instancia->escena.cambiarModoSombreado();
            _instancia->escena.cambiarUsoNormales();
            break;
        case 'r':
        case 'R':
            _instancia->escena.resetearPoseLampara();
            break;
        case 'm':
        case 'M':
            _instancia->cambiarModoInteraccion();
            break;
        case 'u':
            if (_instancia->modoTransformacionGlobal) {
                _instancia->escena.trasladarY(0.1f);
            }
            break;
        case 'U':
            if (_instancia->modoTransformacionGlobal) {
                _instancia->escena.trasladarY(-0.1f);
            }
            break;
        case 'x':
            if (_instancia->modoTransformacionGlobal) {
                _instancia->escena.rotarEscenaX(5.0f);
            }
            break;
        case 'X':
            if (_instancia->modoTransformacionGlobal) {
                _instancia->escena.rotarEscenaX(-5.0f);
            }
            break;
        case 'y':
            if (_instancia->camara.getMovimientoActivo()) {
                _instancia->camara.rotacionEjeY(5.0);
            } else if (_instancia->modoTransformacionGlobal) {
                _instancia->escena.rotarEscenaY(5.0f);
            }
            break;
        case 'Y':
            if (_instancia->camara.getMovimientoActivo()) {
                _instancia->camara.rotacionEjeY(-5.0);
            } else if (_instancia->modoTransformacionGlobal) {
                _instancia->escena.rotarEscenaY(-5.0f);
            }
            break;
        case 'z':
            if (_instancia->modoTransformacionGlobal) {
                _instancia->escena.rotarEscenaZ(5.0f);
            }
            break;
        case 'Z':
            if (_instancia->modoTransformacionGlobal) {
                _instancia->escena.rotarEscenaZ(-5.0f);
            }
            break;
        case 's':
            if (_instancia->modoTransformacionGlobal) {
                _instancia->escena.escalarEscena(0.05f);
            }
            break;
        case 'S':
            if (_instancia->modoTransformacionGlobal) {
                _instancia->escena.escalarEscena(-0.05f);
            }
            break;
        case 'a':
        case 'A':
            _instancia->animacionModeloActiva = !_instancia->animacionModeloActiva;
            if (_instancia->animacionModeloActiva) {
                printf("Animacion automática del modelo ACTIVADA\n");
            } else {
                printf("Animacion automática del modelo DESACTIVADA\n");
            }
            break;
        case 'g':
        case 'G':
            _instancia->orbitaAutomaticaActiva = !_instancia->orbitaAutomaticaActiva;
            if (_instancia->orbitaAutomaticaActiva) {
                printf("Orbitado automático de la cámara ACTIVADO\n");
            } else {
                printf("Orbitado automático de la cámara DESACTIVADO\n");
            }
            break;
        case '1':
            if (!_instancia->modoTransformacionGlobal) {
                _instancia->escena.setParteSeleccionada(0);
                if (_instancia->camara.getMovimientoActivo()) {
                    _instancia->camara.desactivarMovimiento();
                    printf("Modo camara desactivado: flechas reasignadas a la parte elegida\n");
                }
                printf("Base seleccionada - Usa las flechas para rotar\n");
            }
            break;
        case '2':
            if (!_instancia->modoTransformacionGlobal) {
                _instancia->escena.setParteSeleccionada(1);
                if (_instancia->camara.getMovimientoActivo()) {
                    _instancia->camara.desactivarMovimiento();
                    printf("Modo camara desactivado: flechas reasignadas a la parte elegida\n");
                }
                printf("Brazo 1 seleccionado - Usa las flechas para rotar\n");
            }
            break;

        case 'd': // Apartado E: aumentar en 0.1 la componente R del coeficiente difuso del material
            _instancia->escena.getMaterial()->incrementarRDifuso(0.1);
            break;
        case 'D': // Apartado E: disminuir en 0.1 la componente R del coeficiente difuso del material
            _instancia->escena.getMaterial()->incrementarRDifuso(-0.1);
            break;
        // case 's': // Apartado E: aumentar en 0.1 la componente R del coeficiente especular del material
        //     _instancia->escena.getMaterial()->incrementarREspecular(0.1);
        //     break;
        // case 'S': // Apartado E: disminuir en 0.1 la componente R del coeficiente especular del material
        //     _instancia->escena.getMaterial()->incrementarREspecular(-0.1);
        //     break;
        // case 'p': // Apartado E: aumentar en 10 el exponente de Phong del material
        //     _instancia->escena.getMaterial()->incrementarExpPhong(10);
        //     break;
        // case 'P': // Apartado E: disminuir en 10 el exponente de Phong del material
        //     _instancia->escena.getMaterial()->incrementarExpPhong(-10);
        //     break;
        // case 'e': // activa/desactiva la visualizaci�n de los ejes
        //     _instancia->escena.set_ejes(!_instancia->escena.get_ejes());
        //     break;
        case '3':
            if (!_instancia->modoTransformacionGlobal) {
                _instancia->escena.setParteSeleccionada(2);
                if (_instancia->camara.getMovimientoActivo()) {
                    _instancia->camara.desactivarMovimiento();
                    printf("Modo camara desactivado: flechas reasignadas a la parte elegida\n");
                }
                printf("Brazo 2 seleccionado - Izq/Der giran lateralmente, Arr/Ab inclinan\n");
            }
            break;
        case 27:
            exit(1);
    }
    glutPostRedisplay();
}

void igvInterfaz::specialFunc(int key, int x, int y) {
    bool camaraActiva = _instancia->camara.getMovimientoActivo();
    bool modoGlobal = _instancia->modoTransformacionGlobal;
    bool hayParteSeleccionada = _instancia->escena.getParteSeleccionada() != -1;
    int modoMovimientoLuz = _instancia->escena.getModoMovimientoLuz();

    igvFuenteLuz* luzSeleccionada = nullptr;
    if (modoMovimientoLuz == 1) {
        luzSeleccionada = _instancia->escena.getLuzPuntual();
    } else if (modoMovimientoLuz == 2) {
        luzSeleccionada = _instancia->escena.getLuzSpotlight();
    }

    if (!modoGlobal && hayParteSeleccionada && camaraActiva) {
        _instancia->camara.desactivarMovimiento();
        camaraActiva = false;
        printf("Modo camara desactivado: las flechas ahora mueven la parte seleccionada\n");
    }

    if (luzSeleccionada != nullptr) {
        switch (key) {
            case GLUT_KEY_DOWN:
                luzSeleccionada->mover(0.0f, -0.2f, 0.0f);
                break;
            case GLUT_KEY_UP:
                luzSeleccionada->mover(0.0f, 0.2f, 0.0f);
                break;
            case GLUT_KEY_RIGHT:
                luzSeleccionada->mover(0.2f, 0.0f, 0.0f);
                break;
            case GLUT_KEY_LEFT:
                luzSeleccionada->mover(-0.2f, 0.0f, 0.0f);
                break;
        }

        glutPostRedisplay();
        return;
    }

    switch (key) {
        case GLUT_KEY_LEFT:
            if (camaraActiva) {
                _instancia->camara.orbita(-5.0);
            } else if (modoGlobal) {
                _instancia->escena.trasladarX(0.1f);
            } else if (hayParteSeleccionada) {
                _instancia->aplicarIncrementoSeleccionadoHorizontal(-5.0f);
            }
            break;
        case GLUT_KEY_RIGHT:
            if (camaraActiva) {
                _instancia->camara.orbita(5.0);
            } else if (modoGlobal) {
                _instancia->escena.trasladarX(-0.1f);
            } else if (hayParteSeleccionada) {
                _instancia->aplicarIncrementoSeleccionadoHorizontal(5.0f);
            }
            break;
        case GLUT_KEY_UP:
            if (camaraActiva) {
                _instancia->camara.cabeceo(5.0);
            } else if (modoGlobal) {
                _instancia->escena.trasladarZ(0.1f);
            } else if (hayParteSeleccionada) {
                _instancia->aplicarIncrementoSeleccionadoVertical(5.0f);
            }
            break;
        case GLUT_KEY_DOWN:
            if (camaraActiva) {
                _instancia->camara.cabeceo(-5.0);
            } else if (modoGlobal) {
                _instancia->escena.trasladarZ(-0.1f);
            } else if (hayParteSeleccionada) {
                _instancia->aplicarIncrementoSeleccionadoVertical(-5.0f);
            }
            break;
    }

    glutPostRedisplay();
}

void igvInterfaz::reshapeFunc(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    _instancia->set_ancho_ventana(w);
    _instancia->set_alto_ventana(h);
    if (h != 0) {
        double aspecto = static_cast<double>(w) / static_cast<double>(h);
        _instancia->camara.setAspecto(aspecto);
    }
    _instancia->camara.aplicar();
}

void igvInterfaz::mouseFunc(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (_instancia->modoTransformacionGlobal) {
            printf("El modo global esta activo. Pulsa M para volver a seleccionar partes.\n");
            return;
        }

        if (_instancia->camara.getMovimientoActivo()) {
            _instancia->camara.desactivarMovimiento();
            printf("Modo camara desactivado: flechas dedicadas a la parte seleccionada\n");
        }

        _instancia->escena.seleccionarParte(x, y, _instancia->alto_ventana);
        int parte = _instancia->escena.getParteSeleccionada();
        switch(parte) {
            case 0:
                printf("Base seleccionada - Arrastra o usa las flechas para rotar\n");
                _instancia->arrastrando = true;
                break;
            case 1:
                printf("Brazo 1 seleccionado - Arrastra o usa las flechas para rotar\n");
                _instancia->arrastrando = true;
                break;
            case 2:
                printf("Brazo 2 seleccionado - Arrastra para girar/inclinar o usa las flechas\n");
                _instancia->arrastrando = true;
                break;
            case 3:
                printf("Pantalla seleccionada - Arrastra para girar/inclinar o usa las flechas\n");
                _instancia->arrastrando = true;
                break;
            default:
                printf("No se selecciono ninguna parte - Haz clic en la lámpara\n");
                _instancia->arrastrando = false;
                break;
        }

        _instancia->ultimoX = x;
        _instancia->ultimoY = y;

        glutPostRedisplay();
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        _instancia->arrastrando = false;
    }
}

void igvInterfaz::motionFunc(int x, int y) {
    if (!_instancia->modoSeleccion || !_instancia->arrastrando) return;

    int dx = x - _instancia->ultimoX;
    int dy = y - _instancia->ultimoY;

    _instancia->aplicarMovimientoRaton(dx, dy);

    _instancia->ultimoX = x;
    _instancia->ultimoY = y;

    glutPostRedisplay();
}

void igvInterfaz::displayFunc() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (_instancia->modoMultiViewport) {
        for (int i = 0; i < 4; i++) {
            _instancia->camara.aplicarViewport(i,
                                               _instancia->ancho_ventana,
                                               _instancia->alto_ventana);

            _instancia->escena.visualizar();
        }
    } else {
        glViewport(0, 0, _instancia->ancho_ventana, _instancia->alto_ventana);
        _instancia->camara.aplicar();
        _instancia->escena.visualizar();
    }

    glutSwapBuffers();
}

void igvInterfaz::timerFunc(int value) {
    if (_instancia->animacionModeloActiva) {
        //_instancia->escena.rotarBaseLampara(1.0f);
        _instancia->camara.orbita(0.3);
        _instancia->escena.getModelo().animarContinuo();
        //_instancia->camara.cabeceo(0.2);

    }

    if (_instancia->orbitaAutomaticaActiva) {
        _instancia->camara.orbita(0.5);
    }

    if (_instancia->animacionModeloActiva || _instancia->orbitaAutomaticaActiva) {
        glutPostRedisplay();
    }

    glutTimerFunc(_instancia->timerAnimacion, timerFunc, 0);
}

void igvInterfaz::inicializa_callbacks() {
    glutKeyboardFunc(keyboardFunc);
    glutSpecialFunc(specialFunc);
    glutReshapeFunc(reshapeFunc);
    glutDisplayFunc(displayFunc);
    glutMouseFunc(mouseFunc);
    glutMotionFunc(motionFunc);
    glutTimerFunc(16, timerFunc, 0);
}

int igvInterfaz::get_ancho_ventana() {
    return ancho_ventana;
}

int igvInterfaz::get_alto_ventana() {
    return alto_ventana;
}

void igvInterfaz::set_ancho_ventana(int _ancho_ventana) {
    ancho_ventana = _ancho_ventana;
}

void igvInterfaz::set_alto_ventana(int _alto_ventana) {
    alto_ventana = _alto_ventana;
}