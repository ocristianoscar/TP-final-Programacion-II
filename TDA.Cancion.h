#ifndef TDA_CANCION_H_INCLUDED
#define TDA_CANCION_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ENIEMINUSCULA 164
#define ASONG "canciones.dat"

typedef struct {
   int idCancion;
   char titulo[30];
   char artista[40];
   float duracion;
   char album[20];
   int anio;
   char genero[20];
   char comentario[150];
   int recomendacion;
   int eliminado;  // indica 1 o 0 si la canción fue eliminada
} stSong;

typedef struct nodoArbolCancion{
    stSong c;
    struct nodoArbolCancion * izquierda;
    struct nodoArbolCancion * derecha;
} nodoArbolCancion;


typedef struct nodoLC{
    stSong c;
    struct nodoLC *sig;
}nodoLC;

stSong cargarCancion(int);                                          //28 funciones, congrats - gnosinporta
nodoArbolCancion *inicArbol();
nodoArbolCancion *iniciarArbol();                                   // 30 funciones ahora kill me - el pobre milano
nodoArbolCancion *crearArbol(stSong);
nodoArbolCancion *insertarArbol(nodoArbolCancion*, nodoArbolCancion*);
nodoArbolCancion *cargarArbol(nodoArbolCancion*);
nodoArbolCancion *masGrande(nodoArbolCancion *);
nodoArbolCancion *compararCancion(nodoArbolCancion*, stSong);
int buscarEnLista(nodoLC*, stSong);
int DivRedondeoUp(int);
void arbolToArchivo(nodoArbolCancion*, FILE*);
void archivoToArbol(FILE*, nodoArbolCancion**, int, int);
void mostrarArbolInorder(nodoArbolCancion*);
void mostrarArbolpostOrder(nodoArbolCancion*);
void mostrarArbolPreOrder(nodoArbolCancion*);
void mostrarCancion(stSong);
nodoArbolCancion *buscarNodoId(nodoArbolCancion*, int);
nodoArbolCancion *buscarNodoNombre(nodoArbolCancion *, char[]);
void borrarNodo(nodoArbolCancion**);
nodoArbolCancion *buscador(nodoArbolCancion*);
void modificarCancion(nodoArbolCancion **);
void consulta(nodoArbolCancion*);
int contarCanciones();
int archivoToArreglo(stSong**);
int postMenor(stSong[], int, int);
void ordenacionS(stSong[], int);
void insertar(stSong[], int, int, stSong);
void ordenacionI(stSong[], int);
void listado();
nodoLC *inicLista();
nodoLC *crearNodoLC(stSong);
nodoLC *agregarPpio(nodoLC*, nodoLC*);
nodoLC *agregarFinal(nodoLC*, nodoLC*);
nodoLC *agregarOrden(nodoLC*, nodoLC*);
void mostrarLC(nodoLC*);
nodoLC *borrarNodoLC(nodoLC*, int);
///int cargarVariasCanciones(stSong[], int);
///void cargarCancionsArchivos(stSong[], int);

#endif // TDA_CANCION_H_INCLUDED
