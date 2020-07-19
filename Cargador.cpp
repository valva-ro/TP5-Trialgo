Cargador::Cargador()
{

}

void Cargador::cargadorDeABB(ABB<Diccionario> &arbolAeropuertos , ifstream archivo)
{
    //char[3] o string ?
    string nombre ,ciudad ,pais,codigoIATA ;
    double superficie;
    int cantidadTerminales,destinosNacionales,destinosInternacionales ;


    if(!archivo.fail())
    {
        while(!archivo.eof())
        {
            //Puntero a los datos del aeropuerto
            Aeropuerto *pAeropuerto ;

            archivo >> codigoIATA;
            archivo >> nombre;
            archivo >> ciudad;
            archivo >> pais;
            archivo >> superficie;
            archivo >> cantidadTerminales;
            archivo >> destinosNacionales;
            archivo >> destinosInternacionales;

            pAeropuerto = new Aeropuerto(nombre,ciudad,pais,superficie,cantidadTerminales,destinosNacionales,destinosInternacionales);

            //Creo un diccionario y le paso por parametro el puntero y la clave del codigo
            Diccionario dicAeropuerto(codigoIATA,pAeropuerto);

            /
            Nodo<Diccionario> nodo(dicAeropuerto);

            //Inserto el nodo en el arbol
            arbolAeropuertos.insertar(nodo);
        }
        cout << "Se han cargado los Aeropuertos en el arbol correctamente " << endl;

    }
    else{
        //Deberiamos throw the exception
        cout << "No se ha podido abrir el archivo! " << endl;
    }
    archivo.close();

}
