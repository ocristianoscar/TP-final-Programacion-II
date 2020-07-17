#include "TDA.Cancion.h"

///----------------------------------------------- ARBOLES CANCIONES -------------------------------------------------------------

///---Inicializa el arbol en NULL.---
nodoArbolCancion *inicArbol(){
    return NULL;
}

///---Crea un Nodo del arbol de canciones.---
nodoArbolCancion *crearArbol(stSong dato){
    nodoArbolCancion *aux = (nodoArbolCancion*)malloc(sizeof(nodoArbolCancion));
    aux->c = dato;
    aux->derecha = NULL;
    aux->izquierda = NULL;
    return aux;
}

///---Agrega en el arbol un nodo por ID manteniendo el orden.---
nodoArbolCancion *insertarArbol(nodoArbolCancion *tree, nodoArbolCancion *leaf){
    if(tree==NULL){
        tree = leaf;
    }else{
        if(tree->c.idCancion > leaf->c.idCancion){
            tree->izquierda = insertarArbol(tree->izquierda, leaf);
        }else{
            tree->derecha = insertarArbol(tree->derecha, leaf);
        }
    }
    return tree;
}

///---Agrega multiples nodos a un arbol revisando si ya existian.---
nodoArbolCancion *cargarArbol(nodoArbolCancion *tree){
    char control='s';
    nodoArbolCancion *leaf;
    while(control=='s'){

        nodoArbolCancion *aux = masGrande(tree);

        if(aux!=NULL){
            leaf = crearArbol(cargarCancion(aux->c.idCancion));
        }else{
            leaf = crearArbol(cargarCancion(0));
        }
        nodoArbolCancion *auxC;
        auxC = compararCancion(tree, leaf->c);

        if(auxC==NULL){
            tree = insertarArbol(tree, leaf);
        }else{
            auxC->c.eliminado = 0;
        }

        printf("Desea ingresar otro dato? s/n \n");
        fflush(stdin);
        scanf("%c", &control);
    }
    return tree;
}

///---Revisa si existe una cancion con el mismo titulo, artista y album, y si existe lo retorna.---
nodoArbolCancion *compararCancion(nodoArbolCancion *tree, stSong cancion){
    nodoArbolCancion *aux = inicArbol();
    if(tree!=NULL){
        if(strcmp(tree->c.titulo,cancion.titulo)==0 && strcmp(tree->c.artista,cancion.artista)==0 && strcmp(tree->c.album,cancion.album)==0){
            aux = tree;
        }else{
            aux = compararCancion(tree->izquierda, cancion);
            if(aux!=NULL){
                aux = compararCancion(tree->derecha, cancion);
            }
        }
    }
    return aux;
}

///---Retorna el elemento que se ubique mas a la derecha de un arbol.---
nodoArbolCancion *masGrande(nodoArbolCancion *tree){
    nodoArbolCancion *aux = tree;
    if(aux!=NULL){
        if(aux->derecha!=NULL){
            aux = masGrande(aux->derecha);
        }
    }
    return aux;
}

///---Permite ingresarle datos a una cancion y retornarla.---
stSong cargarCancion(int id){
    stSong song;
    song.idCancion = id+1;
    printf("Titulo: ");
    fflush(stdin);
    gets(song.titulo);
    printf("\nArtista: ");
    fflush(stdin);
    gets(song.artista);
    int dur = song.duracion;
    do{
        if(dur-song.duracion>=0.61){
            printf("A%co no valido, intente denuevo\n", ENIEMINUSCULA);
        }
        printf("\nDuracion: ");
        fflush(stdin);
        scanf("%f", &song.duracion);
        dur = (int)song.duracion;
    }while(dur-song.duracion>=0.61);


    printf("\nAlbum: ");
    fflush(stdin);
    gets(song.album);


    do{
        if(song.anio<1000 || song.anio > 2020){
            printf("A%co no valido, intente denuevo\n", ENIEMINUSCULA);
        }
        printf("\nA%co: ", ENIEMINUSCULA);
        fflush(stdin);
        scanf("%d", &song.anio);
    }while(song.anio<1000 || song.anio > 2020);

    printf("\nGenero: ");
    fflush(stdin);
    gets(song.genero);
    printf("\nComentario: ");
    fflush(stdin);
    gets(song.comentario);
    song.eliminado=0;
    song.recomendacion=0;
    printf("\n");
    return song;
}

///---Pasa los datos del arbol al archivo de manera ordenada.---
void arbolToArchivo(nodoArbolCancion *tree, FILE *ArchivoSong){
    stSong cancion;
    if(tree!=NULL){
        arbolToArchivo(tree->izquierda, ArchivoSong);
        cancion = tree->c;
        fwrite(&cancion, sizeof(stSong), 1, ArchivoSong);
        arbolToArchivo(tree->derecha, ArchivoSong);
    }
}

///---Pasa los datos del archivo al arbol de manera que quede balanceado.---
void archivoToArbol(FILE *ArchivoSong, nodoArbolCancion **tree, int start, int endN){
    int aux = endN - start;
    stSong cancion;
    aux = DivRedondeoUp(aux);
    fseek(ArchivoSong, sizeof(stSong)*(start), SEEK_SET);
    fseek(ArchivoSong, sizeof(stSong)*(aux-1), SEEK_CUR);
    fread(&cancion, sizeof(stSong), 1, ArchivoSong);
    if(buscarNodoId(*tree, cancion.idCancion)==NULL){
        *tree = insertarArbol(*tree, crearArbol(cancion));
    }
    if((aux-1)!=0){
        archivoToArbol(ArchivoSong, tree, start, cancion.idCancion);
        archivoToArbol(ArchivoSong, tree, cancion.idCancion, endN);
    }
}

///---Funcion para iniciar el arbol al principio del programa.---
nodoArbolCancion *iniciarArbol(){
    nodoArbolCancion *tree = inicArbol();
    stSong cancion;
    int inicio = 0, fin = contarCanciones();
    FILE *ArchivoSong = fopen(ASONG, "rb");
    archivoToArbol(ArchivoSong, &tree, inicio, fin);
    //if(fin % 2 != 0){
        fseek(ArchivoSong, sizeof(stSong)*(fin-1), SEEK_SET);
        fread(&cancion, sizeof(stSong), 1, ArchivoSong);
        tree = insertarArbol(tree, crearArbol(cancion));
    //}
    fclose(ArchivoSong);
    return tree;
}

///---Funcion auxiliar que redondea los numeros hace arriba.---
int DivRedondeoUp(int dato){
    int aux2;
    float aux = (float)dato/2;
    aux2 = dato/2;
    if((aux - aux2) > 0){
        aux2++;
    }
    return aux2;
}

///---Muestra el arbol de manera posOrder.---
void mostrarArbolpostOrder(nodoArbolCancion *tree){
    if(tree!=NULL){
        mostrarArbolpostOrder(tree->izquierda);
        mostrarArbolpostOrder(tree->derecha);
        if(tree->c.eliminado!=1)
            mostrarCancion(tree->c);
    }
}

///---Muestra el arbol de manera preOrder.---
void mostrarArbolPreOrder(nodoArbolCancion *tree){
    if(tree!=NULL){
        if(tree->c.eliminado!=1)
            mostrarCancion(tree->c);
        mostrarArbolPreOrder(tree->izquierda);
        mostrarArbolPreOrder(tree->derecha);
    }
}

///---Muestra el arbol de manera inOrder.---
void mostrarArbolInorder(nodoArbolCancion *tree){
    if(tree!=NULL){
        mostrarArbolInorder(tree->izquierda);
        if(tree->c.eliminado!=1){
            printf("//----------------------------------------------------//\n");
            mostrarCancion(tree->c);
        }
        mostrarArbolInorder(tree->derecha);
    }
}

///---Muestra por pantalla una unica cancion.---
void mostrarCancion(stSong cancion){
    printf("ID: %d\n", cancion.idCancion);
    printf("Titulo: %s\n", cancion.titulo);
    printf("Artista : %s\n", cancion.artista);
    printf("Album : %s\n", cancion.album);
    printf("A%co: %d\n", ENIEMINUSCULA, cancion.anio);
    printf("Genero: %s\n", cancion.genero);
    printf("Duracion: %f\n", cancion.duracion);
    printf("Recomendacion: %d\n", cancion.recomendacion);
    printf("Comentario: %s\n", cancion.comentario);
}

///---Busca un nodo en un arbol a travez de la ID y lo retorna si lo encuentra.---
nodoArbolCancion *buscarNodoId(nodoArbolCancion *tree, int id){
    nodoArbolCancion *aux = inicArbol();
    if(tree!=NULL){
        if(tree->c.idCancion==id){
            aux = tree;
        }else{
            if(tree->c.idCancion>id)
                aux = buscarNodoId(tree->izquierda,id);
            else
                aux = buscarNodoId(tree->derecha,id);
        }
    }
    return aux;
}

///---Busca un nodo en un arbol a travez del nombre y lo retorna si lo encuentra.---
nodoArbolCancion *buscarNodoNombre(nodoArbolCancion *tree, char name[]){
    nodoArbolCancion *aux = inicArbol();
    if(tree!=NULL){
        if(strcmp(tree->c.titulo,name)==0){
            aux = tree;
        }else{
            aux = buscarNodoNombre(tree->izquierda,name);
            if(aux!=NULL)
                aux = buscarNodoNombre(tree->derecha,name);
        }
    }
    return aux;
}

///---Realiza una baja logica en el arbol.---
void borrarNodo(nodoArbolCancion **tree){
    nodoArbolCancion *aux=inicArbol();
    aux = buscador(*tree);
    if(aux!=NULL)
        aux->c.eliminado = 1;
}

///---Muestra por pantalla una cancion del arbol.---
void consulta(nodoArbolCancion *tree){
    nodoArbolCancion *aux=inicArbol();
    aux = buscador(tree);
    if(aux!=NULL){
        mostrarCancion(aux->c);
    }
}

///---Actualmente busca por ID una cancion y si la encuentra retorna el nodo donde se ubica.---
nodoArbolCancion *buscador(nodoArbolCancion *tree){
    nodoArbolCancion *aux=inicArbol();
    int id, modo;
    char name[30];
    /**printf("Con 1 busca por id\n");
    printf("Con 2 busca por titulo\n");
    fflush(stdin);
    scanf("%d", &modo);*/
    modo = 1;
    switch(modo){
        case 1:
            printf("Id de la cancion: \n");
            fflush(stdin);
            scanf("%d", &id);
            aux = buscarNodoId(tree,id);
            break;
        case 2:
            printf("Titulo de la cancion: \n");
            fflush(stdin);
            gets(name);
            aux = buscarNodoNombre(tree, name);
            break;
        default:
            printf("Caso incorrecto\nIntente otra vez\n");
            aux = buscador(tree);
            break;
    }
    return aux;
}

///---Permite modificar Titulo, Artista, Album, A�o, Genero y Duracion de un tema.---
void modificarCancion(nodoArbolCancion **tree){
    nodoArbolCancion *aux=inicArbol();
    int modo;
    aux = buscador(*tree);
    if(aux!=NULL){
        char control='s';
        while(control=='s'){
            printf("Modificar: \n1: Titulo\n2: Artista\n3: Album\n4: A%co\n5: Genero\n6: Duracion\n", ENIEMINUSCULA);
            fflush(stdin);
            scanf("%d", &modo);
            int anio;
            float dur;
            char *arreglo;
            switch(modo){
                case 1:
                    printf("Titulo de la cancion: \n");
                    fflush(stdin);
                    arreglo = malloc(sizeof(char)*30);
                    gets(arreglo);
                    strcpy(aux->c.titulo,arreglo);
                    break;
                case 2:
                    printf("Artista de la cancion: \n");
                    fflush(stdin);
                    arreglo = malloc(sizeof(char)*40);
                    gets(arreglo);
                    strcpy(aux->c.artista,arreglo);
                    break;
                case 3:
                    printf("Album de la cancion: \n");
                    fflush(stdin);
                    arreglo = malloc(sizeof(char)*20);
                    gets(arreglo);
                    strcpy(aux->c.album,arreglo);
                    break;
                case 4:
                    printf("A%co de la cancion: \n", ENIEMINUSCULA);
                    fflush(stdin);
                    scanf("%d", &anio);
                    aux->c.anio = anio;
                    break;
                case 5:
                    printf("Genero de la cancion: \n");
                    fflush(stdin);
                    arreglo = malloc(sizeof(char)*20);
                    gets(arreglo);
                    strcpy(aux->c.genero,arreglo);
                    break;
                case 6:
                    printf("Duracion de la cancion: \n");
                    fflush(stdin);
                    scanf("%f", &dur);
                    aux->c.duracion = dur;
                    break;
               /* case 7:
                    printf("Recomendacion de la cancion: \n");
                    fflush(stdin);
                    scanf("%d", &anio);
                    aux->c.recomendacion = anio;
                    break;*/
                default:
                    printf("Caso incorrecto\nIntente otra vez\n");
                    aux = buscador(*tree);
                    break;
            }
            printf("Desea ingresar otro dato? s/n \n");
            fflush(stdin);
            scanf("%c", &control);
        }
    }
}

///----------------------------------------------- ARREGLO CANCIONES -------------------------------------------------------------

///---Cuenta cuantas canciones hay en el archivo de canciones y retorna la cantidad.---
int contarCanciones(){
    int cant=0;
    FILE *ArchivoSong = fopen(ASONG, "rb");
    fseek(ArchivoSong, 0, SEEK_END);
    cant = ftell(ArchivoSong) / sizeof(stSong);
    fclose(ArchivoSong);
    return cant;
}

///---Pasa los datos del archivo de canciones a un arreglo.---
int archivoToArreglo(stSong **arreglo){
    int validos = contarCanciones();
    int i=0;
    stSong aux;
    *arreglo = malloc(sizeof(stSong)*validos);
    FILE *ArchivoSong = fopen(ASONG, "rb");
    while(fread(&aux, sizeof(stSong), 1, ArchivoSong)>0){
        *arreglo[i] = aux;
        i++;
    }
    return i;
}

///---Metodo de ordenacion por seleccion en arreglos tomando el titulo como dato principal.---
int postMenor(stSong arr[], int validos, int pos){
    char menor[30];
    strcpy(menor,arr[pos].titulo);
    int posmenor = pos;
    int i = pos + 1;
    while(i<validos){
        if(strcmp(menor, arr[i].titulo)>0){
            strcpy(menor,arr[i].titulo);
            posmenor = i;
        }
        i++;
    }
    return posmenor;
}

void ordenacionS(stSong arr[], int validos){
    int posmenor;
    int i = 0;
    stSong aux;
    while(i<validos-1){
        posmenor = postMenor(arr,validos,i);
        aux = arr[posmenor];
        arr[posmenor] = arr[i];
        arr[i] = aux;
        i++;
    }
}

///---Metodo de ordenacion por insercion en arreglos tomando el genero como dato principal.---
void insertar(stSong arr[], int validos, int last, stSong newt){
    int i = last;
    while(i>=0 && strcmp(newt.genero,arr[i].genero)>0){
        arr[i+1] = arr[i];
        i--;
    }
    arr[i+1] = newt;
}

void ordenacionI(stSong arr[], int validos){
    int last = 0;
    while(last < validos-1){
        insertar(arr,validos,last,arr[last+1]);
        last++;
    }
}

///---Muestra por pantalla un arreglo con todas las canciones del archivo por titulo o genero.---
void listado(){
    int modo, val, i;
    stSong *vector;
    val = archivoToArreglo(&vector);
    printf("Con 1 muestra por titulo\n");
    printf("Con 2 muestra por genero\n");
    fflush(stdin);
    scanf("%d", &modo);
    switch(modo){
        case 1:
            ordenacionS(vector,val);
            for(i=0;i<val;i++){
                if(vector[i].eliminado!=1){
                    mostrarCancion(vector[i]);
                }
            }
            break;
        case 2:
            ordenacionI(vector,val);
            for(i=0;i<val;i++){
                if(vector[i].eliminado!=1){
                    mostrarCancion(vector[i]);
                }
            }
            break;
        default:
            printf("Caso incorrecto\nIntente otra vez\n");
            listado();
            break;
    }
}

///----------------------------------------------- LISTAS CANCIONES -------------------------------------------------------------


///---Inicializa la lista en NULL.---
nodoLC *inicLista(){
    return NULL;
}

///---Crea un Nodo de lista de canciones.---
nodoLC *crearNodoLC(stSong cancion){
    nodoLC *aux = (nodoLC*)malloc(sizeof(nodoLC));
    aux->c = cancion;
    aux->sig = NULL;
    return aux;
}

///---Agrega un nuevo nodo a la lista ubicandolo al inicio.---
nodoLC *agregarPpio(nodoLC *lista, nodoLC *newt){
    newt->sig = lista;
    return newt;
}

///---Agrega un nuevo nodo a la lista ubicandolo al final.---
nodoLC *agregarFinal(nodoLC *lista, nodoLC *newt){
    if(lista==NULL){
        lista = newt;
    }else{
        nodoLC *aux = lista;
        while(aux->sig!=NULL){
            aux = aux->sig;
        }
        aux->sig = newt;
    }
    return lista;
}

///---Agrega un nuevo nodo a la lista ubicandolo en orden por titulo.---
nodoLC *agregarOrden(nodoLC *lista, nodoLC *newt){
    if(lista==NULL){
        lista = newt;
    }else{
        if(strcmp(lista->c.titulo, newt->c.titulo)>0){
            lista = agregarPpio(lista, newt);
        }else{
            nodoLC *aux = lista;
            nodoLC *ante = aux;
            while(strcmp(aux->c.titulo, newt->c.titulo)<0){
                ante = aux;
                aux = aux->sig;
            }
            newt->sig = aux;
            ante->sig = newt;
        }
    }
    return lista;
}

///---Muestra toda la lista de canciones.---
void mostrarLC(nodoLC *lista){
    while(lista!=NULL){
        printf("//----------------------------------------------------//\n");
        mostrarCancion(lista->c);
        lista = lista->sig;
    }
}

///---Realiza una baja logica de un nodo buscandolo por ID.---
nodoLC *borrarNodoLC(nodoLC *lista, int id){
    nodoLC *aux;
    if(lista->c.idCancion==id){
        aux=lista;
        lista = lista->sig;
        aux->sig = NULL;
        free(aux);
    }else{
        aux = lista;
        nodoLC *ante = aux;
        while(aux->c.idCancion != id){
            ante = aux;
            aux = aux->sig;
        }
        if(aux!=NULL){
            ante->sig = aux->sig;
            aux->sig = NULL;
            free(aux);
        }
    }
    return lista;
}

///---Busca una cancion en la lista y devuelve 1 si la encuentra, 0 si no la encuentra
int buscarEnLista(nodoLC *lista, stSong cancion){
    int flag=0;
    while(lista!=NULL && flag!=1){
        if(strcmp(lista->c.titulo,cancion.titulo)==0 && strcmp(lista->c.artista,cancion.artista)==0 && strcmp(lista->c.album,cancion.album)==0){
            flag=1;
        }
        lista = lista->sig;
    }
    return flag;
}

///---------------------------------------------- FUNCIONES SIN UTILIZAR --------------------------------------------------------


/**int cargarVariasCanciones(stSong variasC[], int dim){
    char control = 's';
    int i=0;
    while(i<dim && control == 's'){
        variasC[i] = cargarCancion();
        printf("Desea agregar otra cancion? s/n\n");
        fflush(stdin);
        scanf("%c", &control);
        i++;
    }
    if(control=='s'){
        cargarCancionsArchivos(variasC,dim-1);
        cargarVariasCanciones(variasC,dim);
    }
    return i;
}

void cargarCancionsArchivos(stSong variasC[], int val){
    FILE *ArchivoSong=fopen(ASONG,"ab");
    for(int i=0;i<val;i++){
        fwrite(&variasC[i],sizeof(stSong),1,ArchivoSong);
    }
    fclose(ArchivoSong);
}

int leerCancionesArchivos(stSong variasC[], int dim){
    FILE *ArchivoSong=fopen(ASONG,"rb");
    int i=0;
    while(i<dim && fread(&variasC[i],sizeof(stSong),1,ArchivoSong)){
        i++;
    }
    fclose(ArchivoSong);
    return i;
}*/
