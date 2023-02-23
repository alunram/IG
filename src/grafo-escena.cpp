//Nombre: Alvaro, Apellidos: Luna Ramirez, Titulacion: GIM, correo: alvaroluna@correo.ugr.es, DNI: 
// *********************************************************************
// **
// ** Gestión de una grafo de escena (implementación)
// ** Copyright (C) 2016 Carlos Ureña
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

#include "ig-aux.h"
#include "grafo-escena.h"
#include "malla-ind.h"
#include "malla-revol.h"

using namespace std ;

// *********************************************************************
// Entrada del nodo del Grafo de Escena

// ---------------------------------------------------------------------
// Constructor para entrada de tipo sub-objeto
int valoridentificador=1;

EntradaNGE::EntradaNGE( Objeto3D * pObjeto )
{
   assert( pObjeto != NULL );
   tipo   = TipoEntNGE::objeto ;
   objeto = pObjeto ;
}
// ---------------------------------------------------------------------
// Constructor para entrada de tipo "matriz de transformación"

EntradaNGE::EntradaNGE( const Matriz4f & pMatriz )
{
   tipo    = TipoEntNGE::transformacion ;
   matriz  = new Matriz4f() ; // matriz en el heap, puntero propietario
   *matriz = pMatriz ;
}

// ---------------------------------------------------------------------
// Constructor para entrada de tipo "matriz de transformación"

EntradaNGE::EntradaNGE( Material * pMaterial )
{
   assert( pMaterial != NULL );
   tipo     = TipoEntNGE::material ;
   material = pMaterial ;
}

// -----------------------------------------------------------------------------
// Destructor de una entrada

EntradaNGE::~EntradaNGE()
{
   /**  no fnciona debido a que se hacen copias (duplicados) de punteros
   if ( tipo == TipoEntNGE::transformacion )
   {
      assert( matriz != NULL );
      delete matriz ;
      matriz = NULL ;
   }
   * **/
}

// *****************************************************************************
// Nodo del grafo de escena: contiene una lista de entradas
// *****************************************************************************

// -----------------------------------------------------------------------------
// Visualiza usando OpenGL


void NodoGrafoEscena::visualizarGL( ContextoVis & cv )
{
   leerFijarColVertsCauce(cv);
   // COMPLETAR: práctica 3: recorrer las entradas y visualizar cada nodo.
   // ........
   //mio:
   //esta en las diapositivas del tema 2, pg173
   //guarda modelview actual
   cv.cauce->pushMM();

   //color?????
   const Tupla4f color_previo = leerFijarColVertsCauce(cv);

   //material P4:
   Material * cvMaterial = cv.material_act;
   if (!cv.iluminacion){
      cvMaterial = nullptr;
   }

   //rcorrer todas las entradas del array que hay en el nodo:
   for (unsigned i = 0; i < entradas.size(); i++)
   {
      switch (entradas[i].tipo)
      {
      case TipoEntNGE::objeto:
         entradas[i].objeto->visualizarGL(cv);
         break;
      
      case TipoEntNGE::transformacion :
         cv.cauce->compMM(*(entradas[i].matriz));
         break;

      case TipoEntNGE::material:
         //esto ya sera de la P4 supongo  
         //si. diap 208 t3:
         if (cv.iluminacion){
            //entradas[i].material->activar( cv );
               
            cv.material_act = entradas[i].material;
            cv.material_act->activar(cv);
         }
         break;
      }
   }
   
   // restaurar el color previamente fijado
   cv.cauce->fijarColor(color_previo);

   //restauramos material:
   //if (cvMaterial != nullptr){
      //cv.material_act = cvMaterial;
     // cv.material_act->activar(cv);
   //}

   if (cvMaterial != nullptr && cv.material_act != cvMaterial)
      cvMaterial->activar(cv);

   //pop de modelview
   cv.cauce->popMM();


   // COMPLETAR: práctica 4: en la práctica 4, si 'cv.iluminacion' es 'true',
   // se deben de gestionar los materiales:
   //   1. guardar puntero al material activo al inicio (está en cv.material_act)
   //   2. si una entrada des de tipo material, activarlo y actualizar 'cv.material_act'
   //   3. al finalizar, restaurar el material activo al inicio (si es distinto del actual)

}




// *****************************************************************************
// visualizar pura y simplemente la geometría, sin colores, normales, coord. text. etc...

void NodoGrafoEscena::visualizarGeomGL( ContextoVis & cv )
{
   // comprobar que hay un cauce en 'cv' 
   assert( cv.cauce != nullptr );
  

   // COMPLETAR: práctica 3
   //
   // Este método hace un recorrido de las entradas del nodo, parecido a 'visualizarGL', teniendo 
   // en cuenta estos puntos:
   //
   // - usar push/pop de la matriz de modelado al inicio/fin (al igual que en visualizatGL)
   // - recorrer las entradas, llamando recursivamente a 'visualizarGeomGL' en los nodos u objetos hijos
   // - ignorar el color o identificador del nodo (se supone que el color ya está prefijado antes de la llamada)
   // - ignorar las entradas de tipo material, y la gestión de materiales (se usa sin iluminación)

   // .......
   //mio:
   //guarda modelview actual
   cv.cauce->pushMM();

   //rcorrer todas las entradas del array que hay en el nodo:
   for (unsigned i = 0; i < entradas.size(); i++)
   {
      switch (entradas[i].tipo)
      {
      case TipoEntNGE::objeto:
         entradas[i].objeto->visualizarGeomGL(cv);
         break;
      
      //esto no se si hace falta:
      case TipoEntNGE::transformacion :
         cv.cauce->compMM(*(entradas[i].matriz));
         break;
      }
   }

   //pop de modelview
   cv.cauce->popMM();

}



// -----------------------------------------------------------------------------

NodoGrafoEscena::NodoGrafoEscena()
{

}

// -----------------------------------------------------------------------------
// Añadir una entrada (al final).
// genérica (de cualqiuer tipo de entrada)

unsigned NodoGrafoEscena::agregar( const EntradaNGE & entrada )
{
   // COMPLETAR: práctica 3: agregar la entrada al nodo, devolver índice de la entrada agregada
   // ........
   //mio:
   entradas.push_back(entrada);

   return (entradas.size()-1) ; // sustituir por lo que corresponda ....

}
// -----------------------------------------------------------------------------
// construir una entrada y añadirla (al final)
// objeto (copia solo puntero)

unsigned NodoGrafoEscena::agregar( Objeto3D * pObjeto )
{
   return agregar( EntradaNGE( pObjeto ) );
}
// ---------------------------------------------------------------------
// construir una entrada y añadirla (al final)
// matriz (copia objeto)

unsigned NodoGrafoEscena::agregar( const Matriz4f & pMatriz )
{
   return agregar( EntradaNGE( pMatriz ) );
}
// ---------------------------------------------------------------------
// material (copia solo puntero)
unsigned NodoGrafoEscena::agregar( Material * pMaterial )
{
   return agregar( EntradaNGE( pMaterial ) );
}

// devuelve el puntero a la matriz en la i-ésima entrada
Matriz4f * NodoGrafoEscena::leerPtrMatriz( unsigned indice )
{
   // COMPLETAR: práctica 3: devolver puntero la matriz en ese índice
   //   (debe de dar error y abortar si no hay una matriz en esa entrada)
   // ........(sustituir 'return nullptr' por lo que corresponda)
   //mio:
   //esta en la diap 183 del tema2
   assert(indice < entradas.size());
   assert(entradas[indice].tipo == TipoEntNGE::transformacion);
   assert(entradas[indice].matriz != nullptr);

   return entradas[indice].matriz ;


}
// -----------------------------------------------------------------------------
// si 'centro_calculado' es 'false', recalcula el centro usando los centros
// de los hijos (el punto medio de la caja englobante de los centros de hijos)

void NodoGrafoEscena::calcularCentroOC()
{

   // COMPLETAR: práctica 5: calcular y guardar el centro del nodo
   //    en coordenadas de objeto (hay que hacerlo recursivamente)
   //   (si el centro ya ha sido calculado, no volver a hacerlo)
   // ........
   //mio:
   Matriz4f matriz_ = MAT_Ident();
   Tupla3f centro, sum = {0.0, 0.0, 0.0};
   float centros = 0;

   if(!centrocalculado){
      for (unsigned i = 0; i < entradas.size(); i++){
         if (entradas[i].tipo == TipoEntNGE::objeto){
            entradas[i].objeto->calcularCentroOC();
            sum = sum + (matriz_ * entradas[i].objeto->leerCentroOC());
            centros++;
         }else if (entradas[i].tipo == TipoEntNGE::transformacion){
               matriz_ = matriz_ * (*entradas[i].matriz);
            }
      }
      centro = sum/centros;
      ponerCentroOC(centro);
      centrocalculado = true;
   }
}
// -----------------------------------------------------------------------------
// método para buscar un objeto con un identificador y devolver un puntero al mismo

bool NodoGrafoEscena::buscarObjeto
(
   const int         ident_busc, // identificador a buscar
   const Matriz4f &  mmodelado,  // matriz de modelado
   Objeto3D       ** objeto,     // (salida) puntero al puntero al objeto
   Tupla3f &         centro_wc   // (salida) centro del objeto en coordenadas del mundo
)
{
   assert(0 < ident_busc);

   // COMPLETAR: práctica 5: buscar un sub-objeto con un identificador
   // Se deben de dar estos pasos:
   Matriz4f mmodeladoaux = mmodelado;

   // 1. calcula el centro del objeto, (solo la primera vez)
   // ........
   //mio:
   if (!centrocalculado)
      calcularCentroOC(); //¿solo la primera vez?

   // 2. si el identificador del nodo es el que se busca, ya está (terminar)
   // ........
   //mio:
   if (leerIdentificador() == ident_busc){
      centro_wc = mmodelado * leerCentroOC();   //escribir centro
      if (objeto != nullptr){
         *objeto = this;   //escribir objeto
      }
      
      return true; //terminar
   }

   // 3. El nodo no es el buscado: buscar recursivamente en los hijos
   //    (si alguna llamada para un sub-árbol lo encuentra, terminar y devolver 'true')
   // ........
   //mio:
   for (unsigned i = 0; i < entradas.size(); i++){
      if (entradas[i].tipo == TipoEntNGE::objeto){
         if (entradas[i].objeto->buscarObjeto(ident_busc, mmodeladoaux, objeto, centro_wc)){
            return true;
         }
      }else if (entradas[i].tipo == TipoEntNGE::transformacion){
            mmodeladoaux = mmodeladoaux * (*entradas[i].matriz);
            }
   }

   // ni este nodo ni ningún hijo es el buscado: terminar
   return false;
}


//los adicionales estan en el modelo-jer
//EXAMEN P1, P2, P3
Articulado::Articulado(){
    NodoGrafoEscena *cubo = new NodoGrafoEscena();
    NodoGrafoEscena *objeto = new NodoGrafoEscena();
    NodoGrafoEscena *cilindro = new NodoGrafoEscena();
    NodoGrafoEscena *cilindroconesfera1 = new NodoGrafoEscena();
    NodoGrafoEscena *cilindroconesfera2 = new NodoGrafoEscena();
    NodoGrafoEscena *cilindroconesfera3 = new NodoGrafoEscena();
    NodoGrafoEscena *cilindrosconesferas = new NodoGrafoEscena();

   cubo->agregar(MAT_Escalado(0.5, 0.5, 0.5));
   cubo->agregar(MAT_Traslacion({0.0, 1.0, 0.0}));
   cubo->agregar(new Cubo());

   objeto->agregar(cubo);

   cilindro->agregar(MAT_Escalado(0.25, 0.5, 0.25));
   cilindro->agregar(new Cilindro(20,20));
   cilindro->agregar(MAT_Traslacion({0.0, 1.0, 0.0}));
   cilindro->agregar(new Cilindro(20,20));
   cilindro->agregar(MAT_Traslacion({0.0, 1.0, 0.0}));
   cilindro->agregar(new Cilindro(20,20));

   //cilindroconesfera->agregar(MAT_Traslacion({0.0, 1.0, 0.0}));
   cilindroconesfera1->agregar(cilindro);
   cilindroconesfera1->agregar(MAT_Traslacion({0.0, 1.5, 0.0}));
   cilindroconesfera1->agregar(MAT_Escalado(0.25, 0.25, 0.25));
   cilindroconesfera1->agregar(new Esfera(20,20));

   unsigned int ind1 = cilindrosconesferas->agregar(MAT_Rotacion(0, {0.0, 1.0, 0.0}));
   giroy = cilindrosconesferas->leerPtrMatriz(ind1);
   cilindrosconesferas->agregar(MAT_Traslacion({0.0, 1.0, 0.0}));
   cilindrosconesferas->agregar(cilindroconesfera1);

   unsigned int ind3 = cilindroconesfera2->agregar(MAT_Escalado(1, 1, 1));
   cilindroconesfera2->agregar(MAT_Traslacion({0.0, 1.5, 0.0}));
   cilindroconesfera2->agregar(MAT_Rotacion(-75, {0, 0, 1}));
   cilindroconesfera2->agregar(cilindroconesfera1);
   tamanio = cilindroconesfera2->leerPtrMatriz(ind3);

   unsigned int ind2 = cilindrosconesferas->agregar(MAT_Rotacion(0, {0.0, 0.0, 1.0})); //este giro no me sale bien
   giro2 = cilindrosconesferas->leerPtrMatriz(ind2);

   cilindrosconesferas->agregar(cilindroconesfera2);

   cilindroconesfera3->agregar(MAT_Traslacion({0.0, 1.5, 0.0}));
   cilindroconesfera3->agregar(MAT_Rotacion(-75, {0, 0, 1}));
   cilindroconesfera3->agregar(MAT_Traslacion({0.0, 1.5, 0.0}));
   cilindroconesfera3->agregar(MAT_Rotacion(270, {0, 0, 1}));
   cilindroconesfera3->agregar(cilindroconesfera1);

   cilindrosconesferas->agregar(cilindroconesfera3);

   objeto->agregar(cilindrosconesferas);
   
   agregar(objeto);

}

unsigned Articulado::leerNumParametros() const
{
   return parametros;
}

void Articulado::actualizarEstadoParametro(const unsigned iParam, const float tSec){
    const float velocidad = 2*M_PI*2.5;
    float angulo = 2 * M_PI * tSec * velocidad ;

    float a = -75;
    float b = 40;
    float c = a + b * sin(2.0 * M_PI * tSec*0.1);

    float d = 0.7;
    float e = 0.4;
    float f = d + e * fabs(sin(2.0 * M_PI * tSec*0.3));
   

    using namespace std;
    cout << "Parametro: " << iParam << endl;

    switch (iParam)
    {
      case 0:
        (*giroy) = MAT_Rotacion(angulo, {0, 1, 0}); //una vuelta cada 5 seg
        break;
      case 1:
        //(*giro2) = MAT_Rotacion(c, {0, 0, 1});   //no me sale bien
        break;
      case 2:
        (*tamanio) = MAT_Escalado(f, 1, 1); //al estar girado la longitud de los cilindros es el eje x
        break;
    default:
        break;
    }
}

NodoCubo24::NodoCubo24()
{
   Textura *text = new Textura("window-icon.jpg");
   Material *mat = new Material(text, 1, 1, 1, 50);

   agregar(mat);
   agregar(new Cubo24());
}

NodoDiscoP4::NodoDiscoP4()
{
   ponerNombre("Nodo ejercicio adicional práctica 4, examen 27 enero");

   Textura *text = new Textura("cuadricula.jpg");
   Material *material_disco = new Material(text, 0.4, 0.5, 0.5, 5.0);

   agregar( material_disco );
   agregar( new MallaDiscoP4() );
}

//Ejercicio P5
GrafoEsferasP5::GrafoEsferasP5()
{
   const unsigned
      n_filas_esferas = 8,
      n_esferas_x_fila = 5;
   const float
      e = 0.4/n_esferas_x_fila ;

   agregar( MAT_Escalado( e,e,e ));
   unsigned int  identificadoresfera = 1000;
   for( unsigned i = 0 ; i < n_filas_esferas ; i++ )
   {
      NodoGrafoEscena * fila_esferas = new NodoGrafoEscena() ;
      for( unsigned j = 0 ; j < n_esferas_x_fila ; j++ )
      {
         MallaInd * esfera = new Esfera(40, 40) ;
         
         esfera->ponerIdentificador(identificadoresfera);

         unsigned numero = i*j+j;
         string nombre = "Esfera ";
         esfera->ponerNombre(nombre);

         fila_esferas->agregar( MAT_Traslacion({2.2, 0.0, 0.0}));
         fila_esferas->agregar( esfera );
         identificadoresfera++;
      }
      
      agregar( fila_esferas );
      agregar( MAT_Traslacion( {0.0, 0.0, 5.0 }));
   }
}


//EJERCICIO EXAMNE P4
NodoEXP4::NodoEXP4()
{
   Textura *text = new Textura("textura-exp4-v2.jpg"); //foto de prado
   Material *material_tetraedro = new Material(text, 0.5, 0.5, 0.5, 80);

   agregar( material_tetraedro );
   agregar( new MallaEXP4() );
}

EsferaEXP5::EsferaEXP5(unsigned n)
{
   agregar(MAT_Escalado(M_PI/n, M_PI/n, M_PI/n)); //con esto el radio pasaria de 1 a pi/n, pero no se me ve como en la foto del examen
   Esfera *esfera = new Esfera(20, 20);
   esfera->ponerIdentificador(valoridentificador);
   esfera->ponerNombre("Esfera examen");
   agregar( esfera );

   valoridentificador++;

   //para que la camara no mire a las esferas cambio el metodo seleccion. he puesto esto, pero no sirve. no se el motivo:
   /*
      EsferaEXP5 * pesf = dynamic_cast<EsferaEXP5 *> (objetoencontrado);
      if(pesf == nullptr){
         escena->camaraActual()->mirarHacia(puntocentro);
         cout << "\nSe ha encontrado un objeto. Identificador: " << ident << ". Nombre: " << objetoencontrado->leerNombre() << "\n";
      }else{
         cout << "\nNo se apunta al objeto esfera del examen de la p5 ";
         objetoencontrado->ponerColor({1, 0.5, 0.5});
      } 
   */
}

AnilloEXP5::AnilloEXP5(unsigned n)
{
   assert(n>3);
   ponerIdentificador(0);
   
   for (int i = 0; i < n; i++)
   {
      agregar(new EsferaEXP5(n));
      double angulo = 360/n; 
      agregar(MAT_Rotacion(angulo, {0, 1, 0}));
      agregar(MAT_Traslacion({1.0, 0.0, 0.0}));
   }
   
}