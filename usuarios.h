#ifndef USUARIOS_H_INCLUDED
#define USUARIOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TDA.Cancion.h"


#define ARCHIVO_USUARIOS "usuarios.dat"


//estructura USUARIO

typedef struct{
    int idUsuario;
    char nombreUsuario[30];
    char pass[20];
    int anioNacimiento;
    char genero;
    char pais[20];
    int eliminado;  //indica 0 o 1 si el usuario fue eliminado
    int esAdmin;    //0 si es user, 1 si es admin
}stUsuario;


//estructura de arreglo de usuarios

typedef struct{
    stUsuario usr;
    nodoLC * listaCanciones;
}stCelda;



//prototipados de funciones


//-----------------FUNCIONES DE ARREGLO DE USUARIOS---------------

stCelda * pasarUserToADL(int validos);
stCelda * agregarUsuario(stUsuario user, stCelda * arr, int ** validos);
int buscarUsuarioPorId(int idUser, stCelda a[], int validos);
int buscarUsuarioPorNombre(char nombre[30], stCelda *a, int validos);
void mostrarUsuariosAndCanciones(stCelda a[], int validos);
void ADU_to_archivoUsers(stCelda * array_de_usuarios, int * validos);
//void limpiarArregloDeListas(stUsuario a[]);   emmanuel nos permitio no hacerla
//int persistirCancionesEscuchadas();   esta funcion se realiza con el TDA.Playlist.h, en la funcion actualizarCancionesEscuchadas



stCelda *pasarUserToADL(int);
//---------------FUNCIONES DE ESTRUCTURA DE USUARIOS------------

void inicArchivoUsuarios();
stUsuario crearUsuario();

//stUsuario buscarUsuario(char[]);
int guardarUsuarioArchivo(stUsuario);
int borrarUsuario(stUsuario);
stUsuario ultimoUserIngresado();
int cantUsuarios();
void mostrarUsuario(stUsuario);

//funciones por hacer
int guardarUserConId(stUsuario, int id);




#endif // USUARIOS_H_INCLUDED
