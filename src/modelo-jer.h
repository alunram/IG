// Práctica 3
// *********************************************************************
// **
// ** Modelo jerárquico (declaraciones)
// ** Copyright (C) 2022 Álvaro Luna Ramírez
// **
// ** This program is free software: you can redistribute it and/or modify
// ** it under the terms of the GNU General Public License as published by
// ** the Free Software Foundation, either version 3 of the License, or
// ** (at your option) any later version.
// **
// ** This program is distributed in the hope that it will be useful,
// ** but WITHOUT ANY WARRANTY; without even the implied warranty of
// ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// ** GNU General Public License for more details.
// **
// ** You should have received a copy of the GNU General Public License
// ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// **
// *********************************************************************


#ifndef IG_MODELO_JER_H
#define IG_MODELO_JER_H

#include "malla-revol.h"
#include "grafo-escena.h"
#include "malla-ind.h"

class HorquillaTrasera : public NodoGrafoEscena
{
    public:
        HorquillaTrasera();
};

class HorquillaDelantera : public NodoGrafoEscena
{
    public:
        HorquillaDelantera();
};

class ParteBajaHorquilla : public NodoGrafoEscena
{
    public:
        ParteBajaHorquilla();
};

class CuadroParteVertical : public NodoGrafoEscena
{
    public:
        CuadroParteVertical();
};

class CuadroParteBaja : public NodoGrafoEscena
{
    public:
        CuadroParteBaja();
};

class CuadroParteAlta : public NodoGrafoEscena
{
    public:
        CuadroParteAlta();
};

class Tija : public NodoGrafoEscena
{
    public:
        Tija();
};

class Potencia : public NodoGrafoEscena
{
    public:
        Potencia();
};

class Manillar : public NodoGrafoEscena
{
    public:
        Manillar();
};

class Sillin : public NodoGrafoEscena
{
    public:
        Sillin();
};

class BielaDerecha : public NodoGrafoEscena
{
    protected:
        unsigned int parametro = 1;
        Matriz4f * girobd = nullptr;

    public:
        BielaDerecha();
        virtual unsigned leerNumParametros() const;
        virtual void actualizarEstadoParametro(const unsigned iParam, const float tSec);
};

class BielaIzquierda : public NodoGrafoEscena
{
    protected:
        unsigned int parametro = 1;
        Matriz4f * girobi = nullptr;

    public:
        BielaIzquierda();
        virtual unsigned leerNumParametros() const;
        virtual void actualizarEstadoParametro(const unsigned iParam, const float tSec);
};

class PedalDerecho : public NodoGrafoEscena
{
    protected:
        unsigned int parametro = 1;
        BielaDerecha *bd = new BielaDerecha();

    public:
        PedalDerecho();
        virtual unsigned leerNumParametros() const;
        virtual void actualizarEstadoParametro(const unsigned iParam, const float tSec);
};

class PedalIzquierdo : public NodoGrafoEscena
{
    protected:
        unsigned int parametro = 1;
        BielaIzquierda *bi = new BielaIzquierda();

    public:
        PedalIzquierdo();
        virtual unsigned leerNumParametros() const;
        virtual void actualizarEstadoParametro(const unsigned iParam, const float tSec);

};

class RuedaDelantera : public NodoGrafoEscena
{
    protected:
        unsigned int parametro = 1;
        Matriz4f * girord = nullptr;

    public:
        RuedaDelantera();
        virtual unsigned leerNumParametros() const;
        virtual void actualizarEstadoParametro(const unsigned iParam, const float tSec);
};

class RuedaTrasera : public NodoGrafoEscena
{
    protected:
        unsigned int parametro = 1;
        Matriz4f * girort = nullptr;

    public:
        RuedaTrasera();
        virtual unsigned leerNumParametros() const;
        virtual void actualizarEstadoParametro(const unsigned iParam, const float tSec);
};

class Plato : public NodoGrafoEscena
{
    public:
        Plato(unsigned n);
};

class Cuadro : public NodoGrafoEscena
{
    public:
        Cuadro();
};

class Cadena : public NodoGrafoEscena
{
    public:
        Cadena();
};

class Pinones : public NodoGrafoEscena
{
    public:
        Pinones(unsigned n);
};

class Rampa : public NodoGrafoEscena
{
    public:
        Rampa();
};

class Bici : public NodoGrafoEscena
{
    protected:
        unsigned int  parametros = 6;

        Matriz4f *movimiento = nullptr;
        Matriz4f *tamanio = nullptr;

        RuedaTrasera *rt = new RuedaTrasera();
        RuedaDelantera *rd = new RuedaDelantera();
        PedalDerecho *pd = new PedalDerecho();
        PedalIzquierdo *pi = new PedalIzquierdo();

    public:
        Bici();
        virtual void actualizarEstadoParametro(const unsigned iParam, const float tSec); 
        virtual unsigned leerNumParametros() const;
};

class Bici2 : public NodoGrafoEscena
{
    protected:
        unsigned int  parametros = 5; 

        Matriz4f *movimiento = nullptr;

        RuedaTrasera *rt = new RuedaTrasera();
        RuedaDelantera *rd = new RuedaDelantera();
        PedalDerecho *pd = new PedalDerecho();
        PedalIzquierdo *pi = new PedalIzquierdo();

    public:
        Bici2();
        virtual void actualizarEstadoParametro(const unsigned iParam, const float tSec); 
        virtual unsigned leerNumParametros() const;
};

class P3 : public NodoGrafoEscena
{
    protected:
        unsigned parametros = 6; //son dos, pero para llamar al metodo actualizarestasparametros de las bici hace falta que iParam vaya de 0 a 5
        
        Bici *bici = new Bici();
        Bici2 *bici2 = new Bici2();

    public:
        P3();
        void actualizarEstadoParametro(const unsigned iParam, const float tSec); 
        unsigned leerNumParametros() const;
};

//----------------------------------------------------------------------
//EJERCICIOS ADICIONALES:

class GrafoCubos : public NodoGrafoEscena
{
    protected:
        unsigned int parametros = 1;
        Matriz4f *girocubos = nullptr;

    public:
        GrafoCubos();
        virtual unsigned leerNumParametros() const;
        virtual void actualizarEstadoParametro(const unsigned iParam, const float tSec);
};

class GrafoEstrellaX : public NodoGrafoEscena
{
    protected:
        unsigned int parametros = 1;
        Matriz4f *giro = nullptr;

    public:
        GrafoEstrellaX(unsigned n);
        virtual unsigned leerNumParametros() const;
        virtual void actualizarEstadoParametro(const unsigned iParam, const float tSec);
};


#endif

