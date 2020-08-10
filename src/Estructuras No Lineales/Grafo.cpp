#include "Grafo.h"

const int E_INFINITO = 999999;
const float F_INFINITO = 999998.9;
const string NULO = "---";

Grafo::Grafo() {
    this->elementos = 0;
    this->precioMatriz = new Matriz<int>;
    this->tiempoMatriz = new Matriz<float>;
    this->vertices = new Lista<string>;
    precioMatriz->asignarInicializador(E_INFINITO);
    tiempoMatriz->asignarInicializador(F_INFINITO);
}

Grafo::Grafo(Matriz<int> *precio, Matriz<float> *tiempo, int elementos, Lista<string> *vertices) {
    this->tiempoMatriz = tiempo;
    this->elementos = vertices->obtenerTam();
    this->precioMatriz = precio;
    this->vertices = vertices;
}

Grafo::~Grafo() {
    delete precioMatriz;
    delete tiempoMatriz;
    delete vertices;
}

bool Grafo::existeArista(string origen, string destino) {
    bool existe = false;
    if (existeVertice(origen) && existeVertice(destino)) {
        int posicionOrigen = vertices->obtenerPosicion(origen);
        int posicionDestino = vertices->obtenerPosicion(destino);
        if ((tiempoMatriz->obtenerValor(posicionOrigen, posicionDestino) < E_INFINITO) &&
            (precioMatriz->obtenerValor(posicionOrigen, posicionDestino) < F_INFINITO))
            existe = true;
    }
    return existe;
}

bool Grafo::existeVertice(string vertice) {
    bool existe = false;
    if (vertices->obtenerPosicion(vertice) != -1)
        existe = true;
    return  existe;
}

float Grafo::obtenerTiempo(string origen, string destino) {
    float tiempo = F_INFINITO;
    if(existeArista(origen,destino))
        tiempo = tiempoMatriz->obtenerValor(vertices->obtenerPosicion(origen),vertices->obtenerPosicion(destino));
    return tiempo;
}

int Grafo::obtenerPrecio(string origen, string destino) {
    int precio = E_INFINITO;
    if(existeArista(origen,destino))
        precio = precioMatriz->obtenerValor(vertices->obtenerPosicion(origen),vertices->obtenerPosicion(destino));
    return precio;
}

void Grafo::insertarArista(string origen, string destino, int precio, float tiempo) {
    int posicionDestino;
    int posicionOrigen;

    if(!existeArista(origen,destino)) {

        if(existeVertice(origen) && existeVertice(destino)) {
            posicionOrigen= vertices->obtenerPosicion(origen);
            posicionDestino = vertices->obtenerPosicion(destino);
            precioMatriz->modificarElemento(precio, posicionOrigen, posicionDestino);
            tiempoMatriz->modificarElemento(tiempo, posicionOrigen, posicionDestino);
        }

        else if(existeVertice(origen)) {
            precioMatriz->agregarFilasColumnas(1,1);
            tiempoMatriz->agregarFilasColumnas(1,1);
            vertices->insertar(destino);
            posicionOrigen= vertices->obtenerPosicion(origen);
            posicionDestino = vertices->obtenerPosicion(destino);
            precioMatriz->modificarElemento(precio, posicionOrigen, posicionDestino);
            tiempoMatriz->modificarElemento(tiempo, posicionOrigen, posicionDestino);
            elementos ++;
        }

        else if (existeVertice(destino)) {
            precioMatriz->agregarFilasColumnas(1,1);
            tiempoMatriz->agregarFilasColumnas(1,1);
            vertices->insertar(origen);
            posicionOrigen= vertices->obtenerPosicion(origen);
            posicionDestino = vertices->obtenerPosicion(destino);
            precioMatriz->modificarElemento(precio, posicionOrigen, posicionDestino);
            tiempoMatriz->modificarElemento(tiempo, posicionOrigen, posicionDestino);
            elementos ++;
        }

        else {
            precioMatriz->agregarFilasColumnas(2,2);
            tiempoMatriz->agregarFilasColumnas(2,2);
            vertices->insertar(origen);
            vertices->insertar(destino);
            posicionOrigen= vertices->obtenerPosicion(origen);
            posicionDestino = vertices->obtenerPosicion(destino);
            precioMatriz->modificarElemento(precio, posicionOrigen, posicionDestino);
            tiempoMatriz->modificarElemento(tiempo, posicionOrigen, posicionDestino);
            elementos += 2;
        }
    }
    else
        cout<<"\n\tYa existe una ruta que conecta " << origen << " con " << destino;
}

void Grafo::mostrarCaminosMinimos(string origen, string destino, CaminoMinimoPrecio minPrecio, Diccionario<string, Aeropuerto*> *&aeropuertos) {

    int posOrigen = vertices->obtenerPosicion(origen);
    int posDestino = vertices->obtenerPosicion(destino);

    cout << "\n\tOrigen:";
    if (aeropuertos->existe(origen))
        cout << *aeropuertos->obtenerValor(origen);
    else
        cout << "\n\t" << origen;
    cout << "\n\tDestino:";
    if (aeropuertos->existe(destino))
        cout << *aeropuertos->obtenerValor(destino);
    else
        cout << "\n\t" << destino;

    cout << "\n\tPrecio Minimo:\t$ " << minPrecio.precios->obtenerValor(posOrigen, posDestino);
    cout << "\n\tCon escalas en:\n";
    int i = 1;
    while (minPrecio.rutas->obtenerValor(posOrigen, posDestino) != destino) {
        string escala = minPrecio.rutas->obtenerValor(posOrigen, posDestino);
        cout << "\n\t" << i << ".";
        if (aeropuertos->existe(escala))
            cout << *aeropuertos->obtenerValor(escala);
        else
            cout << "\n\t" << escala;
        posOrigen = vertices->obtenerPosicion(minPrecio.rutas->obtenerValor(posOrigen, posDestino));
        i++;
    }
}

void Grafo::mostrarCaminosMinimos(string origen, string destino, CaminoMinimoTiempo minTiempo, Diccionario<string, Aeropuerto*> *&aeropuertos) {

    int posOrigen = vertices->obtenerPosicion(origen);
    int posDestino = vertices->obtenerPosicion(destino);

    cout << "\n\tOrigen:";
    if (aeropuertos->existe(origen))
        cout << *aeropuertos->obtenerValor(origen);
    else
        cout << "\n\t" << origen;
    cout << "\n\tDestino:";
    if (aeropuertos->existe(destino))
        cout << *aeropuertos->obtenerValor(destino);
    else
        cout << "\n\t" << destino;

    cout << "\n\tTiempo Minimo:\t" << minTiempo.tiempos->obtenerValor(posOrigen, posDestino);
    cout << "hs\n\tCon escalas en:\n";
    int i = 1;
    while (minTiempo.rutas->obtenerValor(posOrigen, posDestino) != destino) {
        string escala = minTiempo.rutas->obtenerValor(posOrigen, posDestino);
        cout << "\n\t" << i << ".";
        if (aeropuertos->existe(escala))
            cout << *aeropuertos->obtenerValor(escala);
        else
            cout << "\n\t" << escala;
        posOrigen = vertices->obtenerPosicion(minTiempo.rutas->obtenerValor(posOrigen, posDestino));
        i++;
    }
}

CaminoMinimoPrecio Grafo::inicializarMatricesPrecio() {

    CaminoMinimoPrecio inicializado;
    if (!inicializado.calculado) {
        inicializado.precios = new Matriz<int>(precioMatriz->obtenerInicializador(), elementos, elementos);
        inicializado.rutas = new Matriz<string>(NULO, elementos, elementos);
        inicializado.calculado = true;
    }
    else {
        delete inicializado.precios;
        delete inicializado.rutas;
        inicializado.precios = new Matriz<int>(precioMatriz->obtenerInicializador(), elementos, elementos);
        inicializado.rutas = new Matriz<string>(NULO, elementos, elementos);
    }
    for (int i = 0; i < elementos; i++) {
        for (int j = 0; j < elementos; j++) {
            if (i != j) {
                inicializado.precios->modificarElemento(precioMatriz->obtenerValor(i,j), i, j);
                inicializado.rutas->modificarElemento(vertices->obtenerDato(i), j, i);
            }
        }
    }
    return inicializado;
}

CaminoMinimoTiempo Grafo::inicializarMatricesTiempo() {

    CaminoMinimoTiempo inicializado;
    if (!inicializado.calculado) {
        inicializado.tiempos = new Matriz<float>(tiempoMatriz->obtenerInicializador(), elementos, elementos);
        inicializado.rutas = new Matriz<string>(NULO, elementos, elementos);
        inicializado.calculado = true;
    }
    else {
        delete inicializado.tiempos;
        delete inicializado.rutas;
        inicializado.tiempos = new Matriz<float>(tiempoMatriz->obtenerInicializador(), elementos, elementos);
        inicializado.rutas = new Matriz<string>(NULO, elementos, elementos);
    }

    for (int i = 0; i < elementos; i++) {
        for (int j = 0; j < elementos; j++) {
            if (i != j) {
                inicializado.tiempos->modificarElemento(tiempoMatriz->obtenerValor(i, j), i, j);
                inicializado.rutas->modificarElemento(vertices->obtenerDato(i), j, i);
            }
        }
    }
    return inicializado;
}

CaminoMinimoPrecio Grafo::caminoMinimoPrecio() {

    CaminoMinimoPrecio minPrecio = inicializarMatricesPrecio();

    for(int k = 0; k < elementos; k++) {
        for (int i = 0; i < elementos; i++) {
            for (int j = 0; j < elementos; j++) {
                int precioMin = minPrecio.precios->obtenerValor(i, k) + minPrecio.precios->obtenerValor(k, j);
                if (i != j && precioMin < minPrecio.precios->obtenerValor(i, j)) {
                    minPrecio.precios->modificarElemento(precioMin, i, j);
                    minPrecio.rutas->modificarElemento(vertices->obtenerDato(k), i, j);
                }
                else if (i != j && precioMin == minPrecio.precios->obtenerValor(i, j) && precioMin < E_INFINITO) {
                    // TODO: Guardar esta posibilidad en algun lado
                }
            }
        }
    }
    return minPrecio;
}

CaminoMinimoTiempo Grafo::caminoMinimoTiempo() {

    CaminoMinimoTiempo minTiempo = inicializarMatricesTiempo();

    for(int k = 0; k < elementos; k++) {
        for (int i = 0; i < elementos; i++) {
            for (int j = 0; j < elementos; j++) {
                float tiempoMin = minTiempo.tiempos->obtenerValor(i, k) + minTiempo.tiempos->obtenerValor(k, j);
                if (i != j && tiempoMin < minTiempo.tiempos->obtenerValor(i, j)) {
                    minTiempo.tiempos->modificarElemento(tiempoMin, i, j);
                    minTiempo.rutas->modificarElemento(vertices->obtenerDato(k), i, j);
                }
                else if (i != j && tiempoMin == minTiempo.tiempos->obtenerValor(i, j) && tiempoMin < F_INFINITO) {
                    // TODO: Guardar esta posibilidad en algun lado
                }
            }
        }
    }
    return minTiempo;
}
