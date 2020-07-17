#include <stdio.h>
#include <stdlib.h>

#include "menu.h"
#include "usuarios.h"
#include "TDA.Cancion.h"
#include "TDA.Playlist.h"



void inicio(nodoArbolCancion ** arbol_de_canciones, stCelda ** arreglo_de_usuarios, int * validos_ADU);



int main()
{
    nodoArbolCancion *arbol = inicArbol();
    stCelda *arreglo_de_usuarios;
    int validos_ADU;

    inicio(&arbol, &arreglo_de_usuarios, &validos_ADU);

    menuPrincipal(arbol, arreglo_de_usuarios, &validos_ADU);
    return 0;
}




void inicio(nodoArbolCancion ** arbol_de_canciones, stCelda ** arreglo_de_usuarios, int * validos_ADU)
{
    //inicializar el archivo de usuarios
    inicArchivoUsuarios();

    //crear el arbol de canciones
   // arbol_de_canciones = inicArbol();
    *arbol_de_canciones = iniciarArbol();

    //crear el arreglo de usuarios
    (*validos_ADU) = cantUsuarios();

    //arreglo_de_usuarios = pasarUserToADL(*validos_ADU);   //comentado porque la funcion de abajo ya hace esto
    *arreglo_de_usuarios = pasarCancionesToADL(*arreglo_de_usuarios, *arbol_de_canciones);
}
