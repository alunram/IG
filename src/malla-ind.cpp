// *********************************************************************
// **
// ** Informática Gráfica, curso 2020-21
// ** Declaraciones de la clase Objeto3D.hpp
// **
// *********************************************************************

#include "ig-aux.h"
#include "malla-ind.h" // declaración de 'ContextoVis'
#include "lector-ply.h"

// *****************************************************************************
// funciones auxiliares

// *****************************************************************************
// métodos de la clase MallaInd.

MallaInd::MallaInd()
{
   // nombre por defecto
   ponerNombre("malla indexada, anónima");
}
// -----------------------------------------------------------------------------

MallaInd::MallaInd(const std::string &nombreIni)
{
   // 'identificador' puesto a 0 por defecto, 'centro_oc' puesto a (0,0,0)
   ponerNombre(nombreIni);
}

//-----------------------------------------------------------------------------
// calcula la tabla de normales de triángulos una sola vez, si no estaba calculada

void MallaInd::calcularNormalesTriangulos()
{

   // si ya está creada la tabla de normales de triángulos, no es necesario volver a crearla
   const unsigned nt = triangulos.size();
   assert(1 <= nt);
   if (0 < nor_tri.size())
   {
      assert(nt == nor_tri.size());
      return;
   }

   // COMPLETAR: Práctica 4: creación de la tabla de normales de triángulos
   // ....
}

// -----------------------------------------------------------------------------
// calcula las dos tablas de normales

void MallaInd::calcularNormales()
{
   // COMPLETAR: en la práctica 4: calculo de las normales de la malla
   // se debe invocar en primer lugar 'calcularNormalesTriangulos'
   // .......
}

// --------------------------------------------------------------------------------------------

void MallaInd::visualizarGL(ContextoVis &cv)
{

   using namespace std;
   assert(cv.cauce != nullptr);
   CError();

   if (triangulos.size() == 0 || vertices.size() == 0)
   {
      cout << "advertencia: intentando dibujar malla vacía '" << leerNombre() << "'" << endl
           << flush;
      return;
   }

   // guardar el color previamente fijado y fijar el color del objeto actual
   const Tupla4f color_previo = leerFijarColVertsCauce(cv);

   // COMPLETAR: práctica 1: si el nombre del VAO es 0, crear el VAO con sus VBOs:
   //   * en primer lugar se crea y activa el VAO , con 'CrearVAO'.
   //   * después se añade el VBO con la tabla de coordenadas de posición, 'CrearVBOAtrib'.
   //   * se añade el VBO con la tabla de índices (la tabla de triángulos), con 'CrearVBOInd'.
   //   * finalmente se añaden al VAO los VBOs con tablas de atributos (opcionaes) que haya, con 'CrearVBOAtrib'.
   // si el VAO ya está creado, (nombre_vao > 0), activarlo, con 'glBindVertexArray'
   //
   //  hay que tener en cuenta que el nombre del VAO y los nombres de losVBOs deben quedar en las correspondientes
   //  variables de instancia. Estos nombres son los devueltos por las
   //  funciones 'CrearVAO', 'CrearVBOAtrib' y 'CrearVBOInd'.
   //
   // mio:
   if (nombre_vao == 0)
   {
      nombre_vao = CrearVAO();
      // como se guardan los nombres de los vbos?. creo que es nombre_vbo_pos y nombre_vbo_tri
      nombre_vbo_pos = CrearVBOAtrib(ind_atrib_posiciones, vertices);
      nombre_vbo_tri = CrearVBOInd(triangulos);

      if (col_ver.size() > 0)
      {
         nombre_vbo_col = CrearVBOAtrib(ind_atrib_colores, col_ver);
      }

      //esto me lo dice isa, no estoy seguro:
      //nombre_vbo_nor = CrearVBOAtrib(ind_atrib_normales, nor_ver);
      //nombre_vbo_cct = CrearVBOAtrib(ind_atrib_coord_text, cc_tt_ver);

      CError();
      // CrearVBOAtrib(nombre_vao, TABLA DE ATRIBUTOS(OPCIONALES)); //FALTA ESTO¿?¿?¿?
   }
   else
   {
      if (nombre_vao > 0)
      {
         glBindVertexArray(nombre_vao);
      }
   }

   // COMPLETAR: práctica 1: visualizar con 'glDrawElements' y desactivar VAO.
   // mio:
   glDrawElements(GL_TRIANGLES, 3 * triangulos.size(), GL_UNSIGNED_INT, 0); // triangulos size * 3¿?
   glBindVertexArray(0);                                                    // creo que asi se desactiva el vao

   // restaurar el color previamente fijado
   cv.cauce->fijarColor(color_previo);
}

// -----------------------------------------------------------------------------
// visualizar pura y simplemente la geometría, sin colores, normales, coord. text. etc...
// (se supone que el estado de OpenGL está fijado antes de esta llamada de alguna forma adecuada)

void MallaInd::visualizarGeomGL(ContextoVis &cv)
{
   // COMPLETAR: práctica 1: asegurarnos de que el VAO de geometría está creado y activado
   // ....
   // mio:
   if (nombre_vao_geom == 0)
   {
      nombre_vao_geom = CrearVAO();
      // glBindBuffer, glVertexAttribPointer y glEnableVertexAttribArray:
      // NO SE SI ESTA BIEN
      /*glBindBuffer( GL_ARRAY_BUFFER, nombre_vbo_pos );
      glVertexAttribPointer( ind_atrib_posiciones, 3, GL_FLOAT, 0, 0, 0 );
      glEnableVertexAttribArray( ind_atrib_posiciones );

      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, nombre_vbo_tri );
      glVertexAttribPointer( ind_atrib_posiciones, 3, GL_FLOAT, 0, 0, 0 );
      glEnableVertexAttribArray( ind_atrib_posiciones ); */
      glBindBuffer(GL_ARRAY_BUFFER, nombre_vbo_pos);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, nombre_vbo_tri);
      glVertexAttribPointer(ind_atrib_posiciones, 3, GL_FLOAT, GL_FALSE, 0, 0);
      glEnableVertexAttribArray(ind_atrib_posiciones);

      CError();
   }
   else
   {
      if (nombre_vao_geom > 0)
      {
         glBindVertexArray(nombre_vao_geom);
         CError();
      }
   }

   // COMPLETAR: práctica 1. Visualizar la malla y desactivar VAO
   // ....
   // mio:
   glDrawElements(GL_TRIANGLES, 3 * triangulos.size(), GL_UNSIGNED_INT, 0);
   glBindVertexArray(0); // creo que asi se desactiva el vao
   CError();
}

// ****************************************************************************
// Clase 'MallaPLY'

MallaPLY::MallaPLY(const std::string &nombre_arch)
{
   ponerNombre(std::string("malla leída del archivo '") + nombre_arch + "'");

   // COMPLETAR: práctica 2: leer archivo PLY e inicializar la malla
   // ..........................
   //mio:
   LeerPLY(nombre_arch, vertices, triangulos);

   // COMPLETAR: práctica 4: invocar  a 'calcularNormales' para el cálculo de normales
   // .................
}

// ****************************************************************************
// Clase 'Cubo

Cubo::Cubo()
    : MallaInd("cubo 8 vértices")
{

   vertices =
       {
           {-1.0, -1.0, -1.0}, // 0
           {-1.0, -1.0, +1.0}, // 1
           {-1.0, +1.0, -1.0}, // 2
           {-1.0, +1.0, +1.0}, // 3
           {+1.0, -1.0, -1.0}, // 4
           {+1.0, -1.0, +1.0}, // 5
           {+1.0, +1.0, -1.0}, // 6
           {+1.0, +1.0, +1.0}, // 7
       };

   triangulos =
       {
           {0, 1, 3}, {0, 3, 2}, // X-
           {4, 7, 5},
           {4, 6, 7}, // X+ (+4)

           {0, 5, 1},
           {0, 4, 5}, // Y-
           {2, 3, 7},
           {2, 7, 6}, // Y+ (+2)

           {0, 6, 4},
           {0, 2, 6}, // Z-
           {1, 5, 7},
           {1, 7, 3} // Z+ (+1)
       };
}

// ****************************************************************************
// Clase 'CuboTejado'
CuboTejado::CuboTejado()
    : MallaInd("cubo 8 vértices")
{

   vertices =
       {
           {-1.0, -1.0, -1.0}, // 0
           {-1.0, -1.0, +1.0}, // 1
           {-1.0, +1.0, -1.0}, // 2
           {-1.0, +1.0, +1.0}, // 3
           {+1.0, -1.0, -1.0}, // 4
           {+1.0, -1.0, +1.0}, // 5
           {+1.0, +1.0, -1.0}, // 6
           {+1.0, +1.0, +1.0}, // 7
           {+0.0, +2.0, +0.0}, // 8
       };

   for (Tupla3f &v : vertices)
      v = 2.0f * v + Tupla3f({0.0, 2.0, 0.0});

   triangulos =
       {
           {0, 1, 3}, {0, 3, 2}, // X-
           {4, 7, 5},
           {4, 6, 7}, // X+ (+4)

           {0, 5, 1},
           {0, 4, 5}, // Y-
           //{2,3,7}, {2,7,6}, // Y+ (+2)   // quito cara superior
           {2, 3, 8},
           {3, 7, 8},
           {7, 6, 8},
           {6, 2, 8}, // añado tejado

           {0, 6, 4},
           {0, 2, 6}, // Z-
           {1, 5, 7},
           {1, 7, 3} // Z+ (+1)
       };
}
// -----------------------------------------------------------------------------------------------

// Clase tetraedro:
Tetraedro::Tetraedro()
    : MallaInd("tetraedro")
{
   vertices =
       {
           {0.0, 0.0, 0.0},  // 0
           {+1.0, 0.0, 0.0}, // 1
           {0.0, +1.0, 0.0}, // 2
           {0.0, 0.0, +1.0}, // 3
       };

   triangulos =
       {
           {0, 1, 3},
           {1, 2, 3},
           {2, 0, 3},
           {0, 2, 1},
       };

   ponerColor({1.0, 1.0, -2.0});
   // calcularNormales();
}

// ------------------------------------
// clase cubo colores:
CuboColores::CuboColores()
    : MallaInd("cubo colores")
{

   vertices =
       {
           {-1.0, -1.0, -1.0}, // 0
           {-1.0, -1.0, +1.0}, // 1
           {-1.0, +1.0, -1.0}, // 2
           {-1.0, +1.0, +1.0}, // 3
           {+1.0, -1.0, -1.0}, // 4
           {+1.0, -1.0, +1.0}, // 5
           {+1.0, +1.0, -1.0}, // 6
           {+1.0, +1.0, +1.0}, // 7
       };

   triangulos =
       {
           {0, 1, 3}, {0, 3, 2}, // X-
           {4, 7, 5},
           {4, 6, 7}, // X+ (+4)

           {0, 5, 1},
           {0, 4, 5}, // Y-
           {2, 3, 7},
           {2, 7, 6}, // Y+ (+2)

           {0, 6, 4},
           {0, 2, 6}, // Z-
           {1, 5, 7},
           {1, 7, 3} // Z+ (+1)
       };

   col_ver = {
      {-1.0, -1.0, -1.0}, // 0
      {-1.0, -1.0, +1.0}, // 1
      {-1.0, +1.0, -1.0}, // 2
      {-1.0, +1.0, +1.0}, // 3
      {+1.0, -1.0, -1.0}, // 4
      {+1.0, -1.0, +1.0}, // 5
      {+1.0, +1.0, -1.0}, // 6
      {+1.0, +1.0, +1.0}, // 7
   };

   /*for (int i = 0; i < vertices.size(); i++)
      for (int j = 0; j < 3; j++)
         col_ver[i][j] = vertices[i][j] * 1.0 ;*/

   /*for (int i = 0; i < vertices.size(); i++)
      for (int j = 0; j < 3; j++)
         col_ver[i][j] = vertices[i][j] * 0.5 + 0.5;*/
}

// -----------------------------------------------------------------------------------------------
//EJERCICIO EXTRA 1 P1
EstrellaZ :: EstrellaZ (unsigned n)
    : MallaInd ("estrella z")
{
   assert(n>1);

   const float PI = 3.14159265358979323846;

   //añadir el centro en (0.5, 0.5, 0)
   vertices.push_back({0.5, 0.5, 0.0});
   col_ver.push_back({1.0, 1.0, 1.0});

   //añadir resto de vértices
   for (unsigned i = 0; i < n; i++)
   {
      //float angulo = 2 * PI * i / n;
      float angulo = 2 * PI * i / n ;
      vertices.push_back({float(0.5 + 0.5 * cos(angulo)), float(0.5 + 0.5 * sin(angulo)), 0.0});
      col_ver.push_back({float(0.5 + 0.5 * cos(angulo)), float(0.5 + 0.5 * sin(angulo)), 0.0});
   }

   for (unsigned i = 0; i < n; i++)
   {
      //float angulo = 2 * PI * i / n;
      float angulo =  PI / n + 2 * PI * i / n ;
      vertices.push_back({float(0.5 + 0.25 * cos(angulo)), float(0.5 + 0.25 * sin(angulo)), 0.0});
      col_ver.push_back({float(0.5 + 0.25 * cos(angulo)), float(0.5 + 0.25 * sin(angulo)), 0.0});
   }

   //añadir los triangulos
   for (unsigned i = 1; i <= n ; i++)
   {
      triangulos.push_back({0, i, n + i});
   }

   triangulos.push_back({0, 1, 2 * n});

   for (unsigned i = 2; i <= n ; i++)
   {
      triangulos.push_back({0, i, n + i - 1});
   }

   /*
   //añadir color blanco al centro
   col_ver.push_back({1.0, 1.0, 1.0});

    //añadir los demas colores
   for (int i = 1; i <= 2 * n; i++)
   {
      col_ver.push_back({vertices[i][1], vertices[i][2], vertices[i][3]});
   }*/
}

//-----------------------------------------------------------------------------------------------
//EJERCICIO EXTRA 2 P1
CasaX :: CasaX ()
   : MallaInd ("casa x")
{
   vertices =
       {
           {0.0, 0.0, 0.0}, // 0
           {0.0, 0.0, +0.8}, // 1
           {0.0, +1.0, 0.0}, // 2
           {0.0, +1.0, +0.8}, // 3
           {+1.0, 0.0, 0.0}, // 4
           {+1.0, 0.0, +0.8}, // 5
           {+1.0, +1.0, 0.0}, // 6
           {+1.0, +1.0, +0.8}, // 7
           {+1.0, +1.3, +0.4},   //8
           {0.0, +1.3, +0.4},   //9
       };

   triangulos =
       {
           {0, 1, 3}, {0, 3, 2}, // X-
           {4, 7, 5},
           {4, 6, 7}, // X+ (+4)

           //{0, 5, 1},
           //{0, 4, 5}, // Y-
           //{2, 3, 7},
           //{2, 7, 6}, // Y+ (+2)

           {0, 6, 4},
           {0, 2, 6}, // Z-
           {1, 5, 7},
           {1, 7, 3}, // Z+ (+1)

           {6,8,7},
           {3,9,2},
           {7,8,3},
           {8,9,3},
           {6,2,8},
           {2,9,8},
       };
       /*
           {0.0, 0.0, 0.0}, // 0
           {0.0, 0.0, +0.8}, // 1
           {0.0, +1.0, 0.0}, // 2
           {0.0, +1.0, +0.8}, // 3
           {+1.0, 0.0, 0.0}, // 4
           {+1.0, 0.0, +0.8}, // 5
           {+1.0, +1.0, 0.0}, // 6
           {+1.0, +1.0, +0.8}, // 7
           {+1.0, +1.3, +0.4},   //8
           {0.0, +1.3, +0.4},   //9
       */


      col_ver.push_back({0, 0, 0});
      col_ver.push_back({0, 0, +0.8});
      col_ver.push_back({0.0, +1.0, 0.0});
      col_ver.push_back({0.0, +1.0, +0.8});
      col_ver.push_back({+1.0, 0.0, 0.0});
      col_ver.push_back({+1.0, 0.0, +0.8});
      col_ver.push_back({+1.0, +1.0, 0.0});
      col_ver.push_back({+1.0, +1.0, +0.8});
      col_ver.push_back({+1.0, +1.3, +0.4});
      col_ver.push_back({0.0, +1.3, +0.4});      
       
}

//-----------------------------------------------------------------------------------------------
//EJERCICIO EXTRA 3 P1
MallaTriangulo :: MallaTriangulo ()
: MallaInd ("triangulo")
{
   vertices =
      {
         {0.0, 0.0, +0.5},       //0
         {0.0, 0.0, -0.5},       //1
         {sqrt(2), 0.0, 0.0},    //2
      };

   triangulos =
      {
         {0, 1, 2},
      };
}

MallaCuadrado :: MallaCuadrado ()
: MallaInd ("cuadrado")
{
   vertices =
      {
         {+1.0, 0.0, +1.0},       //0
         {+1.0, 0.0, -1.0},       //1
         {-1.0, 0.0, -1.0},    //2
         {-1.0, 0.0, +1.0},    //3
      };

   triangulos =
      {
         {0, 1, 2},
         {0, 2, 3},
      };
}

MallaPiramideL :: MallaPiramideL ()
: MallaInd ("Piramide L")
{
   vertices =
      {
         {0.0, 0.0, 0.0},        //0
         {0.0, 0.0, +1.0},       //1
         {+1.0, 0.0, +1.0},      //2
         {+1.0, 0.0, +0.5},      //3
         {+0.5, 0.0, +0.5},      //4
         {+0.5, 0.0, 0.0},       //5
         {+0.5, +1.0, +0.5},     //6
      };

   triangulos =
      {
         {0, 4, 1},
         {4, 5, 0},
         {1, 3, 4},
         {1, 2, 3},
         {1, 2, 6},
         {2, 3, 6},
         {3, 4, 6},
         {4, 5, 6},
         {5, 0, 6},
         {0, 1, 6},
      };
}


//-----------------------------------------------------------------------------------------------
//EJERCICIO EXTRA 1 PRACTICA 2:
PiramideEstrellaZ::PiramideEstrellaZ(unsigned n)
: MallaInd ("Piramide Estrella Z")
{
   assert(n>1);

   const float PI = 3.14159265358979323846;

   //añadir el centro en (0.5, 0.5, 0)
   vertices.push_back({0.5, 0.5, 0.0});
   col_ver.push_back({0.5, 0.5, 0.0});

   //añadir resto de vértices
   for (unsigned i = 0; i < n; i++)
   {
      //float angulo = 2 * PI * i / n;
      float angulo = 2 * PI * i / n ;
      vertices.push_back({float(0.5 + 0.5 * cos(angulo)), float(0.5 + 0.5 * sin(angulo)), 0.0});
      col_ver.push_back({float(0.5 + 0.5 * cos(angulo)), float(0.5 + 0.5 * sin(angulo)), 0.0});
   }

   for (unsigned i = 0; i < n; i++)
   {
      //float angulo = 2 * PI * i / n;
      float angulo =  PI / n + 2 * PI * i / n ;
      vertices.push_back({float(0.5 + 0.25 * cos(angulo)), float(0.5 + 0.25 * sin(angulo)), 0.0});
      col_ver.push_back({float(0.5 + 0.25 * cos(angulo)), float(0.5 + 0.25 * sin(angulo)), 0.0});
   }

   //añadir el apice en (0.5, 0.5, 0.5)
   vertices.push_back({0.5, 0.5, 0.5});
   col_ver.push_back({1.0, 1.0, 1.0});

   //añadir los triangulos
   for (unsigned i = 1; i <= n ; i++)
   {
      triangulos.push_back({0, i, n + i});
   }

   triangulos.push_back({0, 1, 2 * n});

   for (unsigned i = 2; i <= n ; i++)
   {
      triangulos.push_back({0, i, n + i - 1});
   }


   //extra p2:
   for (unsigned i = 1; i <= n; i++)
   {
      triangulos.push_back({i, n + i, 2*n+1});
   }
   triangulos.push_back({1, 2*n, 2 * n +1});
   for (unsigned i = 2; i <= n ; i++)
   {
      triangulos.push_back({i, n+i-1, 2*n+1});
   }
   
}

//EJERCICIO EXTRA 2 PRACTICA 2:
RejillaY::RejillaY(unsigned n, unsigned m)
: MallaInd ("Rejilla Y")
{
   assert(n>1);
   assert(m>1);

   float x = 0.0;
   float z = 0.0;
   //añadir los vértices
   for (unsigned i = 0; i < n; i++)
   {
      for (unsigned j = 0; j < m; j++)
      {
         x = float(i) / (n-1);
         z = float(j) / (m-1);
         vertices.push_back({x, 0.0, z});
         col_ver.push_back({x, 0.0, z});
      }
   }
   
   //añadir los triangulos
   for (unsigned i = 0; i < m-1; i++)
   {
      for (unsigned j = 0; j < n-1; j++)
      {
         triangulos.push_back({ i*n+j+1, i*n+j, i*n+j+n});
         triangulos.push_back({ i*n+j+1, i*n+j+n, i*n+j+n+1});
      }
   }
   
}

//EJERCICIO EXTRA 3 PRACTICA 2:
MallaTorre::MallaTorre(unsigned n)
: MallaInd ("Torre")
{
   assert(n>0);

   //añadir los vértices
   for (unsigned i = 0; i <= n; i++)
   {
      vertices.push_back({0.0, float(i), 0.0});
      vertices.push_back({+1.0, float(i), 0.0});
      vertices.push_back({+1.0, float(i), +1.0});
      vertices.push_back({0.0, float(i), +1.0});
   }

   //añadir los triangulos
   for (unsigned i = 0; i < n; i++)
   {
      //triangulos.push_back({4*i, 4*i+1, 4*i+2});
      //triangulos.push_back({4*i, 4*i+2, 4*i+3});
      triangulos.push_back({4*i, 4*i+4, 4*i+1});   //T1 (0,1,4)
      triangulos.push_back({4*i+1, 4*i+4, 4*i+5});   //T2 (1,4,5)
      triangulos.push_back({4*i+2, 4*i+1, 4*i+5});   //T3 (2,1,5)
      triangulos.push_back({4*i+2, 4*i+5, 4*i+6});   //T4 (2,5,6)
      triangulos.push_back({4*i+3, 4*i+2, 4*i+6});   //T5 (3,2,6)
      triangulos.push_back({4*i+3, 4*i+6, 4*i+7});   //T6 (3,6,7)
      triangulos.push_back({4*i, 4*i+3, 4*i+7});   //T7 (0,3,7)
      triangulos.push_back({4*i, 4*i+7, 4*i+4});   //T8 (0,7,4)
   }

}

//----------------------------------------------------------------------
//PARA LA P3:
Rueda::Rueda(unsigned n)
: MallaInd("Rueda bicicleta")
{
   assert(n>0);
   const float PI = 3.14159265358979323846;

   //añadir los vértices
   vertices.push_back({0.0, 0.0, 0.0});
   vertices.push_back({0.0, 0.0, +0.05});
   //vertices.push_back({float(0.5 + 0.5 * cos(angulo)), float(0.5 + 0.5 * sin(angulo)), 0.0});
   for (unsigned i = 0; i < n; i++)
   {
      float angulo = 2 * PI * i / n;
      vertices.push_back({float(cos(angulo)), float(sin(angulo)), 0.0});
      vertices.push_back({float(cos(angulo)), float(sin(angulo)), +0.05});
   }

   //añadir los triangulos
   for (unsigned i = 2; i <= 2*n; i++)
   {
      triangulos.push_back({ i, i+2, i+1});
   }
   triangulos.push_back({ 3, 2, 2*n+1});
   triangulos.push_back({ 2, 2*n, 2*n+1});

   for (unsigned i = 2; i < 2*n; i=i+4)
   {
      triangulos.push_back({ 0, 1, i});
   }
}

SillinBici::SillinBici()
: MallaInd("Sillin bicicleta")
{
   vertices =
       {
           {-0.5, 0.0, -0.5}, // 0
           {-0.5, 0.0, +0.5}, // 1
           {-0.5, +0.25, -0.5}, // 2
           {-0.5, +0.25, +0.5}, // 3
           {+1.0, 0.0, -0.5}, // 4
           {+1.0, 0.0, +0.5}, // 5
           {+1.0, +0.25, -0.5}, // 6
           {+1.0, +0.25, +0.5}, // 7
           {+1.5, +0.2, 0.0}  // 8
       };

   triangulos =
       {
           {0, 1, 3}, {0, 3, 2}, // X-
           //{4, 7, 5},
           //{4, 6, 7}, // X+ (+4)
           {7, 8, 6}, {5, 8, 7}, {4, 6, 8}, {4, 8, 5},

           {0, 5, 1},
           {0, 4, 5}, // Y-
           {2, 3, 7},
           {2, 7, 6}, // Y+ (+2)

           {0, 6, 4},
           {0, 2, 6}, // Z-
           {1, 5, 7},
           {1, 7, 3} // Z+ (+1)
       };

}

BielaBici :: BielaBici()
: MallaInd ("Biela bicicleta")
{
      vertices =
       {
           {-0.1, -0.12, 0.0}, // 0 
           {-0.1, +0.12, 0.0}, // 1
           {-0.1, -0.12, +0.2}, // 2
           {-0.1, +0.12, +0.2}, // 3
           {+1.45, -0.12, 0.0}, // 4
           {+1.45, +0.12, 0.0}, // 5
           {+1.45, -0.12, +0.2}, // 6
           {+1.45, +0.12, +0.2}, // 7
           //{+1.5, +0.2, 0.0}  // 8
       };

   triangulos =
       {
           {0, 1, 3}, {0, 3, 2}, // X-
           {4, 7, 5},
           {4, 6, 7}, // X+ (+4)
           //{7, 8, 6}, {5, 8, 7}, {4, 6, 8}, {4, 8, 5},

           {0, 5, 1},
           {0, 4, 5}, // Y-
           {2, 3, 7},
           {2, 7, 6}, // Y+ (+2)

           {0, 6, 4},
           {0, 2, 6}, // Z-
           {1, 5, 7},
           {1, 7, 3} // Z+ (+1)
       };
}

PedalBici::PedalBici()
:MallaInd("Pedal bicicleta")
{
   vertices =
       {
           {-0.5, 0.0, -0.5}, // 0
           {+0.5, 0.0, -0.5}, // 1
           {-0.5, +0.25, -0.5}, // 2
           {+0.5, +0.25, -0.5}, // 3
           {-0.5, 0.0, +1.0}, // 4
           {+0.5, 0.0, +1.0}, // 5
           {-0.5, +0.25, +1.0}, // 6
           {+0.5, +0.25, +1.0}, // 7
           //{+1.5, +0.2, 0.0}  // 8
       };

   triangulos =
       {
           {0, 1, 3}, {0, 3, 2}, // X-
           {4, 7, 5},
           {4, 6, 7}, // X+ (+4)
           //{7, 8, 6}, {5, 8, 7}, {4, 6, 8}, {4, 8, 5},

           {0, 5, 1},
           {0, 4, 5}, // Y-
           {2, 3, 7},
           {2, 7, 6}, // Y+ (+2)

           {0, 6, 4},
           {0, 2, 6}, // Z-
           {1, 5, 7},
           {1, 7, 3} // Z+ (+1)
       };  
}

PlatoBici::PlatoBici(unsigned n)
:MallaInd("Plato bicicleta")
{
   assert(n>0);
   const float PI = 3.14159265358979323846;

   vertices.push_back({0.0, 0.0, 0.0});

   for (unsigned i = 0; i < n; i++)
   {
      float angulo = 2 * PI * i / n;
      vertices.push_back({float(cos(angulo)), float(sin(angulo)), 0.0});
   }

   for (unsigned i = 1; i <= n; i++)
   {
      triangulos.push_back({ 0, i, i+1});
   }
   triangulos.push_back({ 0, n, 1});

}

RampaBici::RampaBici()
:MallaInd("Rampa bici 2")
{
   vertices =
       {
           {-1.0, 0.0, 0.0}, // 0
           {-1.0, 0.0, +3.0}, // 1
           {+9.0, +3.42, 0.0}, // 2
           {+9.0, +3.42, +3.0}, // 3
       };

   triangulos =
       {
           {0, 1, 2}, {2, 3, 1}
       };
}
