#include<iostream>
#include "Cargador.h"

    /// METODOS PRIVADOS ///

void Cargador::cargarDatos(ABB<string clave,Aeropuerto*> &arbolAeropuertos, string ruta)
{
    ifstream archivo;
    archivo.open(ruta.c_str(),ios::in);

    try {
        if (archivo.fail())
            throw (Excepcion(EXCEPCION_ABB));

        cargadorDeABB(arbolAeropuertos, archivo);
        cout << "\n\tSe han cargado los Aeropuertos en el arbol correctamente\n";
    }
    catch(Excepcion &e) {
        cout << e.what() << endl;
    }

    archivo.close();
}
/*
void Cargador::cargarDatos(Grafo<Vuelo*> &grafoVuelos, string ruta)
{
    ifstream archivo;
    archivo.open(ruta.c_str(),ios::in);

    try {
        if (archivo.fail())
            throw (Excepcion(EXCEPCION_GRAFO));

        cargadorDeGrafo(grafoVuelos, archivo);
        cout << "\n\tSe han cargado los vuelos en el arbol correctamente\n";
    }

    catch(Excepcion &e) {
        cout << e.what() << endl;
    }

    archivo.close();
}
*/
    /// METODOS PUBLICOS ///

void Cargador::cargadorDeABB(ABB<string clave,Aeropuerto*> &arbolAeropuertos, ifstream& archivo)
{
    string nombre, ciudad, pais, codigoIATA;
    double superficie;
    int cantidadTerminales, destinosNacionales, destinosInternacionales;

    Aeropuerto *pAeropuerto;

    while(!archivo.eof()) {

        archivo >> codigoIATA;
        archivo >> nombre;
        archivo >> ciudad;
        archivo >> pais;
        archivo >> superficie;
        archivo >> cantidadTerminales;
        archivo >> destinosNacionales;
        archivo >> destinosInternacionales;

        pAeropuerto = new Aeropuerto(codigoIATA, nombre, ciudad,
                                     pais, superficie, cantidadTerminales,
                                     destinosNacionales, destinosInternacionales);


        arbolAeropuertos.insertar(codigoIATA,pAeropuerto);
    }

}
/*
void Cargador:: cargadorDeGrafo(int &grafo, ifstream &archivo) {
    //TODO
}
*/
