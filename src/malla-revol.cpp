// *********************************************************************
// **
// ** Informática Gráfica, curso 2019-20
// ** Implementación de la clase 'MallaRevol'
// **
// *********************************************************************

#include "ig-aux.h"
#include "lector-ply.h"
#include "malla-revol.h"

using namespace std ;

// *****************************************************************************




// Método que crea las tablas de vértices, triángulos, normales y cc.de.tt.
// a partir de un perfil y el número de copias que queremos de dicho perfil.
void MallaRevol::inicializar
(
   const std::vector<Tupla3f> & perfil,     // tabla de vértices del perfil original
   const unsigned               num_copias  // número de copias del perfil
)
{
   // COMPLETAR: Práctica 2: completar: creación de la malla....
   //mio:
   const int m = perfil.size(); 
   const int n = num_copias;
   Matriz4f matrizRot;
   Tupla3f eje = {0.0, 1.0, 0.0};
   //1. Crear la tabla de vértices:
   for (int i = 0; i < n; i++)
   {
      for (int j = 0; j < m; j++)
      {
         float angulo = 360.0 * i / (n-1); 
         matrizRot = MAT_Rotacion(angulo, eje);
         vertices.push_back(matrizRot * perfil[j]);
      }
   }

   //2.Crear tabla de triángulos:
   for (int i = 0; i < (n-1); i++)
   {
      for (int j = 0; j < (m-1); j++)
      {
         int k = i*m + j;
         triangulos.push_back({k, k+m, k+m+1});
         triangulos.push_back({k, k+m+1, k+1});
      }
   }


}

// -----------------------------------------------------------------------------
// constructor, a partir de un archivo PLY

MallaRevolPLY::MallaRevolPLY
(
   const std::string & nombre_arch,
   const unsigned      nperfiles
)
{
   ponerNombre( std::string("malla por revolución del perfil en '"+ nombre_arch + "'" ));
   // COMPLETAR: práctica 2: crear la malla de revolución
   // Leer los vértice del perfil desde un PLY, después llamar a 'inicializar'
   // ...........................

   //mio:
   std::vector<Tupla3f> perfil;
   LeerVerticesPLY(nombre_arch, perfil);
   inicializar(perfil, nperfiles);

}

// *****************************************************************************
//Constructores de cilindro cono y esfera
//mio:
Cilindro:: Cilindro(const int num_verts_per, const unsigned nperfiles)
{
   ponerNombre( std::string("Cilindro"));

   std::vector<Tupla3f> perfil;
   for(int i=0; i<num_verts_per; i++){
      perfil.push_back({1.0, 1.0*i/(num_verts_per-1), 0.0});
   }
   inicializar(perfil, nperfiles);
}

Cono:: Cono(const int num_verts_per, const unsigned nperfiles)
{
   ponerNombre( std::string("Cono"));

   std::vector<Tupla3f> perfil;
   for(int i=0; i<num_verts_per; i++){
      perfil.push_back({1.0-1.0*i/(num_verts_per-1), 1.0*i/(num_verts_per-1), 0.0});
      //perfil.push_back({i / (num_verts_per - 1), -i / (num_verts_per - 1) + 1, 0.0});   
   }
   inicializar(perfil, nperfiles);
}

Esfera:: Esfera(const int num_verts_per, const unsigned nperfiles)
{
   ponerNombre( std::string("Esfera"));

   std::vector<Tupla3f> perfil;

   perfil.push_back({0.0, 1.0, 0.0});

   for (int i = 1; i < num_verts_per-1; i++)
   {
      double angulo = (M_PI/2 - M_PI * i /(num_verts_per-2));
      perfil.push_back({cos(angulo), sin(angulo), 0.0});
   }

   perfil.push_back({0.0, -1.0, 0.0});

   inicializar(perfil, nperfiles);
   
}

