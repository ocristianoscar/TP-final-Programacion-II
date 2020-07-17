#include "TDA.Playlist.h"

int contarArchivoPlaylist(){
    int cant=0;
    FILE *ArchivoPlay = fopen(ALIST, "rb");
    fseek(ArchivoPlay, 0, SEEK_END);
    cant = ftell(ArchivoPlay) / sizeof(stPlaylist);
    fclose(ArchivoPlay);
    return cant;
}

/**stPlaylist *archivoToArregloP(int validos){    ///Validos es contarArchivoPlaylist
    stPlaylist *arreglo = malloc(sizeof(stPlaylist)*validos);
    FILE *ArchivoPlay = fopen(ALIST, "rb");
    int i=0;
    while(fread(&arreglo[i], sizeof(stPlaylist), 1, ArchivoPlay)>0){
        i++;
    }
    fclose(ArchivoPlay);
    return arreglo;
}*/



stCelda *pasarCancionesToADL(stCelda *celdas, nodoArbolCancion *canciones){
    int validos = cantUsuarios();
    celdas = pasarUserToADL(validos);
    FILE *ArchivoPlay = fopen(ALIST, "rb");
    stPlaylist playlist;
    ///playlist = archivoToArregloP(validos);///Puede poner esto afuera de la funcion y recibirlo
    int flag=0, j=0;
    nodoArbolCancion *aux;
    while(fread(&playlist, sizeof(stPlaylist), 1, ArchivoPlay)>0){
        while(flag !=1){
            if(playlist.idUsuario == celdas[j].usr.idUsuario){
                aux = buscarNodoId(canciones, playlist.idCancion);
                celdas[j].listaCanciones = agregarFinal(celdas[j].listaCanciones, crearNodoLC(aux->c));
                flag = 1;
                j=0;
            }else{
                j++;
            }
        }
        flag = 0;
    }
    fclose(ArchivoPlay);
    return celdas;
}

void actualizarCancionesEscuchadas(stUsuario user, stSong cancion){
    stPlaylist aux;
    aux.idCancion = cancion.idCancion;
    aux.idUsuario = user.idUsuario;
    aux.idPlaylist = contarArchivoPlaylist();
    FILE *ArchivoPlay = fopen(ALIST, "ab");
    fwrite(&aux, sizeof(stPlaylist), 1, ArchivoPlay);
    fclose(ArchivoPlay);
}

void agregarCancionToUsuario(int idUser, stSong cancion, stCelda a[])
{
    a[idUser + 1].listaCanciones = agregarFinal(a[idUser + 1].listaCanciones , crearNodoLC(cancion));
    actualizarCancionesEscuchadas(a[idUser + 1].usr, cancion);
}

nodoArbolCancion *algoritmoRecomendacion(nodoArbolCancion *tree, stCelda user, nodoArbolCancion *aux){
    if(tree!=NULL){
        if(tree->c.recomendacion > aux->c.recomendacion){
            if(buscarEnLista(user.listaCanciones, tree->c)!=1){
                aux = tree;
            }
        }
        aux = algoritmoRecomendacion(tree->derecha, user, aux);
        aux = algoritmoRecomendacion(tree->izquierda, user, aux);
    }
    return aux;
}
