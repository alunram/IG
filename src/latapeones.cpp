//Nombre: Alvaro, Apellidos: Luna Ramirez, Titulacion: GIM, correo: alvaroluna@correo.ugr.es, DNI: 
// *********************************************************************
#include "latapeones.h"
#include "grafo-escena.h"
#include "malla-ind.h"

LataPeones::LataPeones()
{
    unsigned int  int_lata = 1;
    unsigned int  int_peonmadera = 2;
    unsigned int  int_peonblanco = 3;
    unsigned int  int_peonnegro = 4;

    Lata *lata = new Lata("lata-coke.jpg");
    lata->ponerIdentificador(int_lata);
    lata->ponerNombre("Lata");

    TexturaXY *tex = new TexturaXY("text-madera.jpg");
    Material *material_madera = new Material(tex, 0.2, 1, 1.3, 50);
    Peon *peon_madera = new Peon();
    peon_madera->ponerNombre("Peón de madera");
    peon_madera->ponerIdentificador(int_peonmadera);  

    Material *material_blanco = new Material(0.2, 0.5, 0.0, 5.0);
    Peon *peon_blanco = new Peon();
    peon_blanco->ponerNombre("Peón blancas");
    peon_blanco->ponerIdentificador(int_peonblanco);
    peon_blanco->ponerColor({1.0, 1.0, 1.0});

    //Material *material_negro = new Material(0.01, 0.25, 0.25, 50.0);
    Material *material_negro = new Material(0.4, 0.1, 0.5, 10);
    Peon *peon_negro = new Peon();
    peon_negro->ponerNombre("Peón negras");
    peon_negro->ponerIdentificador(int_peonnegro);
    peon_negro->ponerColor({0.0, 0.0, 0.0});
    
    agregar(lata);
    agregar(MAT_Traslacion({0.5, 0.0, 0.0}));
    agregar(material_madera);
    agregar(peon_madera);
    agregar(MAT_Traslacion({0.5, 0.0, 0.0}));
    agregar(material_blanco);
    agregar(peon_blanco);
    agregar(MAT_Traslacion({0.5, 0.0, 0.0}));
    agregar(material_negro);
    agregar(peon_negro);

}

Peon::Peon()
{
   agregar(MAT_Traslacion({0, 0.25, 1.0}));
   agregar(MAT_Escalado(0.2, 0.2, 0.2));

   agregar(new MallaRevolPLY("peon.ply", 100));
}

Lata::Lata(std::string nombre_archivo)
{
   Textura *text = new Textura(nombre_archivo);

   Material *material_arribayabajo = new Material(0.5, 0.75, 1, 50.0);

   agregar(material_arribayabajo);

   agregar(new MallaRevolPLY("lata-psup.ply", 100));
   agregar(new MallaRevolPLY("lata-pinf.ply", 100));

   Material *material_partecentral = new Material(text, 1, 1, 1, 20.0);

   agregar(material_partecentral);

   agregar(new MallaRevolPLY("lata-pcue.ply", 100));

}

VariasLatasPeones::VariasLatasPeones()
{
   unsigned int  int_lata2 = 5;
   Lata *lata2 = new Lata("lata-pepsi.jpg");
   lata2->ponerNombre("Lata de Pepsi");
   lata2->ponerIdentificador(int_lata2);


   unsigned int  int_lata3 = 6;   
   Lata *lata3 = new Lata("window-icon.jpg");
   lata3->ponerNombre("Lata de la UGR");
   lata3->ponerIdentificador(int_lata3);

   agregar(new LataPeones());
   agregar(MAT_Traslacion({0.75, 0.0, 0.0}));
   agregar(lata2); 
   agregar(MAT_Traslacion({0.75, 0.0, 0.0}));
   agregar(lata3);

}









