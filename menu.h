#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "usuarios.h"
#include "TDA.Cancion.h"
#include "TDA.Playlist.h"



//prototipados de funciones de menu

void menuPrincipal(nodoArbolCancion * arbol_de_canciones, stCelda * arreglo_de_usuarios, int * validos_ADU);
void login(nodoArbolCancion * arbol_de_canciones, stCelda * arreglo_de_usuarios, int * validos_ADU);
void menuAdmin(nodoArbolCancion * arbol_de_canciones, stCelda * arreglo_de_usuarios, int * validos_ADU);
void adminUsers(nodoArbolCancion * arbol_de_canciones, stCelda * arreglo_de_usuarios, int * validos_ADU);
void altaUsers(stCelda ** arreglo_de_usuarios, int ** validos_ADU);
void altaAdmin(stCelda ** arreglo_de_usuarios, int * validos_ADU);
void bajaUsers(stCelda ** arreglo_de_usuarios, int * validos_ADU);
void modUsers(stCelda ** arreglo_de_usuarios, int * validos_ADU);
void consultaUsers(stCelda * arreglo_de_usuarios, int * validos_ADU);
void listadoUsers(stCelda * arreglo_de_usuarios, int * validos_ADU);
void menuUser(stCelda * arreglo_de_usuarios, int * validos_ADU, int pos_user, nodoArbolCancion * arbol_de_canciones);
void verPerfil(stCelda * arreglo_de_usuarios, int pos_user);
void mostrarPlaylistUser(stCelda * arreglo_de_usuarios, int pos_user);
void escucharCancion(stCelda ** arreglo_de_usuarios, int pos_user, nodoArbolCancion * arbol_de_canciones);
void cancionRecomendada(stCelda ** arreglo_de_usuarios, int pos_user, nodoArbolCancion * arbol_de_canciones);
stCelda *agregarToPlaylist(stCelda * arreglo_de_usuarios, int pos_user, nodoLC *lista, nodoArbolCancion **leaf);
void adminCanciones(nodoArbolCancion * arbol_de_canciones);
void altaSong(nodoArbolCancion ** arbol_de_canciones);
void bajaSong(nodoArbolCancion ** arbol_de_canciones);
void modSong(nodoArbolCancion ** arbol_de_canciones);
void consultaSong(nodoArbolCancion * arbol_de_canciones);
void listadoSong(nodoArbolCancion*);






#endif // MENU_H_INCLUDED
