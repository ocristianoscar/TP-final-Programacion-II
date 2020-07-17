#ifndef TDA_PLAYLIST_H_INCLUDED
#define TDA_PLAYLIST_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TDA.Cancion.h"
#include "usuarios.h"
#define ARCHIVO_USUARIOS "usuarios.dat"
#define ALIST "playlist.dat"

typedef struct
{
    int idPlaylist;
    int idUsuario;
    int idCancion;
} stPlaylist;

///TEMPORAL PARA TESTEO
//No hay mas! WOooooOOOooOOooW

int contarArchivoPlaylist();
///stPlaylist *archivoToArregloP(int);
stCelda *pasarCancionesToADL(stCelda*, nodoArbolCancion*);
void actualizarCancionesEscuchadas(stUsuario, stSong);
void agregarCancionToUsuario(int, stSong, stCelda[]);
nodoArbolCancion *algoritmoRecomendacion(nodoArbolCancion*, stCelda, nodoArbolCancion*);


#endif // TDA_PLAYLIST_H_INCLUDED
