//Nombre: Alvaro, Apellidos: Luna Ramirez, Titulacion: GIM, correo: alvaroluna@correo.ugr.es, DNI: 
// *********************************************************************

#ifndef IG_LATAPEONES_H
#define IG_LATAPEONES_H

#include "malla-revol.h"
#include "grafo-escena.h"
#include "malla-ind.h"

class LataPeones : public NodoGrafoEscena
{
    public:
        LataPeones();
};

class Peon : public NodoGrafoEscena
{
    public:
        Peon();
};

class Lata : public NodoGrafoEscena
{
    public:
        Lata(std::string nombre_archivo);
};

class VariasLatasPeones : public NodoGrafoEscena
{
    public:
        VariasLatasPeones();
};

#endif


