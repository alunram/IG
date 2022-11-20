// Práctica 3
// *********************************************************************
// **
// ** Modelo jerárquico (implementacion)
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

#include "modelo-jer.h"

using namespace std ;

P3 :: P3(){
    bici = new Bici();
    agregar(bici);
    
    bici2 = new Bici2();
    agregar(bici2);

    agregar(new Rampa());
}

unsigned P3:: leerNumParametros() const{
    return parametros;
}

void P3::actualizarEstadoParametro(const unsigned iParam, const float tSec){
    assert(iParam < leerNumParametros());

    using namespace std;
    cout << "Parametro: " << iParam << endl;
    bici->actualizarEstadoParametro(iParam, tSec);
    bici2->actualizarEstadoParametro(iParam, tSec);
}

Bici:: Bici(){
    unsigned int subirbici = agregar(MAT_Traslacion({0.0, +1.0, 0.0}));
    unsigned int tam = agregar(MAT_Escalado(1.0, 1.0, 1.0));

    agregar(new Manillar());
    agregar(new Plato(40));
    agregar(new Sillin());
    agregar(new Pinones(40));
    agregar(new Cuadro());
    agregar(new Cadena());
    

    //con animaciones:
    rt = new RuedaTrasera();
    agregar(rt);
    rd = new RuedaDelantera();
    agregar(rd);
    pd = new PedalDerecho();
    agregar(pd);
    pi = new PedalIzquierdo();
    agregar(pi);

    movimiento = leerPtrMatriz(subirbici);
    tamanio = leerPtrMatriz(tam);
}

void Bici::actualizarEstadoParametro(const unsigned iParam, const float tSec){
    assert(iParam < leerNumParametros());

    float a = 0.0;
    float b = 0.7;
    float c = a + 2 * b * sin(M_PI * tSec);

    using namespace std;
    cout << "Parametro: " << iParam << endl;
    switch (iParam)
    {
        case 0:
            *movimiento = MAT_Traslacion({c, 0.7, 0.0});
            break;

        case 1:
            *tamanio = MAT_Escalado(+0.3+fabs(sin(M_PI * tSec)/2), +0.3+fabs(sin(M_PI * tSec)/2), +0.3+fabs(sin(M_PI * tSec)/2));
            break;

        case 2:
            rt->actualizarEstadoParametro(0, tSec);
            break;
        
        case 3:
            rd->actualizarEstadoParametro(0, tSec);
            break;

        case 4:
            pd->actualizarEstadoParametro(0, tSec);
            break;

        case 5:
            pi->actualizarEstadoParametro(0, tSec);
            break;

        default:   
            break;
    }
}

unsigned Bici:: leerNumParametros() const{
    return parametros;
}

Bici2:: Bici2(){
    unsigned int subirbici = agregar(MAT_Traslacion({4.0, +1.4, 5.0}));
    agregar(MAT_Rotacion(20, {0, 0, 1}));

    agregar(new Manillar());
    agregar(new Plato(40));
    agregar(new Cuadro());
    agregar(new Sillin());
    agregar(new Cadena());
    agregar(new Pinones(40));

    //con animaciones:
    rt = new RuedaTrasera();
    agregar(rt);
    rd = new RuedaDelantera();
    agregar(rd);
    pd = new PedalDerecho();
    agregar(pd);
    pi = new PedalIzquierdo();
    agregar(pi);

    movimiento = leerPtrMatriz(subirbici);
}

unsigned Bici2:: leerNumParametros() const{
    return parametros;
}

void Bici2::actualizarEstadoParametro(const unsigned iParam, const float tSec){
    float a = 4.0;
    float b = 10.0;
    float c = a +  fabs(b * sin(2.0 * M_PI * tSec * 0.1));
    float d = 1.4;
    float e = 3.42;
    float f = d +  fabs(e * sin(2.0 * M_PI * tSec * 0.1));

    using namespace std;
    cout << "Parametro: " << iParam << endl;
    switch (iParam)
    {
        case 0:
            *movimiento = MAT_Traslacion({c, f, 5.0});
            break;

        case 1:
            rt->actualizarEstadoParametro(0, tSec);
            break;
        case 2:
            rd->actualizarEstadoParametro(0, tSec);       
            break;
        
        case 3:
            pd->actualizarEstadoParametro(0, tSec);
            break;

        case 4:
            pi->actualizarEstadoParametro(0, tSec);
            break;

        default:
            break;
    }
}

RuedaDelantera :: RuedaDelantera(){
    ponerColor({0.0, 0.0, 0.0});
    unsigned int anim = agregar(MAT_Rotacion(0, {1, 0, 0}));
    girord = leerPtrMatriz(anim);
    agregar(new Rueda(50));
}

RuedaTrasera :: RuedaTrasera(){
    ponerColor({0.0, 0.0, 0.0});
    agregar(MAT_Traslacion({-2.75, 0.0, 0.0}));
    unsigned int anim = agregar(MAT_Rotacion(0, {1, 0, 0}));
    girort = leerPtrMatriz(anim);
    agregar(new Rueda(50));
}

unsigned RuedaTrasera::leerNumParametros() const
{
    return parametro;
}

unsigned RuedaDelantera::leerNumParametros() const
{
    return parametro;
}

void RuedaTrasera::actualizarEstadoParametro(const unsigned iParam, const float tSec)
{
    const float velocidad = 2*M_PI*1.3*2.5;
    float angulo = 2 * velocidad * M_PI * tSec;
    switch (iParam)
    {
    case 0:
        cout << "Parametro 0: " << endl;
       (*girort) = MAT_Rotacion(-angulo, {0, 0, 1});
       break;
    default:
       break;
    }
}

void RuedaDelantera::actualizarEstadoParametro(const unsigned iParam, const float tSec)
{
    const float velocidad = 2*M_PI*1.3*2.5;
    float angulo = 2 * velocidad * M_PI * tSec;
    switch (iParam)
    {
    case 0:
        cout << "Parametro 0: " << endl;
        (*girord) = MAT_Rotacion(-angulo, {0, 0, 1});
       break;
    default:
       break;
    }
}

Manillar :: Manillar(){
    ponerColor({0.0, 0.0, 0.0});
    agregar(MAT_Traslacion({-0.25, 1.81, -0.812}));
    agregar(MAT_Escalado(0.04, 0.04, 0.04));
    agregar(MAT_Rotacion(90, {0.0, 0.0, 1.0}));
    agregar(MAT_Rotacion(90, {1.0, 0.0, 0.0}));
    agregar(new Cilindro(20, 20));
    for (int i = 0; i < 38; i++)
    {
        agregar(MAT_Traslacion({0.0, 1.0, 0.0}));
        agregar(new Cilindro(20, 20));
    }
}

Sillin :: Sillin(){
    ponerColor({0.0, 0.0, 0.0});
    agregar(MAT_Traslacion({-1.72, 1.8, 0.0375}));
    agregar(MAT_Escalado(0.25, 0.25, 0.1875));
    agregar(new SillinBici());
}

BielaDerecha :: BielaDerecha(){
    ponerColor({0.0, 0.0, 0.0});
    agregar(MAT_Escalado(0.25, 0.25, 0.25));
    agregar(MAT_Rotacion(-90, {0.0, 0.0, 1.0}));

    unsigned int anim = agregar(MAT_Rotacion(0, {1, 0, 0}));
    girobd = leerPtrMatriz(anim);
    agregar(new BielaBici());
    
    agregar(MAT_Rotacion(90, {0.0, 0.0, 1.0}));
    agregar(MAT_Traslacion({0.0, -1.4, 0.22}));
    agregar(MAT_Escalado(0.5, 0.5, 0.5));
    agregar(new PedalBici());
}

unsigned BielaDerecha::leerNumParametros() const
{
    return parametro;
}

void BielaDerecha::actualizarEstadoParametro(const unsigned iParam, const float tSec)
{
    const float velocidad = 15;
    float angulo = 3*M_PI/4 + 2 * velocidad * M_PI * tSec;
    switch (iParam)
    {
    case 0:
        cout << "Parametro 0: " << endl;
        (*girobd) = MAT_Rotacion(-angulo, {0, 0, 1});
        break;
    default:
       break;
    }
}

BielaIzquierda :: BielaIzquierda(){
    ponerColor({0.0, 0.0, 0.0});
    agregar(MAT_Escalado(0.25, 0.25, 0.25));
    agregar(MAT_Rotacion(90, {0.0, 0.0, 1.0}));

    unsigned int anim = agregar(MAT_Rotacion(0, {1, 0, 0}));
    girobi = leerPtrMatriz(anim);
    agregar(new BielaBici());
    
    agregar(MAT_Rotacion(-90, {0.0, 0.0, 1.0}));
    agregar(MAT_Traslacion({0.0, 1.4, -0.22}));
    agregar(MAT_Escalado(0.5, 0.5, 0.5));
    agregar(new PedalBici());
}

unsigned BielaIzquierda::leerNumParametros() const
{
    return parametro;
}

void BielaIzquierda::actualizarEstadoParametro(const unsigned iParam, const float tSec)
{
    const float velocidad = 15;
    float angulo = 3*M_PI/4 + 2 * velocidad * M_PI * tSec;
    switch (iParam)
    {
    case 0:
        cout << "Parametro 0: " << endl;
        (*girobi) = MAT_Rotacion(-angulo, {0, 0, 1});
        break;
    default:
       break;
    }
}

PedalDerecho :: PedalDerecho()
{
    agregar(MAT_Traslacion({-1.65, 0.28, +0.1}));
    bd = new BielaDerecha();
    agregar(bd);
}

unsigned PedalDerecho::leerNumParametros() const
{
    return parametro;
}

void PedalDerecho::actualizarEstadoParametro(const unsigned iParam, const float tSec)
{
    switch (iParam)
    {
    case 0:
        bd->actualizarEstadoParametro(iParam, tSec);
        break;
    default:
       break;
    }
}

PedalIzquierdo :: PedalIzquierdo()
{
    agregar(MAT_Traslacion({-1.65, 0.28, -0.1}));
    bi = new BielaIzquierda();
    agregar(bi);
}

unsigned PedalIzquierdo::leerNumParametros() const
{
    return parametro;
}

void PedalIzquierdo::actualizarEstadoParametro(const unsigned iParam, const float tSec)
{
    switch (iParam)
    {
    case 0:
        bi->actualizarEstadoParametro(iParam, tSec);
        break;
    default:
       break;
    }

}

Plato :: Plato(unsigned n){
    ponerColor({0.1, 0.1, 0.1});
    agregar(MAT_Traslacion({-1.65, 0.28, 0.1}));
    agregar(MAT_Escalado(0.2, 0.2, 0.2));
    agregar(new PlatoBici(n));
}

Cuadro :: Cuadro(){
    agregar(new HorquillaTrasera());
    agregar(new HorquillaDelantera());
    agregar(new ParteBajaHorquilla());
    agregar(new CuadroParteBaja());
    agregar(new CuadroParteAlta());
    agregar(new CuadroParteVertical());
    agregar(new Tija());
    agregar(new Potencia());   
}

HorquillaTrasera :: HorquillaTrasera(){
    ponerColor({0.0, 0.85, 1.0});
    agregar(MAT_Traslacion({-2.75, 0.0, 0.0}));
    agregar(MAT_Escalado(0.07, 0.07, 0.07));
    agregar(MAT_Rotacion(-34, {0.0, 0.0, 1.0}));
    agregar(MAT_Traslacion({0.0, 0.0, 0.3}));
    agregar(new Cilindro(10, 10));

    for (int i = 0; i < 25; i++)
    {
        agregar(MAT_Traslacion({0.0, 1.0, 0.0}));
        agregar(new Cilindro(10, 10));
    } 
}

HorquillaDelantera :: HorquillaDelantera(){
    ponerColor({0.0, 0.85, 1.0});
    agregar(MAT_Escalado(0.07, 0.07, 0.07));
    agregar(MAT_Rotacion(10, {0.0, 0.0, 1.0}));
    agregar(MAT_Traslacion({0.0, 0.0, 0.3}));
    agregar(new Cilindro(10, 10));

    for (int i = 0; i < 20; i++)
    {
        agregar(MAT_Traslacion({0.0, 1.0, 0.0}));
        agregar(new Cilindro(10, 10));
    }
}

ParteBajaHorquilla :: ParteBajaHorquilla(){
    ponerColor({0.0, 0.85, 1.0});
    agregar(MAT_Traslacion({-2.75, 0.0, 0.0}));
    agregar(MAT_Escalado(0.07, 0.07, 0.07));
    agregar(MAT_Rotacion(-75, {0.0, 0.0, 1.0}));
    agregar(MAT_Traslacion({0.0, 0.0, 0.3}));
    agregar(new Cilindro(10, 10));
    for (int i = 0; i < 15; i++)
    {
        agregar(MAT_Traslacion({0.0, 1.0, 0.0}));
        agregar(new Cilindro(10, 10));
    } 
}

CuadroParteVertical :: CuadroParteVertical(){
    ponerColor({0.0, 0.85, 1.0});
    agregar(MAT_Traslacion({-1.68, 0.21, 0.021}));
    agregar(MAT_Escalado(0.07, 0.07, 0.07));
    agregar(new Cilindro(10, 10));
    for (int i = 0; i < 17; i++)
    {
        agregar(MAT_Traslacion({0.0, 1.0, 0.0}));
        agregar(new Cilindro(10, 10));
    }
}

CuadroParteBaja :: CuadroParteBaja(){
    ponerColor({0.0, 0.85, 1.0});
    agregar(MAT_Traslacion({-1.65, 0.27, 0.0}));
    agregar(MAT_Escalado(0.07, 0.07, 0.07));
    agregar(MAT_Rotacion(-50, {0.0, 0.0, 1.0}));
    agregar(MAT_Traslacion({0.0, 0.0, 0.3}));
    agregar(new Cilindro(10, 10));
    for (int i = 0; i < 25; i++)
    {
        agregar(MAT_Traslacion({0.0, 1.0, 0.0}));
        agregar(new Cilindro(10, 10));
    }
}

CuadroParteAlta :: CuadroParteAlta(){
    ponerColor({0.0, 0.85, 1.0});
    agregar(MAT_Traslacion({-0.19, +1.5, 0.0}));
    agregar(MAT_Escalado(0.07, 0.07, 0.07));
    agregar(MAT_Rotacion(90, {0.0, 0.0, 1.0}));
    agregar(MAT_Traslacion({0.0, 0.0, 0.3}));
    agregar(new Cilindro(10, 10));
    for (int i = 0; i < 22; i++)
    {
        agregar(MAT_Traslacion({0.0, 1.0, 0.0}));
        agregar(new Cilindro(10, 10));
    }
}

Tija :: Tija (){
    ponerColor({0.0, 0.0, 0.0});
    agregar(MAT_Traslacion({-1.69, 1.5, 0.0105}));
    agregar(MAT_Escalado(0.035, 0.035, 0.035));
    agregar(new Cilindro(20, 20));
    for (int i = 0; i < 8; i++)
    {
        agregar(MAT_Traslacion({0.0, 1.0, 0.0}));
        agregar(new Cilindro(20, 20));
    }
}

Potencia :: Potencia(){
    ponerColor({0.0, 0.0, 0.0});
    agregar(MAT_Traslacion({-0.25, 1.5, 0.0105}));
    agregar(MAT_Escalado(0.035, 0.035, 0.035));
    agregar(new Cilindro(20, 20));
    for (int i = 0; i < 7; i++)
    {
        agregar(MAT_Traslacion({0.0, 1.0, 0.0}));
        agregar(new Cilindro(20, 20));
    }

}

Cadena :: Cadena(){
    ponerColor({0.1, 0.1, 0.1});
    agregar(MAT_Traslacion({-2.75, 0.16, 0.1}));
    agregar(MAT_Escalado(0.04, 0.04, 0.04));
    agregar(MAT_Rotacion(-74, {0.0, 0.0, 1.0}));
    agregar(new MallaTorre(28));
    agregar(MAT_Rotacion(74, {0.0, 0.0, 1.0}));
    agregar(MAT_Traslacion({0.0, -4.8, -1.0}));
    agregar(MAT_Rotacion(-80, {0.0, 0.0, 1.0}));
    agregar(new MallaTorre(27)); 
}

Pinones :: Pinones(unsigned n){
    ponerColor({0.1, 0.1, 0.1});
    agregar(MAT_Traslacion({-2.8, 0.07, 0.1}));
    agregar(MAT_Escalado(0.15, 0.15, 0.15));
    agregar(new PlatoBici(n));
    for (int i = 0; i < 7; i++)
    {
        agregar(MAT_Traslacion({0.0, 0.0, 0.05}));
        agregar(MAT_Escalado(0.75, 0.75, 0.75));
        agregar(new PlatoBici(n));
    } 
}

Rampa :: Rampa(){
   ponerColor({0.1, 0.1, 0.1});
   agregar(MAT_Traslacion({4.0, 0.0, 4.0}));
   agregar(new RampaBici());
}

//------------------------------------------------------------------------------------
//EJERCICIOS ADICIONALES:

//Ejercicio adicional 2: Grafo Cubos
GrafoCubos::GrafoCubos(){
    /*agregar(MAT_Traslacion({-0.5, -0.5, -0.5}));
    agregar(new RejillaY(8,8));
    agregar(MAT_Rotacion(90, {0.0, 0.0, 1.0}));
    agregar(new RejillaY(8,8));
    agregar(MAT_Rotacion(90, {1.0, 0.0, 0.0}));
    agregar(new RejillaY(8,8));
    agregar(MAT_Rotacion(-90, {1.0, 0.0, 0.0}));
    agregar(MAT_Rotacion(-90, {0.0, 0.0, 1.0}));
    agregar(MAT_Traslacion({0.0, 1.0, 0.0}));
    agregar(new RejillaY(8,8));
    agregar(MAT_Traslacion({+1.0, 0.0, 0.0}));
    agregar(MAT_Rotacion(-90, {0.0, 0.0, 1.0}));
    agregar(new RejillaY(8,8));
    agregar(MAT_Rotacion(90, {0.0, 0.0, 1.0}));
    agregar(MAT_Traslacion({-1.0, 0.0, +1.0}));
    agregar(MAT_Rotacion(90, {+1.0, 0.0, 0.0}));
    agregar(new RejillaY(8,8));
    agregar(MAT_Rotacion(-90, {+1.0, 0.0, 0.0}));
    agregar(MAT_Traslacion({+0.5, -0.5, +0.25}));
    agregar(MAT_Escalado(0.2, 0.2, 0.5));
    agregar(new Cubo());
    agregar(MAT_Traslacion({0.0, 0.0, -3.0}));
    agregar(new Cubo());
    agregar(MAT_Traslacion({+3.75, 0.0, +1.5}));
    agregar(MAT_Escalado(+5.0, +5.0, +2.0));
    agregar(MAT_Escalado(0.5, 0.2, 0.2));
    agregar(new Cubo());
    agregar(MAT_Traslacion({-3.0, 0.0, 0.0}));
    agregar(new Cubo()); */   

    NodoGrafoEscena *rejillasy = new NodoGrafoEscena();
    RejillaY *unarejillay = new RejillaY(10, 10);
    rejillasy->agregar(MAT_Traslacion({-0.5, -0.5, -0.5}));
    rejillasy->agregar(unarejillay);
    agregar(rejillasy);

    NodoGrafoEscena *cubos = new NodoGrafoEscena();
    unsigned int anim = cubos->agregar(MAT_Rotacion(0, {0, 1, 0}));
    Cubo *uncubo = new Cubo();
    cubos->agregar(MAT_Escalado(0.15, 0.25, 0.15));
    cubos->agregar(MAT_Traslacion({0, -3, 0}));
    cubos->agregar(uncubo);
    agregar(cubos);

    for (int i = 0; i < 3; i++)
    {
      agregar(MAT_Rotacion(90, {1, 0, 0}));
      agregar(rejillasy);
      agregar(cubos);
    }

    agregar(MAT_Rotacion(90, {0, 0, 1}));
    agregar(rejillasy);
    agregar(cubos);

    agregar(MAT_Rotacion(180, {0, 0, 1}));
    agregar(rejillasy);
    agregar(cubos);

    girocubos = cubos->leerPtrMatriz(anim);
}

void GrafoCubos :: actualizarEstadoParametro(const unsigned iParam, const float tSec){
    const float velocidad = 4.5;
    float angulo = 2 * velocidad * M_PI * tSec;
    switch (iParam)
    {
    case 0:
       (*girocubos) = MAT_Rotacion(-angulo, {0, 1, 0});
       break;
    default:
       break;
    }
}

unsigned GrafoCubos::leerNumParametros() const
{
   return parametros;
}

//Ejercicio adicional 1:
GrafoEstrellaX::GrafoEstrellaX(unsigned n){
    assert(n>1);
    NodoGrafoEscena *estrella = new NodoGrafoEscena();
    NodoGrafoEscena *objeto = new NodoGrafoEscena();
    NodoGrafoEscena *uncono = new NodoGrafoEscena();
    NodoGrafoEscena *conos = new NodoGrafoEscena();

    estrella->agregar(MAT_Rotacion(90, {0.0, 1.0, 0.0}));
    estrella->agregar(MAT_Escalado(2.6, 2.6, 2.6)); 
    estrella->agregar(MAT_Traslacion({-0.5, -0.5, 0.0}));
    unsigned int ind = objeto->agregar(MAT_Rotacion(0, {1.0, 0.0, 0.0}));
    estrella->agregar(new EstrellaZ(n));
    
    /*agregar(MAT_Escalado(0.1, 0.1, 0.1));
    agregar(MAT_Rotacion(-45, {1.0, 0.0, 0.0}));
    agregar(new Cono(20, 20));

    agregar(MAT_Traslacion({+0.5, +0.5, 0.0}));
    agregar(MAT_Rotacion(-90, {0.0, 1.0, 0.0}));*/

    uncono->agregar(MAT_Escalado(0.15, 0.15, 0.15));
    uncono->agregar(new Cono(20,20));

    for (int i = 0; i < n; i++)
    {
        /*float angulo = 360.0*float(i)/float(n);
        agregar(MAT_Traslacion({0.0, sin(angulo)*0.5, -cos(angulo)*0.5}));
        agregar(MAT_Escalado(0.1, 0.1, 0.1));
        agregar(MAT_Rotacion(-90+angulo, {1.0, 0.0, 0.0}));
        agregar(new Cono(20, 20));
        agregar(MAT_Rotacion(90-angulo, {1.0, 0.0, 0.0}));
        agregar(MAT_Escalado(10, 10, 10));
        agregar(MAT_Traslacion({0.0, -sin(angulo)*0.5, +cos(angulo)*0.5}));*/


        NodoGrafoEscena *conogirado = new NodoGrafoEscena();
        float angulogrados = 360.0*float(i)/float(n);
        float angulorad = ((float)i * 2 * M_PI) / ((float)n);

        conogirado->agregar(MAT_Traslacion({1.3 * cos(angulorad), 1.3 * sin(angulorad), 0.0}));
        conogirado->agregar(MAT_Rotacion(angulogrados-90, {0.0, 0.0, 1.0}));
        conogirado->agregar(uncono);
        conos->agregar(conogirado);
    }

    objeto->agregar(estrella);
    objeto->agregar(MAT_Rotacion(90, {0, 1, 0}));
    objeto->agregar(conos);

    agregar(objeto);
    giro = objeto->leerPtrMatriz(ind);
}

unsigned GrafoEstrellaX::leerNumParametros() const
{
   return parametros;
}

void GrafoEstrellaX::actualizarEstadoParametro(const unsigned iParam, const float tSec){
    const float velocidad = 2*M_PI*1.3*2.5;
    float angulo = 2 * velocidad * M_PI * tSec;

    using namespace std;
    cout << "Parametro: " << iParam << endl;

    switch (iParam)
    {
    case 0:
        (*giro) = MAT_Rotacion(angulo, {1, 0, 0});
        break;
    default:
        break;
    }
}

