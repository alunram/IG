//Nombre: Alvaro, Apellidos: Luna Ramirez, Titulacion: GIM, correo: alvaroluna@correo.ugr.es, DNI: 
#include "ig-aux.h"
#include "practicas.h"
#include "camara.h"
#include "fbo.h"
#include "seleccion.h"
#include "grafo-escena.h"

// framebuffer object usado para selección
static Framebuffer * fbo = nullptr ;

// ---------------------------------------------------------------------

Framebuffer * FBOActual()
{
   return fbo ;
}

// ---------------------------------------------------------------------
// fijar el color actual en el cauce usando un identificador entero

/*void FijarColVertsIdent( Cauce & cauce, const int ident )  // 0 ≤ ident < 2^24
{
   // COMPLETAR: práctica 5: fijar color actual de OpenGL usando 'ident' (con 'cauce.fijarColor')
   // .....
   //mio: AQUI ME FALLABA
   cauce.fijarColor(ident, ident, ident);
}*/
void FijarColVertsIdent(Cauce &cauce, const int ident) // 0 ≤ ident < 2^24
{
   // COMPLETAR: práctica 5: fijar color actual de OpenGL usando 'ident' (con 'cauce.fijarColor')
   // .....
   const unsigned char
       byteR = (ident) % 0x100U,
       byteG = (ident / 0x100U) % 0x100U,
       byteB = (ident / 0x10000U) % 0x100U;

   cauce.fijarColor(float(byteR) / 255.0f, float(byteG) / 255.0f, float(byteB) / 255.0f);
}

// ----------------------------------------------------------------------------------
// leer un identificador entero codificado en el color de un pixel en el
// framebuffer activo actualmente

int LeerIdentEnPixel( int xpix, int ypix )
{
   // COMPLETAR: práctica 5: leer el identificador codificado en el color del pixel (x,y)
   // .....(sustituir el 'return 0' por lo que corresponda)
   // .....
   //mio:
   unsigned char bytes[3]; // Para guardar los tres bytes
   glReadPixels (xpix, ypix, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, bytes); // leer los 3 bytes del frame-buffer
   
   int result = bytes[0] + 256*bytes[1] + 256*256*bytes[2];

   return result;

   //return 0 ;
}

// -------------------------------------------------------------------------------
// Función principal de selección, se llama al hacer click con el botón izquierdo
//
// (x,y)       = posición donde se ha hecho click en coordenadas del sistema de ventanas (enteras)
// objeto_raiz = objeto raiz (no subobjeto de otro) que se está visualizando en la ventana
// cv_dib      = contexto de visualización usado para dibujar el objeto
//
// devuelve: true si se ha seleccionado algún objeto, false si no

bool Seleccion( int x, int y, Escena * escena, ContextoVis & cv_dib )
{
   using namespace std ;
   assert( escena != nullptr );

   // COMPLETAR: práctica 5:
   // Visualizar escena en modo selección y leer el color del pixel en (x,y)
   // Se deben de dar estos pasos:

   //cout << "Seleccion( x == " << x << ", y == " << y << ", obj.raíz ==  " << objeto_raiz.leerNombre() << " )" << endl ;

   // 1. Crear (si es necesario) y activar el framebuffer object (fbo) de selección
   // .........
   //mio:
   if (fbo == nullptr)
      fbo = new Framebuffer(cv_dib.ventana_tam_x, cv_dib.ventana_tam_y);
   //fbo->activar(cv_dib.ventana_tam_x,cv_dib.ventana_tam_y);


   // 2. crear un 'ContextoVis' apropiado, en ese objeto:
   //    * activar modo selecion, desactivar iluminación, poner modo relleno
   //    * usar el mismo cauce que en 'cv_dib'
   //    * fijar el tamaño de la ventana igual que en 'cv_dib'
   //
   // ..........
   //mio:
   /*ContextoVis cv(cv_dib);
   cv.modo_seleccion = true;
   cv.iluminacion = false;
   cv.modo_visu = ModosVisu::relleno;
   FijarColVertsIdent(*cv.cauce, 0);*/

   ContextoVis cv;
   cv.modo_seleccion = true;
   cv.iluminacion = false;
   cv.modo_visu = ModosVisu::relleno;
   cv.ventana_tam_x = cv_dib.ventana_tam_x;
   cv.ventana_tam_y = cv_dib.ventana_tam_y;
   cv.cauce = cv_dib.cauce;
   //cv.cauce->fijarColor(0,0,0);
   FijarColVertsIdent(*cv.cauce, 0);

   // 3. Activar fbo, cauce y viewport. Configurar cauce (modo solido relleno, sin ilum.
   //    ni texturas). Limpiar el FBO (color de fondo: 0)
   // .......
   //mio:
   fbo->activar(cv_dib.ventana_tam_x, cv_dib.ventana_tam_y);
   cv.cauce->activar();
   cv.cauce->fijarEvalMIL(false);//quita la iluminacion
   glViewport(0, 0, cv.ventana_tam_x, cv.ventana_tam_y);
   cv.modo_visu = ModosVisu::relleno;
   glClearColor(0.0, 0.0, 0.0, 1.0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   /*fbo->activar(fbo->leerAncho(), fbo->leerAlto());
   cv_sel.cauce->activar();
   glViewport(0, 0, fbo->leerAncho(), fbo->leerAlto());
   cv_sel.modo_visu = ModosVisu::relleno;
   cv_sel.iluminacion = false;
   cv_sel.cauce->fijarColor(0,0,0); // ??*/

   // 4. Activar la cámara (se debe leer de la escena con 'camaraActual')
   // ....
   //mio:
   escena->camaraActual()->activar(*cv.cauce);


   // 5. Visualizar el objeto raiz actual (se debe leer de la escena con 'objetoActual()')
   //    la visualización se hace en modo selección.
   // ........
   //mio:
   Objeto3D * objeto_raiz_actual = escena->objetoActual();
   objeto_raiz_actual->visualizarGL(cv);

   // 6. Leer el color del pixel (usar 'LeerIdentEnPixel')
   // (hay que hacerlo mientras está activado el framebuffer de selección)
   // .....
   //mio:
   int ident;
   //cout << "\n IDENT : " << ident;
   ident = LeerIdentEnPixel(x, y);
   //cout << "\n IDENT: " << ident;
   //ident = 1;
   //cout << "\n IDENT: " << ident;
   cout << "\nx: " << x << "      y: " << y << flush;


   // 7. Desactivar el framebuffer de selección
   // .....
   //mio:
   fbo->desactivar();

   // 8. Si el identificador del pixel es 0, imprimir mensaje y terminar (devolver 'false')
   // ....
   //mio:
   if (ident == 0){
      cout << "\nEl identificador resultante es 0. No hay ningun objeto seleccionable\n";
      return false;
   }


   // 9. Buscar el objeto en el objeto_raiz (puede ser un grafo de escena)
   //    e informar del nombre del mismo (si no se encuentra, indicarlo)
   //   (usar 'buscarObjeto')
   // .....
   //mio:
   Tupla3f puntocentro;
   Objeto3D * objetoencontrado;
   
   if (objeto_raiz_actual->buscarObjeto(ident, MAT_Ident(), &objetoencontrado, puntocentro)){

      //cambios del examen:
      EsferaEXP5 * pesf = dynamic_cast<EsferaEXP5 *> (objetoencontrado);
      if(pesf == nullptr){
         escena->camaraActual()->mirarHacia(puntocentro);
         cout << "\nSe ha encontrado un objeto. Identificador: " << ident << ". Nombre: " << objetoencontrado->leerNombre() << "\n";
      }else{
         cout << "\nNo se apunta al objeto porque es una esfera del examen de la p5 ";
         objetoencontrado->ponerColor({1, 0.5, 0.5});
      } 
      //escena->camaraActual()->mirarHacia(puntocentro);
      //cout << "\nSe ha encontrado un objeto. Identificador: " << ident << ". Nombre: " << objetoencontrado->leerNombre() << "\n";
   } 
   else{
      cout << "\nNo se ha encontrado un objeto con identificador " << ident << "\n";

      return false;
   }

   // al final devolvemos 'true', ya que hemos encontrado un objeto
   return true ;

}
