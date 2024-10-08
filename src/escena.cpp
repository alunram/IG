//Nombre: Alvaro, Apellidos: Luna Ramirez, Titulacion: GIM, correo: alvaroluna@correo.ugr.es, DNI: 

#include "ig-aux.h"
#include "escena.h"

#include "objeto3d.h"
#include "malla-ind.h"
#include "malla-revol.h"
#include "practicas.h"
#include "camara.h"
#include "materiales-luces.h"
#include "seleccion.h"
#include "modelo-jer.h"
#include "latapeones.h"

// -----------------------------------------------------------------------------------------------

Escena::Escena()
{
   // COMPLETAR: Práctica 4: inicializar 'col_fuentes' y 'material_ini'
   // ...
   //mio:
   col_fuentes = new Col2Fuentes();
   material_ini = new Material();

   // COMPLETAR: Práctica 5: hacer 'push_back' de varias camaras perspectiva u ortogonales,
   // (sustituir la cámara orbital simple ('CamaraOrbitalSimple') por varias cámaras de 3 modos ('Camara3Modos')
   //camaras.push_back(new CamaraOrbitalSimple()); //esta se va a quitar
   camaras.push_back(new Camara3Modos(true,{5.0, 1.0, 1.0}, 1.0, {2.0, 1.0, 1.0}, 50.0));
   //camaras.push_back(new Camara3Modos());
   //camaras.push_back(new Camara3Modos());
   camaras.push_back( new Camara3Modos(false,{6.5, 6.5, 6.5}, 1.0, {4.0, 4.0, 4.0}, 65.0)); //alzado ortogonal
   camaras.push_back( new Camara3Modos(true, {4.0, 3.0, 1.0}, 1.0, {2.0, 1.0, 4.0}, 80.0)); //perspectiva
}
// -----------------------------------------------------------------------------------------------
// visualiza la escena en la ventana actual, usando la configuración especificada en 'cv'

void Escena::visualizarGL(ContextoVis &cv)
{
   // static unsigned int count = 0 ;
   // log("entra",count);
   // count ++ ;
   CError();
   using namespace std;

   // recuperar el cauce actual de 'cv' en 'cauce', activarlo
   Cauce *cauce = cv.cauce;
   assert(cauce != nullptr);
   cauce->activar();

   CError();

   // recuperar la cámara actual de esta escena y  fijar las matrices 'modelview'
   // y 'projection' en el cauce gráfico (es decir: activar la cámara actual)
   CamaraInteractiva *camara = camaras[ind_camara_actual];
   assert(camara != nullptr);
   const float ratio_vp = float(cv.ventana_tam_y) / float(cv.ventana_tam_x);
   camara->fijarRatioViewport(ratio_vp);
   camara->activar(*cauce);

   // log("por aquí ii");
   CError();

   // dibujar los ejes, si procede
   if (cv.dibujar_ejes)
      DibujarEjesSolido(*cauce); // ver 'ig-aux.cpp' para la definición.

   // fijar el color por defecto (inicial) en el cauce para dibujar los objetos
   // (es blanco debido a que el fondo se rellena con un color oscuro y debe contrastar).
   cauce->fijarColor(1.0, 1.0, 1.0);

   // fijar el modo de normales (útil para la práctica 4)
   cauce->fijarUsarNormalesTri(cv.usar_normales_tri);

   // COMPLETAR: Práctica 1: Configurar el modo de polígonos con
   // 'glPolygonMode' en función del modo guardado en 'cv.modo_visu',
   // que puede ser: puntos,lineas o relleno.
   //
   // ...................
   // mio:
   GLenum modov;
   CError();

   switch (cv.modo_visu)
   {
   case ModosVisu::lineas:
      modov = GL_LINE;
      break;

   case ModosVisu::puntos:
      modov = GL_POINT;
      break;

   case ModosVisu::relleno:
      modov = GL_FILL;
      break;
   }

   CError();

   glPolygonMode(GL_FRONT_AND_BACK, modov);

   CError();

   if (cv.iluminacion)
   {
      // COMPLETAR: Práctica 4: activar evaluación del MIL (y desactivar texturas)
      // * habilitar evaluación del MIL en el cauce (fijarEvalMIL)
      // * activar la colección de fuentes de la escena
      // * activar el material inicial
      // ....
      //mio:
      cauce->fijarEvalMIL(true);
      cauce->fijarEvalText(false);

      col_fuentes->activar(*(cv.cauce));
      material_ini->activar(cv);
   }
   else // si la iluminación no está activada, deshabilitar MIL y texturas
   {
      cauce->fijarEvalMIL(false);
      cauce->fijarEvalText(false);
   }

   // log("recupero objeto");
   CError();

   // recuperar el objeto actual de esta escena
   Objeto3D *objeto = objetos[ind_objeto_actual];
   assert(objeto != nullptr);

   // COMPLETAR: Práctica 1: visualizar el objeto actual ('objeto')
   //mio:
   objeto->visualizarGL(cv);

   // Visualizar las aristas del objeto, si procede (es decir: en modo relleno, con
   // visualización de aristas activada y siempre que no estemos en el
   // 'modo de selección' de la prác.5)

   if (cv.dibujar_aristas && cv.modo_visu == ModosVisu::relleno && !cv.modo_seleccion)
   {
      // desactivar iluminación y texturas (podrían estarlo a partir de prác. 4)
      cv.cauce->fijarEvalMIL(false);
      cv.cauce->fijarEvalText(false);

      // COMPLETAR: Práctica 1: visualizar únicamente las aristas del objeto actual
      // - hay que invocar 'visualizarGeomGL' para el objeto actual de la escena ('objeto')
      // - antes de eso debemos de poner el cauce en un estado adecuado:
      //      - fijar el color a negro
      //      - fijar el modo de polígonos a modo 'lineas'
      //
      // ...........
      //mio:
      cv.cauce->fijarColor(0.0,0.0,0.0);
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //german lo tiene diferente

      objeto->visualizarGeomGL(cv);

      if ( cv.visualizar_normales && !cv.modo_seleccion )
         visualizarNormales( cv );
   }
}

// -----------------------------------------------------------------------------------------------
// pasa la cámara actual a la siguiente

void Escena::siguienteCamara()
{
   assert(ind_camara_actual < camaras.size());
   ind_camara_actual = (ind_camara_actual + 1) % camaras.size();
   using namespace std;
   cout << "Cámara actual cambiada a: " << (ind_camara_actual + 1) << " (de " << camaras.size() << ")" << endl;
}

void Escena::visualizarNormales( ContextoVis & cv )
{
   // recuperar el objeto raiz de esta escena y comprobar que está ok.
   bool ilum_ant = cv.iluminacion ;
   assert( cv.cauce != nullptr );
   Objeto3D * objeto = objetos[ind_objeto_actual] ; assert( objeto != nullptr );

   // configurar el cauce:
   cv.cauce->fijarEvalMIL( false );
   cv.cauce->fijarEvalText( false );

   // configurar el contexto de visualizacion
   cv.visualizando_normales = true ;   // hace que MallaInd::visualizarGL visualize las normales.
   cv.iluminacion           = false ;

   // visualizar objeto actual
   objetos[ind_objeto_actual]->visualizarGL( cv );

   // restaurar atributos cambiados en el contexto de visualización
   cv.visualizando_normales = false ;
   cv.iluminacion = ilum_ant ;
}

// -----------------------------------------------------------------------------------------------
// pasa el objeto actual al siguiente

void Escena::siguienteObjeto()
{
   if (objetos.size() == 0)
      return;
   assert(ind_objeto_actual < objetos.size());
   ind_objeto_actual = (ind_objeto_actual + 1) % objetos.size();
   using namespace std;
   cout << "Objeto actual cambiado a: " << objetoActual()->leerNombre()
        << " (" << (ind_objeto_actual + 1) << "/" << objetos.size() << ")." << endl;
}

// -----------------------------------------------------------------------------------------------
// devuelve puntero al objeto actual

Objeto3D *Escena::objetoActual()
{
   assert(ind_objeto_actual < objetos.size());
   assert(objetos[ind_objeto_actual] != nullptr);
   return objetos[ind_objeto_actual];
}
// -----------------------------------------------------------------------------------------------
// devuelve un puntero a la cámara actual

CamaraInteractiva *Escena::camaraActual()
{
   assert(ind_camara_actual < camaras.size());
   assert(camaras[ind_camara_actual] != nullptr);
   return camaras[ind_camara_actual];
}
// -----------------------------------------------------------------------------------------------
// devuelve un puntero a la colección de fuentes actual

ColFuentesLuz *Escena::colFuentes()
{
   assert(col_fuentes != nullptr);
   return col_fuentes;
}
// -----------------------------------------------------------------------------------------------

Escena1::Escena1()
{
   using namespace std;
   cout << "Creando objetos de escena 1 .... " << flush;

   // añadir el objeto 'Cubo' a la lista de objetos de esta escena:
   //objetos.push_back(new Cubo());

   // COMPLETAR: Práctica 1: creación del resto objetos de la práctica 1
   // Añadir objetos al vector 'objetos', con:
   //     objetos.push_back( new .... )
   // .........
   //mio:
   unsigned nestrella = 8;
   //objetos.push_back(new PiramideCruz());
   //objetos.push_back(new Rueda(50));
   objetos.push_back(new Cubo());
   objetos.push_back(new CuboTejado());
   objetos.push_back(new Tetraedro()); 
   // cuando haga mas objetos se veran poniendolo aqui
   objetos.push_back(new CuboColores());
   objetos.push_back(new EstrellaZ(nestrella));
   objetos.push_back(new CasaX());
   objetos.push_back(new MallaTriangulo());
   objetos.push_back(new MallaCuadrado());
   objetos.push_back(new MallaPiramideL());
   //objetos.push_back(new examenlunes());

   cout << "hecho." << endl
        << flush;
}

// -------------------------------------------------------------------------
// COMPLETAR: Práctica 2
// Añadir la implementación del constructor de la clase Escena2 para construir
// los objetos que se indican en los guiones de las práctica 2
// .......
//mio:
Escena2::Escena2()
{
   using namespace std;

   cout << "Creando objetos de escena 2 .... " << flush;


   //aquí pondré los objetos.push_back();
   //objetos.push_back(new Cilindro(20, 20));
   //objetos.push_back(new CopaRevol(32, 32));
   objetos.push_back(new Cilindro(50, 50));
   objetos.push_back(new Cono(15, 35));
   //objetos.push_back(new MallaRevolPLY("peon.ply", 20));
   //objetos.push_back(new MallaPLY("ant.ply"));
   //objetos.push_back(new MallaPLY("beethoven.ply"));
   //objetos.push_back(new MallaPLY("big_dodge.ply"));
   objetos.push_back(new Esfera(40, 40));
   objetos.push_back(new PiramideEstrellaZ(8));
   objetos.push_back(new RejillaY(10,10));
   //objetos.push_back(new MallaTorre(5));
   //objetos.push_back(new circunferenciaprueba(1,20)); //es una circunferencia
   

   cout << "hecho." << endl
        << flush;
}

// -------------------------------------------------------------------------
// COMPLETAR: Práctica 3
// Añadir la implementación del constructor de la clase Escena3 para construir
// los objetos que se indican en los guiones de las práctica 3
// .......
//mio:
Escena3:: Escena3()
{
   using namespace std;

   cout << "Creando objetos de escena 3 .... " << flush;

   //aquí pondré los objetos.push_back();
   //objetos.push_back(new ahoraborroesto(10));
   //objetos.push_back(new Articulado());
   objetos.push_back(new P3());
   //objetos.push_back(new Bici());
   //objetos.push_back(new GrafoEstrellaX(6));
   //objetos.push_back(new GrafoCubos());
   //objetos.push_back(new pruebaexamen(5));


   cout << "hecho." << endl
        << flush;
}

// ----------------------------------------------------------------------
// COMPLETAR: Práctica 4
// Añadir la implementación del constructor de la clase Escena4 para construir
// los objetos que se indican en los guiones de las práctica 4
// .......
//mio:
Escena4:: Escena4()
{
   using namespace std;

   cout << "Creando objetos de escena 4 .... " << flush;

   //aquí pondré los objetos.push_back();
   objetos.push_back(new NodoEXP4());
   objetos.push_back(new LataPeones());
   objetos.push_back(new NodoCubo24);
   objetos.push_back(new NodoDiscoP4());


   cout << "hecho." << endl
        << flush;
}

// ----------------------------------------------------------------------
// COMPLETAR: Práctica 5
// Añadir la implementación del constructor de la clase Escena5 para construir
// los objetos que se indican en los guiones de las práctica 5
// .......
//mio:
Escena5:: Escena5()
{
   using namespace std;

   cout << "Creando objetos de escena 5 .... " << flush;

   //aquí pondré los objetos.push_back();
   unsigned valor = 16;
   objetos.push_back(new AnilloEXP5(valor));
   objetos.push_back(new VariasLatasPeones());
   objetos.push_back(new GrafoEsferasP5());
   
   cout << "hecho." << endl
        << flush;
}
