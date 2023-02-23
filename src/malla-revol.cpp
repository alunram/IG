//Nombre: Alvaro, Apellidos: Luna Ramirez, Titulacion: GIM, correo: alvaroluna@correo.ugr.es, DNI: 
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

   //P4:
   std::vector<Tupla3f> normales, normalesaux;
   Tupla3f resta, arista;

   //aristas
   for (unsigned int i = 0; i < m; i++)
   {
      resta = perfil[i + 1] - perfil[i];
      arista = {resta(1), -resta(0), 0.0};

      if (arista.lengthSq() > 0)
         arista = arista.normalized();

      normalesaux.push_back(arista);
   }

   //vertices
   Tupla3f resta2;

   normales.push_back(normalesaux[0]);

   for (unsigned int i = 1; i < m-1; i++)
   {
      resta2 = normalesaux[i - 1] + normalesaux[i];

      if(resta2.lengthSq() != 0.0)
         resta2 = resta2.normalized();

      normales.push_back(resta2);
   }

   normales.push_back(normalesaux[m - 2]);


   //coordenadas de textura:
   std::vector<float> d, t, sum_par;
   float sum;

   for (unsigned int i = 0; i < perfil.size() - 1; i++)
   {
      d.push_back((sqrt((perfil[i + 1] - perfil[i]).lengthSq()))); //dist
      sum += d[i];
   }

   sum_par.push_back(0.0);
   t.push_back(0.0);

   for (unsigned int i = 1; i < perfil.size(); i++)
   {
      sum_par.push_back(sum_par[i - 1] + d[i - 1]);
   }
  
   for (unsigned int i = 1; i < perfil.size(); i++)
   {
      t.push_back(sum_par[i] / sum);
   }

   for (int i = 0; i < n; i++)
   {
      for (int j = 0; j < m; j++)
      {
         float angulo = 360.0 * i / (n-1); 
         matrizRot = MAT_Rotacion(angulo, eje);
         nor_ver.push_back(matrizRot * normales[j]);

         cc_tt_ver.push_back({float(i) / (n - 1), 1 - t[j]});
      }
   }

   calcularNormales();

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

   for (int i = 0; i < num_verts_per; i++)
   {
      double angulo = (-M_PI/2 + M_PI * i /(num_verts_per-1));
      perfil.push_back({float(cos(angulo)), float(sin(angulo)), 0.0});
      //perfil.push_back({float(cos(M_PI * i / (num_verts_per - 1) - M_PI / 2)), float(sin(M_PI * i / (num_verts_per - 1) + M_PI / 2)), 0});

   }

   perfil.push_back({0.0, -1.0, 0.0});

   inicializar(perfil, nperfiles);
   
}

circunferenciaprueba:: circunferenciaprueba(const int num_verts_per, const unsigned nperfiles)
{
   ponerNombre( std::string("prueba de hacer una circunferencia"));

   std::vector<Tupla3f> perfil;
   perfil.push_back({0.0, 0.0, 0.0});
   perfil.push_back({1.0, 0.0, 0.0});
   //for(int i=0; i<num_verts_per; i++){
      //perfil.push_back({1.0-1.0*i/(num_verts_per-1), 1.0*i/(num_verts_per-1), 0.0});
      //perfil.push_back({i / (num_verts_per - 1), -i / (num_verts_per - 1) + 1, 0.0});   
   //}
   inicializar(perfil, nperfiles);
}

// *****************************************************************************

//He hecho dos versiones, ninguna sale del todo bien. La primera sale recta, no se hace bien el angulo.
//La segunda, que esta abajo comentada, tiene forma redondeada pero no como la de la foto. No consigo hacer bien la forma
CopaRevol:: CopaRevol(const int num_verts_per, const unsigned nperfiles)
{
   ponerNombre( std::string("Copa revolucion"));

   std::vector<Tupla3f> perfil;

   //añado los de la base de la copa;
   perfil.push_back({1.0, -0.1, 0.0});
   perfil.push_back({1.0, 0.0, 0.0});

   float numvertcirc = (num_verts_per-2) / 2;
   //añado los de la primera circunferencia
   for (int i = (num_verts_per-2)/2; i > 0; i--)
   {
      //double angulo = (3*M_PI/4 - M_PI / 2 * i /((num_verts_per-2)/2));
      double angulo = (M_PI / 2  * (i /numvertcirc));
      perfil.push_back({float(1.0 - 0.8*cos(angulo)), float(0.1 +  0.8*cos(angulo)), 0.0});
      //perfil.push_back({float(cos(M_PI * i / (num_verts_per - 1) - M_PI / 2)), float(sin(M_PI * i / (num_verts_per - 1) + M_PI / 2)), 0});

   }

   //añado los de la segunda circunferencia
   for (int i = 0; i < (num_verts_per-2)/2; i++)
   {
      double angulo = (M_PI / 2  * (i /numvertcirc));
      //double angulo = (-M_PI/2 - M_PI /2  * i /(num_verts_per-2) / 2);
      perfil.push_back({float(0.2 + 0.8*cos(angulo)), float(0.9 + 0.8*cos(angulo)), 0.0});
      //perfil.push_back({float(cos(M_PI * i / (num_verts_per - 1) - M_PI / 2)), float(sin(M_PI * i / (num_verts_per - 1) + M_PI / 2)), 0});
   }

   //no sale bien, hago mal los angulos
   inicializar(perfil, nperfiles);
   
}

/*CopaRevol:: CopaRevol(const int num_verts_per, const unsigned nperfiles)
{
   ponerNombre( std::string("Copa revolucion"));

   std::vector<Tupla3f> perfil;

   //añado los de la base de la copa;
   perfil.push_back({1.0, -0.1, 0.0});
   perfil.push_back({1.0, 0.0, 0.0});

   float numvertcirc = (num_verts_per-2) / 2;
   //añado los de la primera circunferencia
   for (int i = 0; i < (num_verts_per-1)/2; i++)
   {
      //double angulo = (3*M_PI/4 - M_PI / 2 * i /((num_verts_per-2)/2));
      double angulo = (M_PI / 2  * (i /numvertcirc));
      perfil.push_back({float(1.0 - 0.8*cos(angulo)), float(0.1 +  0.8*sin(angulo)), 0.0});
      //perfil.push_back({float(cos(M_PI * i / (num_verts_per - 1) - M_PI / 2)), float(sin(M_PI * i / (num_verts_per - 1) + M_PI / 2)), 0});

   }

   //añado los de la segunda circunferencia
   for (int i = 0; i < (num_verts_per-1)/2; i++)
   {
      double angulo = (M_PI / 2  * (i /numvertcirc));
      //double angulo = (-M_PI/2 - M_PI /2  * i /(num_verts_per-2) / 2);
      perfil.push_back({float(0.2 + 0.8*cos(angulo)), float(0.95 + 0.8*sin(angulo)), 0.0});
   }

   inicializar(perfil, nperfiles);
   
}*/
