#include "menu.h"



//muestra el menu principal, pide opcion y redirecciona a las funciones respectivas
void menuPrincipal(nodoArbolCancion * arbol_de_canciones, stCelda * arreglo_de_usuarios, int * validos_ADU){
    int op;

    do{
        system("cls");
        printf("\nEL SPOTIFY - \"nunca nadie compraria este programa\"\n\n");
                //el ingreso puede cambiarse a dinamico (login - logout)
        printf("1 - login\n2 - registrarse\n0 - salir del programa\n\n> ");  //usar punteros para hacer menus dinamicos
        fflush(stdin);
        scanf("%i", &op);

        switch(op)
        {
            case 0: break;
            case 1: login(arbol_de_canciones, arreglo_de_usuarios, validos_ADU);
                    arreglo_de_usuarios = pasarCancionesToADL(arreglo_de_usuarios, arbol_de_canciones);
                    break;
            case 2: altaUsers(&arreglo_de_usuarios, &validos_ADU); break;
            default: printf("\n\nla opcion no es valida\n\n"); break;
        }

    }while(op != 0);
}




//menu principal de ingreso de administradores
//pide admin, verifica que exista, pide pass, si valida redirecciona al menu de administrador
void login(nodoArbolCancion * arbol_de_canciones, stCelda * arreglo_de_usuarios, int * validos_ADU){

    char usuario[30], pass[20];
    int encontrado = 0, validado = 0, cont = 0, rta;
    int pos_user = -1;

    system("cls");
    printf("MENU DE LOGIN\n\n");


    do
    {
        if(cont != 0)
            printf("no se encontro el usuario\n");  //se debe agregar la opcion si se quiere registrar el usuario
        printf("user: ");
        fflush(stdin);
        gets(usuario);

        pos_user = buscarUsuarioPorNombre(usuario, arreglo_de_usuarios, *validos_ADU);

        if(pos_user != -1)
            encontrado = 1;

        cont++;

    }while(encontrado == 0); //queda en un bucle infinito mientras no se encuentre un user

    stUsuario aux = arreglo_de_usuarios[pos_user].usr;
    if(aux.esAdmin == 1)
        printf("\nel usuario es administrador\n\n");

    cont = 0;

    do
    {
        if(cont != 0)
            printf("pass incorrecto\n");

        printf("pass: ");
        fflush(stdin);
        scanf("%s", pass);

        if( strcmp( pass , arreglo_de_usuarios[pos_user].usr.pass ) == 0 )
            validado = 1;

        cont++;

    }while(validado == 0); //queda en un bucle infinito mientras el pass no sea correcto

    printf("\nbienvenido, %s\n", arreglo_de_usuarios[pos_user].usr.nombreUsuario);


    if(arreglo_de_usuarios[pos_user].usr.esAdmin == 1)
    {
        printf("\ndesea usar el programa como administrador o como usuario?\n\n1 - admin\n2 - usuario\n\n> ");
        fflush(stdin);
        scanf("%i", &rta);


        switch(rta)
        {
            case 1: menuAdmin(arbol_de_canciones, arreglo_de_usuarios, validos_ADU);
                    arreglo_de_usuarios = pasarCancionesToADL(arreglo_de_usuarios, arbol_de_canciones);
                    break;
            case 2: menuUser(arreglo_de_usuarios, validos_ADU, pos_user, arbol_de_canciones);
                    arreglo_de_usuarios = pasarCancionesToADL(arreglo_de_usuarios, arbol_de_canciones);
                    break;
        }
    }
    else{
        menuUser(arreglo_de_usuarios, validos_ADU, pos_user, arbol_de_canciones);
        arreglo_de_usuarios = pasarCancionesToADL(arreglo_de_usuarios, arbol_de_canciones);
    }
}




//menu principal de administracion - redirige a administracion de canciones o de usuarios
void menuAdmin(nodoArbolCancion * arbol_de_canciones, stCelda * arreglo_de_usuarios, int * validos_ADU){

    int op;

    do{
        system("cls");
        printf("MENU DE ADMINISTRACION\n\n");
        printf("1 - administracion de usuarios\n2 - administracion de canciones\n0 - salir del menu de administracion\n\n> ");
        fflush(stdin);
        scanf("%i", &op);

        switch(op)
        {
            case 0: break;
            case 1: adminUsers(arbol_de_canciones, arreglo_de_usuarios, validos_ADU);
                    arreglo_de_usuarios = pasarCancionesToADL(arreglo_de_usuarios, arbol_de_canciones);
                    break;
            case 2: adminCanciones(arbol_de_canciones);

                    arbol_de_canciones = iniciarArbol();


                    break;
            default: printf("\n\nla opcion no es valida\n\n"); break;
        }

    }while(op != 0);

}




//administracion de usuarios - redirige a las funciones de ABMCL de usuarios
void adminUsers(nodoArbolCancion * arbol_de_canciones, stCelda * arreglo_de_usuarios, int * validos_ADU){

    int op;

    do{
        system("cls");
        printf("ADMINISTRACION DE USUARIOS O ADMINS\n\n");



        printf("1 - alta \n2 - baja\n3 - modificacion\n4 - consulta\n5 - listados\n0 - salir del menu\n\n> ");
        fflush(stdin);
        scanf("%i", &op);



        switch(op)
        {
            case 0: break;
            case 1: altaUsers(&arreglo_de_usuarios, &validos_ADU);
                    altaAdmin(&arreglo_de_usuarios, validos_ADU);
                    break;
            case 2: bajaUsers(&arreglo_de_usuarios, validos_ADU); break;
            case 3: modUsers(&arreglo_de_usuarios, validos_ADU); break;
            case 4: consultaUsers(arreglo_de_usuarios, validos_ADU); break;
            case 5: listadoUsers(arreglo_de_usuarios, validos_ADU); break;
            default: printf("\n\nla opcion no es valida\n\n"); break;
        }

    }while(op != 0);


}




//da de alta un nuevo usuario o admin
void altaUsers(stCelda ** arreglo_de_usuarios, int ** validos_ADU){

    system("cls");
    printf("ALTA DE NUEVO USUARIO\n\n");

    char nombre_usuario[30];
    //char pass_confirm[20], op;
    int cont = 0, encontrado = 1, pos_user = -1;
    //int passConfirmado = 0;
    stUsuario aux;

    do{
        if(cont != 0)
            printf("\n\nese nombre ya existe\n\n");

        printf("nombre del nuevo usuario: ");
        fflush(stdin);
        gets(nombre_usuario);


       pos_user = buscarUsuarioPorNombre(nombre_usuario, *arreglo_de_usuarios, **validos_ADU);

        if(pos_user == -1){
            encontrado = 0;
        }

        cont++;
    }while(encontrado == 1);

    aux.idUsuario = **validos_ADU;
    aux.eliminado = 0;
    aux.esAdmin = 0;
    strcpy( aux.nombreUsuario , nombre_usuario );

    printf("\nel nombre %s esta disponible\n\ningresar pass: ", aux.nombreUsuario);
    fflush(stdin);
    gets(aux.pass);

    //confirmar pass
    /*
    do
    {
        printf("\nconfirmar pass: ");
        fflush(stdin);
        gets(pass_confirm);
        if( strcmp( pass_confirm , aux.pass ) == 0 )
        {
            passConfirmado = 1;
        }
        else
        {
            printf("\nerror al confirmar password, vuelva a ingresarlo\n");  //queda en bucle infinito hasta que la confirmación no matchee el pass
        }

    }while(passConfirmado == 0);
    */

    printf("\npais: ");
    fflush(stdin);
    gets(aux.pais);

    aux.anioNacimiento = 1950;

    aux.genero = 'o';

    do{
        if(aux.anioNacimiento<1919 || aux.anioNacimiento > 2020){
            printf("A%co no valido, intente denuevo\n", ENIEMINUSCULA);
        }
        printf("\na%co de nacimiento: ", ENIEMINUSCULA);
        fflush(stdin);
        scanf("%i", &aux.anioNacimiento);

    }while(aux.anioNacimiento<1919 || aux.anioNacimiento > 2020);

    do{
        if(aux.genero!='m' && aux.genero!='f' && aux.genero!='o'){
            printf("Genero no valido, intente denuevo\n");
        }
        printf("\ngenero (m/f/o): ");
        fflush(stdin);
        scanf("%c", &aux.genero);
    }while(aux.genero!='m' && aux.genero!='f' && aux.genero!='o');

    int validos_pre_agregar_ADU = **validos_ADU;

    *arreglo_de_usuarios = agregarUsuario(aux, *arreglo_de_usuarios, validos_ADU);

    if((**validos_ADU) == (validos_pre_agregar_ADU + 1)){
        printf("\n\nusuario creado exitosamente!\n\n");
    }else{
        printf("\n\nerror guardando usuario\n\n");
    }

    system("pause");

}




//pregunta el al usuario recien dado de alta se lo quiere nombrar como admin
void altaAdmin(stCelda ** arreglo_de_usuarios, int * validos_ADU){

    //stUsuario aux = ultimoUserIngresado();
    char op;

    printf("desea nombrar al usuario %s administrador?(s/n)\n\n> ", (*arreglo_de_usuarios)[(*validos_ADU)-1].usr.nombreUsuario);
    fflush(stdin);
    scanf("%c", &op);

    if (op == 's' || op == 'S')
    {
        (*arreglo_de_usuarios)[(*validos_ADU)-1].usr.esAdmin = 1;
    }

    ADU_to_archivoUsers(*arreglo_de_usuarios, validos_ADU);
}





void bajaUsers(stCelda ** arreglo_de_usuarios, int * validos_ADU){

    system("cls");
    printf("ADMINISTRACION DE USUARIOS - baja de usuario o admin\n\n");

    stUsuario aux;
    int cont = 0, encontrado = 0, pos_user = -1;
    char op, nombre[30];

    do{
        if(cont != 0)
            printf("\n\nese nombre no fue encontrado\n\n");

        printf("nombre user: ");
        fflush(stdin);
        gets(nombre);

        pos_user = buscarUsuarioPorNombre(nombre, *arreglo_de_usuarios, *validos_ADU);

        if(pos_user != -1)
            encontrado = 1;

        cont++;

    }while(encontrado == 0);    //queda en loop hasta que encuentre un user

    if(aux.esAdmin == 1)
        printf("/nadvertencia: el usuario es administrador/n");

    printf("\nusuario %s encontrado\n\ndesea borrarlo?: (s/n)", (*arreglo_de_usuarios)[pos_user].usr.nombreUsuario);
    fflush(stdin);
    scanf("%s", &op);


    if (op == 's' || op == 'S')
    {
        (*arreglo_de_usuarios)[pos_user].usr.eliminado = 1;
        ADU_to_archivoUsers(*arreglo_de_usuarios, validos_ADU);
        printf("\n\nel usuario %s ha sido borrado\n\n", nombre);
    }
    system("pause");
}




void modUsers(stCelda ** arreglo_de_usuarios, int * validos_ADU){

    system("cls");
    printf("ADMINISTRACION DE USUARIOS - modificación de usuario o admin\n\n");

    stUsuario aux;
    int encontrado = 0, cont = 0, modificar = 0, nuevo_anio, opint, pos_user;
    char nombre[30], nuevo_nombre[30], nuevo_pass[20], nuevo_genero, nuevo_pais[20], op;

    do{
        if(cont != 0)
            printf("\n\nese nombre no fue encontrado\n\n");

        printf("nombre user: ");
        fflush(stdin);
        gets(nombre);

        pos_user = buscarUsuarioPorNombre(nombre, *arreglo_de_usuarios, *validos_ADU);


        if(aux.idUsuario != -1)
        {
            encontrado = 1;
        }

        cont++;

    }while(encontrado == 0);


    aux = (*arreglo_de_usuarios)[pos_user].usr;


    do{
        printf("\nusuario %s encontrado.\nElija un campo del usuario para modificar:\n\n1 - nombre de usuario\n2 - password\n3 - año de nacimiento\n4 - genero\n5 - pais\n6 - nombrarlo administrador\n 0 - menu anterior\n\n>", aux.nombreUsuario);
        fflush(stdin);
        scanf("%i", &opint);

        switch (opint){
            case 0: break;
            case 1:
                printf("\ningrese nuevo nombre de usuario: ");
                fflush(stdin);
                gets(nuevo_nombre);
                strcpy( aux.nombreUsuario , nuevo_nombre );
                break;
            case 2:
                printf("\ningrese nuevo pass: ");
                fflush(stdin);
                gets(nuevo_pass);
                strcpy( aux.pass , nuevo_pass );
                break;
            case 3:
                printf("\ningrese nuevo año de nacimiento: ");
                fflush(stdin);
                scanf("%i", &nuevo_anio);
                aux.anioNacimiento = nuevo_anio;
                break;
            case 4:
                printf("\ningrese nuevo genero: ");
                fflush(stdin);
                gets(&nuevo_genero);
                strcpy( &aux.genero , &nuevo_genero );
                break;
            case 5:
                printf("\ningrese nuevo pais: ");
                fflush(stdin);
                gets(nuevo_pais);
                strcpy( aux.pais , nuevo_pais );
                break;
            default:
                printf("\nopcion incorrecta\n");
                break;
        }

        //confirmacion de la modificacion (si fue exitosa o no)

        printf("\ndesea realizar otro cambio en este usuario? (s/n)\n");
        fflush(stdin);
        scanf("%c", &op);

        if (op == 's' || op == 'S')
        {
            modificar = 1;
        }
        else
        {
            modificar = 0;
        }


    }while(modificar == 1);

    (*arreglo_de_usuarios)[pos_user].usr = aux;

    ADU_to_archivoUsers(*arreglo_de_usuarios, validos_ADU);
}




void consultaUsers(stCelda * arreglo_de_usuarios, int * validos_ADU){

    system("cls");
    printf("ADMINISTRACION DE USUARIOS - consulta de usuario\n\n");

    int cont = 0, pos_user, encontrado = 0;
    char nombre[30];

    do{
        if(cont != 0)
            printf("\n\nese nombre no fue encontrado\n\n");

        printf("nombre del usuario a consultar: ");
        fflush(stdin);
        gets(nombre);

        pos_user = buscarUsuarioPorNombre(nombre, arreglo_de_usuarios, *validos_ADU);


        if(pos_user != -1)
        {
            encontrado = 1;
        }

        cont++;

    }while(encontrado == 0);

    printf("\nINFORMACION DEL USUARIO:\n\n");

    mostrarUsuario(arreglo_de_usuarios[pos_user].usr);  //solo muestra un usuario

    system("pause");

}




void listadoUsers(stCelda * arreglo_de_usuarios, int * validos_ADU){

    system("cls");
    printf("ADMINISTRACION DE USUARIOS - consulta de usuario\n\n");

    printf("se mostraran todos los usuarios\n\n");
    system("pause");

    for(int i = 0 ; i < *validos_ADU ; i++)
    {
        mostrarUsuario(arreglo_de_usuarios[i].usr);
        system("pause");
    }

    printf("FIN DE LISTA DE USUARIOS\n\n");
    system("pause");
}



void menuUser(stCelda * arreglo_de_usuarios, int * validos_ADU, int pos_user, nodoArbolCancion * arbol_de_canciones){

    system("cls");
    printf("MENU DE USUARIO\n\n");

    int op;

    do{
            system("cls");
        printf("1 - ver perfil\n2 - mostrar playlist\n3 - escuchar cancion\n4 - canciones recomendadas\n0 - menu anterior\n\n> ");
        fflush(stdin);
        scanf("%i", &op);

        switch(op)
        {
            case 0: break;
            case 1:
                verPerfil(arreglo_de_usuarios, pos_user);
                break;
            case 2:
                mostrarPlaylistUser(arreglo_de_usuarios, pos_user);
                break;
            case 3:
                escucharCancion(&arreglo_de_usuarios, pos_user, arbol_de_canciones);
                break;
            case 4:
                cancionRecomendada(&arreglo_de_usuarios, pos_user, arbol_de_canciones);
                break;
            default: printf("\n\nla opcion no es valida\n\n"); break;
        }


    }while(op != 0);

}

void verPerfil(stCelda * arreglo_de_usuarios, int pos_user){
    printf("\n\nINFORMACION DEL USUARIO\n\n");
    mostrarUsuario(arreglo_de_usuarios[pos_user].usr);
    system("pause");
}

void mostrarPlaylistUser(stCelda * arreglo_de_usuarios, int pos_user){
    printf("\n\nCONTENIDOS DE LA PLAYLIST DEL USUARIO\n\n");
    if(arreglo_de_usuarios[pos_user].listaCanciones !=NULL)
        mostrarLC(arreglo_de_usuarios[pos_user].listaCanciones);
    else
        printf("No hay contenido en la playlist\n");
    system("pause");
}

void escucharCancion(stCelda ** arreglo_de_usuarios, int pos_user, nodoArbolCancion * arbol_de_canciones){
    nodoArbolCancion * aux;
    int cancion;
    nodoLC * aux2 = inicLista();
    mostrarArbolInorder(arbol_de_canciones);
    printf("\n\ningrese el id de la cancion que desea agregar a la playlist: ");
    fflush(stdin);
    scanf("%d", &cancion);
    aux = buscarNodoId(arbol_de_canciones, cancion);
    if(aux != NULL)
    {
        *arreglo_de_usuarios = agregarToPlaylist(*arreglo_de_usuarios, pos_user, aux2, &aux);
    }
    else
    {
        printf("\nla cancion no fue encontrada\n");
    }
}

void cancionRecomendada(stCelda ** arreglo_de_usuarios, int pos_user, nodoArbolCancion * arbol_de_canciones){
    char rta='n';
    nodoArbolCancion * aux = masGrande(arbol_de_canciones);
    nodoLC * aux2 = inicLista();
    aux = algoritmoRecomendacion(arbol_de_canciones, (*arreglo_de_usuarios)[pos_user], aux);
    printf("mira esta recomendacion:\n");

    if(aux!=NULL)
    {
        mostrarCancion(aux->c);
        system("pause");
    }else{
        printf("VACIO");
        system("pause");
    }

    printf("\nqueres agregarla a tu playlist? (s/n): \n");
    fflush(stdin);
    scanf("%c", &rta);
    if(rta == 's' || rta == 'S')
    {
        *arreglo_de_usuarios = agregarToPlaylist(*arreglo_de_usuarios, pos_user, aux2, &aux);
    }
}

stCelda *agregarToPlaylist(stCelda * arreglo_de_usuarios, int pos_user, nodoLC *lista, nodoArbolCancion **leaf){
    lista = crearNodoLC((*leaf)->c);
    arreglo_de_usuarios[pos_user].listaCanciones = agregarFinal(arreglo_de_usuarios[pos_user].listaCanciones, lista);
    ((*leaf)->c.recomendacion)++;
    actualizarCancionesEscuchadas(arreglo_de_usuarios[pos_user].usr, (*leaf)->c);
    return arreglo_de_usuarios;
}


void adminCanciones(nodoArbolCancion * arbol_de_canciones){
    int op;

    do{
        system("cls");
        printf("ADMINISTRACION DE CANCIONES\n\n");



        printf("1 - alta \n2 - baja\n3 - modificacion\n4 - consulta\n5 - listados\n0 - salir del menu\n\n> ");
        fflush(stdin);
        scanf("%i", &op);



        switch(op)
        {
            case 0: break;
            case 1: altaSong(&arbol_de_canciones); break;
            case 2: bajaSong(&arbol_de_canciones); break;
            case 3: modSong(&arbol_de_canciones); break;
            case 4: consultaSong(arbol_de_canciones); break;
            case 5: listadoSong(arbol_de_canciones); break;
            default: printf("\n\nla opcion no es valida\n\n"); break;
        }

    }while(op != 0);
}


void altaSong(nodoArbolCancion ** arbol_de_canciones)
{

    system("cls");
    printf("ADMINISTRACION DE CANCIONES - alta de cancion\n\n");

    *arbol_de_canciones = cargarArbol(*arbol_de_canciones);
    FILE * archiSong = fopen(ASONG, "wb");
    arbolToArchivo(*arbol_de_canciones, archiSong);
    fclose(archiSong);

    //cant_canciones = contarCanciones();
}


void bajaSong(nodoArbolCancion ** arbol_de_canciones)
{
    char op = 'n';

    do{
        system("cls");
        printf("ADMINISTRACION DE CANCIONES - baja de cancion\n\n");

        mostrarArbolInorder(*arbol_de_canciones);
        printf("\n");
        borrarNodo(arbol_de_canciones);

        FILE * archiSong = fopen(ASONG, "wb");
        arbolToArchivo(*arbol_de_canciones, archiSong);
        fclose(archiSong);

        printf("Desea borrar otra nodo? (s/n)\n");
        fflush(stdin);
        scanf("%c", &op);

    }while(op == 's');
}


void modSong(nodoArbolCancion ** arbol_de_canciones)
{
    char op = 'n';

    do{
        system("cls");
        printf("ADMINISTRACION DE CANCIONES - modificacion de cancion\n\n");

        mostrarArbolInorder(*arbol_de_canciones);
        printf("\n");
        modificarCancion(arbol_de_canciones);

        FILE * archiSong = fopen(ASONG, "wb");
        arbolToArchivo(*arbol_de_canciones, archiSong);
        fclose(archiSong);

        printf("Desea modificar otra nodo? (s/n)\n");
        fflush(stdin);
        scanf("%c", &op);

    }while(op == 's');
}


void consultaSong(nodoArbolCancion * arbol_de_canciones)
{
    char op = 'n';

    do{
        system("cls");
        printf("ADMINISTRACION DE CANCIONES - consulta de cancion\n\n");

        consulta(arbol_de_canciones);

        printf("Desea consultar otra nodo? (s/n)\n");
        fflush(stdin);
        scanf("%c", &op);

    }while(op == 's');
}


void listadoSong(nodoArbolCancion * arbol_de_canciones)
{
        system("cls");
        printf("ADMINISTRACION DE CANCIONES - listado de canciones\n\n");

        mostrarArbolInorder(arbol_de_canciones);

        system("pause");

}
